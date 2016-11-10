#!/usr/bin/env python

# PFG lxbatch job submitter
#
# Author: Grigory Latyshev, 2016
# Institute for High Energy Physics, Russia 
#

import sys
import os
import argparse
import subprocess
import shutil
import glob
import re

eos = "/afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select"

abspath = os.path.abspath
dirname = os.path.dirname
basename = os.path.basename
osjoin = os.path.join

def submit(filename, opts, dryrun = False):
  if dryrun:
    print " ".join(["bsub -q 1nh"] + opts.split(" ") + [ filename ])
  else:
    print "# Submitting a job ..."
    subprocess.call(["bsub"] + opts.split(" ") + [ filename ])

def replacetext(filename, text, replace):
  r = []
  with open(filename, 'r') as f:
    for l in f.readlines():
      r.append(l.replace(text, replace))
  with open(filename, 'w') as f:
    f.write("".join(r))

def checkGridCert():
  FNULL = open(os.devnull, 'w')
  rc = subprocess.call(['voms-proxy-info'], stdout=FNULL)
  if rc == 0:
    if not os.path.exists(osjoin(dirname(sys.argv[0]), "credentials")):
      os.mkdir(osjoin(dirname(sys.argv[0]), "credentials"))
    for filename in glob.glob(osjoin("/tmp", 'x509up*')):
      try:
        shutil.copy(filename, abspath(osjoin(dirname(sys.argv[0]), "credentials")))
      except:
        pass
    if len(glob.glob(osjoin(osjoin(dirname(sys.argv[0]), "credentials"), 'x509up*'))) == 0:
      return False 
    
  return not bool(rc)
  
def updateGridCert():
  if checkGridCert():
    return True
  rc = subprocess.call(['voms-proxy-init', '--voms', 'cms'], stdout=sys.stdout, stdin=sys.stdin)
  return checkGridCert()

def getCMSSWfilepath(f, source):
  if source == "eos":
    filepath = "root://eoscms//eos/cms/tier0/" + osjoin(args.eos_dir, basename(f))
  elif source == "files":
    if os.path.exists(f):
      filepath = "file:" + abspath(f)
    else:
      filepath = f
  elif source == "das":
    filepath = "root://cms-xrd-global.cern.ch/" + f
  return filepath

parser = argparse.ArgumentParser()
parser.add_argument('infile', help="CMSSW configuration file to process", metavar = "infile")
parser.add_argument('--eos-dir', help="EOS directory with .root files", dest='eos_dir', metavar="directory")
parser.add_argument('--run', help="Run number", dest='run', metavar="run", type=int)
parser.add_argument('--dataset', help="Dataset", dest='dataset', metavar="dataset")
parser.add_argument('--instance', help="DAS Instance", dest='instance', metavar="instance")
parser.add_argument('--cmssw', help="Path to CMSSW", dest='cmssw_dir', metavar="path", default = ".")
parser.add_argument('--output-dir', help="Output directory", dest='output_dir', metavar="directory", default="results")
parser.add_argument('--lxopts', help="lxbatch options", dest='lxopts', metavar="string", default = "")
parser.add_argument('--files-from', help="File with file paths", dest='files_from', metavar="file")
parser.add_argument('--regexp', help="Regular expression to match file names", dest='regexp_name', metavar="regexp")
parser.add_argument('--return-files', help="Path to file with paths to be copied from batch node", dest='file_to_copy', metavar="filename", default = "*")
parser.add_argument('--maxfiles', help="Maximum files to process", dest='maxfiles',type = int, default = -1)
parser.add_argument('--env_prefix', help="Prefix for substituon of environment variables", dest='env_prefix', metavar="prefix", default = "EXTRA_")
parser.add_argument('--join-files', help="Join N files in one job, use N<0 for joining all files", dest='join_files', metavar="N", default = 1, type = int)
parser.add_argument('-n', '--dry-run', help="Do nothing, just prepare files", dest='dryrun', action="store_true", default = False)
parser.add_argument('-l', '--list-files', help="List processed files", dest='listfiles', action="store_true", default = False)

args = parser.parse_args()
dryrun = args.dryrun

if args.files_from:
  source = "files"
elif args.eos_dir:
  source = "eos"
elif args.run and args.dataset:
  source = "das"
else:
  print "# You should specify --files-from or --eos-dir or (--run and --dataset) options"
  sys.exit(0)

if not os.path.exists(args.output_dir):
  if dryrun:
    print "mkdir -p", abspath(args.output_dir)
  else:
    os.mkdir(abspath(args.output_dir))
else:
  print "# Output directory '{0}' exists. It will be used anyway ...".format(args.output_dir)

# prepare list of replacements
replaces = []
for var in os.environ.keys():
  if var.startswith(args.env_prefix):
    realname = "%" + var.replace(args.env_prefix, "") + "%"
    print "# Will replace text '{0}' to '{1}' in the files".format(realname, os.environ[var])
    replaces.append((realname, os.environ[var]))

#loop over files
if source == "files":
  with open(args.files_from, 'r') as f:
    infiles = [x.strip() for x in f.readlines()]
elif source == "eos":
  print "# Reading files from eos ..."
  p = subprocess.Popen("{0} ls {1}".format(eos, args.eos_dir).split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  stdout, stderr = p.communicate()
  infiles = stdout.split("\n")
elif source == "das":
  print "# Calling DAS ..."
  if args.run and args.instance:
      cmd = "{0} --limit=0 --query='file run={1}  dataset={2} instance={3}'".format(osjoin(dirname(sys.argv[0]), "das_client.py"), args.run, args.dataset, args.instance)
  elif args.run:
      cmd = "{0} --limit=0 --query='file run={1}  dataset={2}'".format(osjoin(dirname(sys.argv[0]), "das_client.py"), args.run, args.dataset)
  elif args.instance:
      cmd = "{0} --limit=0 --query='file dataset={1} instance={2}'".format(osjoin(dirname(sys.argv[0]), "das_client.py"), args.dataset, args.instance)
  else:
      cmd = "{0} --limit=0 --query='file dataset={1}'".format(osjoin(dirname(sys.argv[0]), "das_client.py"), args.dataset)

  p = subprocess.Popen(cmd, stdout=subprocess.PIPE,stderr=subprocess.PIPE, shell=True)
  stdout, stderr = p.communicate()
  if len(stderr) != 0:
    print "# Something wrong happened with DAS:", stderr
  infiles = stdout.split("\n")
  infiles.pop(1)

fidx = 0
if args.regexp_name:
  rname = re.compile(args.regexp_name)
else:
  rname = None

if args.listfiles:
  print "# Files:"
  for l in infiles:
    if len(l) == 0:
      continue
    if rname:
      if not bool(rname.match(l)):
        continue
    fidx += 1
    if args.maxfiles != -1 and fidx > args.maxfiles:
      break
    print "# ", getCMSSWfilepath(l, source)
  sys.exit(0)

fidx = 0
filestoprocess = []
infiles = [x for x in infiles if x != ""]
for f in infiles:
  f = f.strip()
  if rname:
    if not bool(rname.match(f)):
      continue
  fidx += 1
  if args.maxfiles != -1 and fidx > args.maxfiles:
    break
  filestoprocess.append(f)
  if f != infiles[-1]:
    if args.join_files > 0:
      if fidx % args.join_files != 0:
        continue
    else:
      continue
  workpath = abspath(osjoin(args.output_dir, basename(f)))
  if not os.path.exists(workpath):
    if dryrun:
      print "mkdir -p", workpath
      print "mkdir -p", osjoin(workpath, "copied_files")
    else:
      os.mkdir(workpath)
      os.mkdir(osjoin(workpath, "copied_files"))
  newinfile = abspath(osjoin(workpath, basename(args.infile)))
  if dryrun:
    print "cp -f {0} {1}".format(abspath(args.infile), newinfile)
  else:
    shutil.copy(abspath(args.infile), newinfile)
  # handle PoolSource
  filepath = getCMSSWfilepath(f, source)
  for (text, rep) in replaces:
    if dryrun:
      print "sed -i 's,{0},{1},g' {2}".format(text, rep, newinfile)
    else:
      replacetext(newinfile, text, rep)
  if not dryrun:
    fh = open(newinfile, 'r')
    lines = fh.readlines()
    fh.close()
    PoolSourceidx = lines.index(
      [x for x in lines if "PoolSource" in x][0]
    )
    filelisttxt = "myfilelist = cms.untracked.vstring()\n"
    filelisttxt += "\n".join(["myfilelist.append('{0}')".format(getCMSSWfilepath(x, source)) for x in filestoprocess]) + "\n"
    lines = lines[0:PoolSourceidx] + [filelisttxt] + lines[PoolSourceidx:]
    fh = open(newinfile, 'w')
    fh.write("".join(lines))
    fh.close()
    replacetext(newinfile, "%FILENAME%", "myfilelist")  
  else:
    print "sed -i \"/PoolSource/i myfilelist = cms.untracked.vstring()\"", newinfile
    for ftp in filestoprocess:
      print "sed -i \"/PoolSource/i myfilelist.append('{0}')\"".format(getCMSSWfilepath(ftp, source)), newinfile
    print "sed -i 's/%FILENAME%/myfilelist/g'", newinfile
  if not dryrun:
    with open(newinfile, 'r') as fh:
      for l in fh.readlines():
        if re.match(".*\%.*\%.*", l):
          print "Some %pattern% blocks have not been replaced:"
          print ">>>"
          print l.strip()
          print "<<<"
          sys.exit(0)
  newbsubfile = osjoin(workpath, "bsub.sh")
  updateGridCert()
  if dryrun:
    fh = sys.stdout
  else:
    fh = open(newbsubfile, 'w')
  txt = """
#!/bin/bash
export mypwd=`pwd`
cd {cmsswdir}

eval `scramv1 runtime -sh`
export
cd -

cp -vf {cfgpysource} .
cp {cred} /tmp/
cmsRun {cfgpyfile}
pwd

ls -lrt
"""
  if dryrun:
    txt = txt.replace("`", "\`")
    print "cat <<EOF > {0}".format(newbsubfile)
  fh.write(txt.format(cmsswdir = abspath(args.cmssw_dir), cred = abspath(osjoin(dirname(sys.argv[0]), "credentials", "*")), cfgpysource = newinfile, cfgpyfile = basename(newinfile)))
  for k in [x.strip() for x in args.file_to_copy.split()]:
    fh.write("cp -fv {0} {1}\n".format(k, abspath(osjoin(workpath, "copied_files"))))
  if dryrun:
    print "EOF"
  else:
    fh.close()
  if dryrun:
    print "chmod 755", newbsubfile
  else:
    os.chmod(newbsubfile, 0755)
  submit(newbsubfile, args.lxopts, dryrun = args.dryrun)
  filestoprocess = []
