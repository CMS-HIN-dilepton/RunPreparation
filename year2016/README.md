# RunPreparation for year 2016
Repository meant to store all macros/documents used for run preparation studies. 
Rules:
-- each macro should have a header that clearly states
a) what the macro does
b) the input needed
c) the output
d) how to run the macro

## .
### compare.C
Loops over two ROOT files with a common structure and plots histograms that are significantly different (based on chi2 or KS) between the two.

### savedir.C
Extracts the Muon directory from offline DQM files

## Trigger
### checkrates.C
Compares rates from the output of recorded_by_HLT_path (with option --scalerate 1e6) to the expectation
