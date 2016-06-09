#!/bin/bash 

cd ./language
export PYTHONPATH=`pwd`
#python shac.py ../examples/hajson/waterTank.json fbt C:\\vsplugin\\sha\\generatedHA\\

python shac.py ../examples/hajson/waterTank.json fbt /Users/jinchen/Desktop/2016_Semester1/VS\ plugin/JsonToIEC/generatedHA/
python shac.py ../examples/hajson/gasBurner.json fbt /Users/jinchen/Desktop/2016_Semester1/VS\ plugin/JsonToIEC/generatedHA/
