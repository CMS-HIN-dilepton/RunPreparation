# Rate Calculator for Muon base triggers

This is a simple calulator for muon triggers to estimate firing rate.

## Function definition


```
HltInput.h
```
HltInput class will fetch 'hltanalysis/HltTree' and trigger object in 'hltobject/(trigger name)'.

```
RateCalc.h
```
RateCalc class inherits HltInput, getters and calculation are all included in here

The `calculateRate.C` macro runs a calculator for all given HLT triggers in given file. Modify the input file name and imply run

```bash
root -b -q calculateRate.C
```
.

