# RunPreparation for year 2016
Repository meant to store all macros/documents used for run preparation studies. 
Rules:
-- each macro should have a header that clearly states
a) what the macro does
b) the input needed
c) the output
d) how to run the macro

## Analysis
## Analysis/Onia
## Analysis/Onia/Tools
### OniaQA.C
Requires opening an OniaTree root file, and navigating to the directory with the tree "myTree".  Draws about 20 histograms of various distributions, event-wise, muon-wise, and muon-pair-wise.  Includes an example of using the dimuon 4-momentum to obtain the opening angle between the muons (since one can't use the v1.Angle(v2) functionality in a Tree->Draw() command).
## .
### compare.C
Loops over two ROOT files with a common structure and plots histograms that are significantly different (based on chi2 or KS) between the two.

### savedir.C
Extracts the Muon directory from offline DQM files

## Trigger
### checkrates.C
Compares rates from the output of recorded_by_HLT_path (with option --scalerate 1e6) to the expectation

## HLT_runbyrun
See https://twiki.cern.ch/twiki/bin/view/CMS/HITriggerTool
