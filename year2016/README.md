# RunPreparation for year 2016
Repository meant to store all macros/documents used for run preparation studies. 
Rules:
-- each macro should have a header that clearly states
a) what the macro does
b) the input needed
c) the output
d) how to run the macro

## Analysis

This directory contains all the macros needed for analaysis during the data taking of pPb 2016. It is currently divided in two directories: 

Onia: Contains all the macros to test and produce (batch and CRAB jobs) the onia trees.
Acceptance: Contains all the macros to perform the Acceptance studies to determine the best kinematic cuts for single muons.

## Analysis/Onia/Tools
### OniaQA.C
Requires opening an OniaTree root file, and navigating to the directory with the tree "myTree".  Draws about 20 histograms of various distributions, event-wise, muon-wise, and muon-pair-wise.  Includes an example of using the dimuon 4-momentum to obtain the opening angle between the muons (since one can't use the v1.Angle(v2) functionality in a Tree->Draw() command).

## MuonID

This directory contains all the macros needed to study the different muon ID variables used during run2 2016 and determine the best set of cuts.

## PublicRelation

This directory contains all the macros related to the production of plots and event displays for public display. Currently, it only has one directory for the macros used to produce the Yellow Plots.

## Trigger

This directory contains all the macros related to trigger studies. It is currently divided in two directories:

openHLT:  Contains the macros to produce the openHLT trees used to compare the performance of the L1/HLT emulator vs data.
Rates: Contains the macros related to trigger rate studies, including the ones to determine the best set of prescales.

### checkrates.C
Compares rates from the output of recorded_by_HLT_path (with option --scalerate 1e6) to the expectation

## HLT_runbyrun  (please move to Trigger :) )
See https://twiki.cern.ch/twiki/bin/view/CMS/HITriggerTool

## .
### compare.C
Loops over two ROOT files with a common structure and plots histograms that are significantly different (based on chi2 or KS) between the two.

### savedir.C
Extracts the Muon directory from offline DQM files

