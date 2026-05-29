#!/bin/bash

dt_tab=("1 10 100 1000 10000")
saveStep=1000
index=-1
doRK4=0
doAllinteractions=0
year=31536000


for i in $dt_tab
do

    echo "Processing simualtion with step size of "${i}" seconds"
    dt=${i}
    inputName="inputs/solarsystem.csv"
    outputName="outputs/coordsSolar"${dt}".csv"

    base=10000
    N=$(($year/$dt))
    saveStep=$(($base / $dt))
    #N=3000000



    ./main ${inputName} ${outputName} ${N} ${dt} ${saveStep} ${index} ${doRK4} ${doAllinteractions}

done