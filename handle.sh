#!/bin/bash


inputName="inputs/solarsystem2.csv"
outputName="outputs/coordstest.csv"
dt=30
# year=31536000
# N=$(($year/$dt))
N=3000000

saveStep=1000
index=-1
doRK4=0
doAllinteractions=0

./main ${inputName} ${outputName} ${N} ${dt} ${saveStep} ${index} ${doRK4} ${doAllinteractions}