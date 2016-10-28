#! /usr/bin/python

import json, os

PDPATHS = open("files.txt","r")

for PDPATH in PDPATHS.readlines():
    PDPATH = PDPATH.rstrip()
    PDNAME = PDPATH.split("/")[1]
    PDTYPE = PDPATH.split("/")[3].rstrip()
    qout = os.popen("das_client.py  --query='run,lumi  dataset='"+PDPATH+"'' --format=json --limit=0")
    data = json.load(qout)
    target = open("./LUMIS/"+PDNAME+"_"+PDTYPE+"_lumySummary.json", 'w')
    target.write("{");
    for ind,val in enumerate(data["data"]):
        target.write("\""+str(data["data"][ind]["run"][0]["run_number"])+"\"" + ": "+ str(data["data"][ind]["lumi"][0]["number"]))
        if (data["data"][ind] != data["data"][-1]): 
            target.write(", ")  
    target.write("}")
    print "LumiSummary created for " + PDPATH

