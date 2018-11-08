#!/bin/python
import sys,string
import csv
from operator import itemgetter
import numpy as np

# script to read the output spit by the OverlapTool, saved in an input (to this script) file (./makeRateHistos > screenSpit.txt

_j_args  = sys.argv

_inputfile     = _j_args[1]
_outfileprefix = _j_args[2]

print("input file name, and outputfileprefix: ", _inputfile, _outfileprefix)

collRateList = [8, 13, 16, 20, 23, 26, 30]

# read the input file
myfile = open(_inputfile, 'r')

words    = [];
ncrs=0
pdnames  = [];
npds=0;
pdstart=0;
pdend=0;

pdrate   = [];


pdaveevtsize=[]
pdoutsize=[]
pdtotalout=[]

sizestart=0
sizeend=0

readrate = [];
i=0;
pdnum=0

for line in myfile:
    splitline = line.split()
    if len(splitline)<1:
        continue
    words.append(splitline)
    if words[i][0].startswith("At") == True:
        readrate.append(splitline[1])
        print("########CR= ", readrate[ncrs])
        ncrs+=1
        pdstart=i+1
        #    if len(readrate)==1: #store all the PD names and rates
    if words[i][0].startswith("-_-_-_-_-")==True:
        pdend=i
        npds=pdend-pdstart
        for pd in range(pdstart,pdend):
            pdnames.append(words[pd][0])
            pdrate.append(words[pd][5])
    if len(splitline)>1:
        if splitline[1]==("TOTAL"): #store pd_output_size: average per event, per pd, total
            sizeend=i-1
            sizestart=i-npds-1
            pdtotalout.append(words[i][4])
            #print("pdend and pdstart",sizestart,sizeend)
            print("Total data rate from all PDs:",words[i][4])
            for ipd in range (sizestart,sizeend):
                pdaveevtsize.append(words[ipd-npds][9])
                # print("Average event size per PD: ", words[ipd-npds][9])
                    
                pdoutsize.append(words[ipd+1][5])
                # print("Average data rate per PD: ", words[ipd+1][5])
    i+=1

print("######## Number of columns: ",ncrs, len(readrate))
print("######## Number of PDs: ",npds)
print(pdnames)
print(len(readrate))
print(len(pdoutsize))
print(len(pdaveevtsize))
# writting output
#outfile1=open(str(_outfileprefix)+"_pdRates"+".txt", "w")#1
outcollrate=[]


frate    = open(str(_outfileprefix)+"_pdrate"+".txt", "w")# output file
fsize    = open(str(_outfileprefix)+"_pdsize"+".txt", "w")# output file
fsizeave = open(str(_outfileprefix)+"_pdsizeave"+".txt", "w")# output file

#frate.write('%-40s %6s %10s %2s\n' % (filename, type, size, modified))

for ipd in range (npds):
    outpdrate=[]
    outpdoutsize=[]
    outpdevtavesize=[]
    for icr in range (ncrs):
        if ipd==0:
            outcollrate.append(readrate[icr])
            print("### collision rate: ", readrate[icr])

        #print("PD index", ipd)
        #print(npds*icr+ipd)
        #print("pdName, pdRate, pd ave evts size, outSize: ",pdnames[npds*icr+ipd],pdrate[npds*icr+ipd],pdoutsize[npds*icr+ipd],pdaveevtsize[npds*icr+ipd])
        outpdrate.append(pdrate[npds*icr+ipd])
        outpdoutsize.append(pdoutsize[npds*icr+ipd])
        outpdevtavesize.append(pdaveevtsize[npds*icr+ipd])
    if(ipd==0):
        frate.write('\t'+'\t'.join(outcollrate[0:])+'\n')
        fsize.write('\t'+'\t'.join(outcollrate[0:])+'\n')
        fsizeave.write('\t'+'\t'.join(outcollrate[0:])+'\n')
    frate.write(pdnames[ipd]+'\t'+'\t'.join(outpdrate[0:])+'\n')
    fsize.write(pdnames[ipd]+'\t'+'\t'.join(outpdoutsize[0:])+'\n')
    fsizeave.write(pdnames[ipd]+'\t'+'\t'.join(outpdevtavesize[0:])+'\n')
# print(pdnames[ipd],outpdrate)
#    print(pdnames[ipd],outpdoutsize)
#    print(pdnames[ipd],outpdevtavesize)

frate.close()
fsize.close()
fsizeave.close()
