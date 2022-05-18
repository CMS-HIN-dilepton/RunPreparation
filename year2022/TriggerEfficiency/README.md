Trigger efficiency plots for dimuon triggers

To run this code follow these instructions:

## Muon Trigger Efficiency

# HOW TO USE
To use the code, first compile with make command in the main directory:
```
make
```
this must be done each time C++ code is modified.

you can also remove compiled files by typing command in the main directory:
```
make clear
```

To run calculate the efficiency for all triggers, use the
multiTrigeff.sh bash script. Inside set the variables:
ONIAFILEPATH, TRIGGERFILEPATH, OUTPUTPATH, PTRANGE, MAXJOBS, TYPE
to configure the path to reco file, trigger file and output directory respectively.

use triggername.sh to split triggers by typing oniafilename 
Files triggersL1.txt triggersL2.txt and triggersL3.txt contains the list of
triggers to process for L1, L2 and L3 triggers respectively.

GetTriggersName makes you easy to split triggers into triggersLX.txt
Please check how source code divide triggers into text file.


Then run with command:
```
./multiTrigeff.sh
```
inside main directory.
The code will calculate efficiencies for triggers provided in parallel,
up to MAXJOBS triggers simultaneusly ( one CPU core/thread per trigger ) and put it in OUTPUTPATH directory.

Output is placed inside OUTPUTPATH path inside a directory named like the reco file used.
Inside that directory there is one directory named as each trigger, with the results inside each.


Efficiencies are calculated as a function of pt, rapidity, centrality and pt+rapidity 2D. Also there is separated efficiencies calculated for mid barrel and forward region as a function of pt. "hist.root" file contains TH1, TH2 and TEfficiency objects calculated in the process.


A plot of superimposed efficiencies as function of pt per trigger level is output in this directory.
A directory named "report" contains a pdf with all plots for efficiencies calculated.

Similarly the bash script trigeff.sh can be configured and ran to calculate trigger efficiency of just one trigger at a time.

If you run ./multiTrigeff.sh, there is additional step getting a reco efficiency from oniafile.

just comment out ./Tools/getEfficiency_pure in the bash script if you want to get only trigger effiency.


If you want to get reco efficiency only, change directory from main directory to Tools/., set the variables in the Tools/run.sh script repectively and then run ./run.sh in that directory.

