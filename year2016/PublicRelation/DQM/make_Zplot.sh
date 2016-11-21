#!/bin/bash

function lumi {
   if [ $1 -eq 285480 ]; then
      echo 0.034
   fi
   if [ $1 -eq 285505 ]; then
      echo 1.714
   fi
   if [ $1 -eq 285517 ]; then
      echo 9.889
   fi
   if [ $1 -eq 285530 ]; then
      echo 12.154
   fi
   if [ $1 -eq 285537 ]; then
      echo 3.071
   fi
   if [ $1 -eq 285538 ]; then
      echo 1.245
   fi
   if [ $1 -eq 285539 ]; then
      echo 5.833
   fi
   if [ $1 -eq 285549 ]; then
      echo 3.727
   fi
}

# MAIN PART
rm dqm_hadd.root
rm plotZ.gif
totlumi=0
cp dqm_muon_285480.root dqm_hadd.root

totlumi=`lumi 285480`
root -l -b -q countZs.C'("dqm_muon_285480.root",285480,285480,'${totlumi}',false)'

for run in 285505 285517 285530 285537 285538 285539 285549; do
   hadd dqm_hadd2.root dqm_hadd.root dqm_muon_${run}.root
   mv dqm_hadd2.root dqm_hadd.root
   thislumi=`lumi ${run}`
   totlumi=`echo ${totlumi}+${thislumi} | bc -l`
   echo $thislumi $totlumi
   root -l -b -q countZs.C'("dqm_hadd.root",285480,'${run}','${totlumi}',false)'
   root -l -b -q countZs.C'("dqm_hadd.root",285480,'${run}','${totlumi}',true)'
done

rm dqm_hadd.root
