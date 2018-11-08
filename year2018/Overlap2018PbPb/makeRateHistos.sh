#!/bin/sh
# script to run the overlap tool, for many PS columns
# the sorting.py script has to be run before: it produces the input tex files, with hlt path, l1 seed, pd name, l1 PS, hlt PS, and evt size
# feel free to change star/end of PS columns, based on what you want from the crCol

#number of events to be processed for the overlap
numEvtsToProces=250000

# location of input file (all triggers MUST be unprescaled there
fileLocation="/tmp/cmm/openHLT_MinBias_V1V11V4Era.root"

# name-prefix of the files with the paths, pds, pss (produced by the sorting.py)

inputFilePrefix="psTable_20181106"
#inputFilePrefix="psTable_20181101"
#inputFilePrefix="psTable_flow"
#inputFilePrefix="dilepton"

# available columns
crCol=(8 10 13 16 20 23 26 30)
#40 50)


# total number of columns
numCols=${#crCol[@]}

# which CR to be processed
startCR=0
endCR=${numCols}


for (( i=${startCR}; i<${endCR}; i++ ));
do
    cr=$((${crCol[i]}*1000))
    echo "Doing collision rate $cr ..."
    echo "file Location:" $fileLocation
    echo "number of events to process: " $numEvtsToProces
    echo "./GenerateOverlapInputs.py ${inputFilePrefix}_${crCol[i]}kHz.txt --mytag all_${crCol[i]}khz --HltTreePath ${fileLocation} --rate $cr --nEvents $numEvtsToProces"
    ./GenerateOverlapInputs.py ${inputFilePrefix}_${crCol[i]}kHz.txt --mytag all_${crCol[i]}khz --HltTreePath ${fileLocation} --rate $cr --nEvents $numEvtsToProces

done

