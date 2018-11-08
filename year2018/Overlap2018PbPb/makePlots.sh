#!/bin/sh
# script to make the overlap plots, for different collision rates

# first argument is the numebr of MB pd to overlap with, then the collision rate

# available columns
crCol=(8 10 13 16 20 23 26 30)
#40 50)

# total number of columns
numCols=${#crCol[@]}

# which CR to be processed
startCR=0
endCR=${numCols}

# number of MB PD with which the overlap is checked
nMbPDs=1

for (( i=${startCR}; i<${endCR}; i++ ));
do
    echo "Doing plots for $cr ..."
    echo "root -l draw.C\($nMbPDs,${crCol[i]}\) -q -b"
    root -l draw.C\($nMbPDs,${crCol[i]}\) -q -b
done

