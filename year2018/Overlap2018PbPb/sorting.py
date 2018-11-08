#!/bin/python
import sys,string
import csv
from operator import itemgetter
import numpy as np

# Get input: file name rate, and number of prescale columns

_j_args  = sys.argv
_outfileprefix = _j_args[2]
print("outputfilename: ", _outfileprefix)


with open(_j_args[1]) as f:
    lines = [line.split('\t') for line in f]
    # reading input file name: output is a list/array of 'lines'/strings
    reader   = csv.reader(open(_j_args[1],'r'),delimiter="\t")

    # make a list sorted by the PD name
    outtable = sorted(reader,key=itemgetter(3)) 
    
    #remove the last entry in list, which is the header file 
    del outtable[-1]
    
    #collision rate columns
    crcols  = filter(None,outtable[0])#columns with prescales, from which the zero entries were removed
    ncrcols = len(crcols)#number of columns with prescales
    print('Number of PS columns:',ncrcols)

    ncolsInFile  = 5+ncrcols*6 #ping+hlt+l1seed + PD+ 6 columns for each CR + evt size
    ncolsOutFile = 6 # hlt + l1seed + PD + l1_ps + hlt_ps + evtsize
    print('columns in input file and output file:',ncolsInFile,ncolsOutFile)
    for ncr in range(0,ncrcols):
        print("PS column# ....: ", crcols[ncr])
        outputf=open(str(_outfileprefix)+"_"+str(crcols[ncr])+".txt", "w")#1 file for each CR
        l1poz       = 6*(ncr+1)-2
        hltpoz      = 6*(ncr+1)+1
        evtsizepoz  = ncolsInFile-2
        #print("a,b,c: ", l1poz,hltpoz,evtsizepoz)
        for line in outtable: #for each element in the array
            if filter(None,line):#remove empty lines/elements (whole empty rows) 
                if ncr==0:
                    del line[0] # remove first column
                line = [ch.replace("#DIV/0!","0") for ch in line] #replace by 0 where not availale
                l1PS,hltPS,size       = [line[i] for i in [l1poz,hltpoz,evtsizepoz]]
                hltPath,l1Seed,PDname = [line[i] for i in [0,1,2]]
              #  print("output: ", hltPath,l1Seed,PDname,l1PS,hltPS,size)
                outputf.write(''.join((hltPath,'\t',l1Seed,'\t',PDname,'\t',l1PS,'\t',hltPS,'\t',size,'\n')))
        outputf.close()
  

