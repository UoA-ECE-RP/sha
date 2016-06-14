#!/bin/bash 

cd ./language
export PYTHONPATH=`pwd`

#on windows
#the first path is the path of the json file, and the second path is where you want to save the converted .fbt file
#python shac.py ../examples/hajson/waterTank.json fbt C:\\vsplugin\\sha\\generatedHA\\

#on linux or mac
#the first path is the path of the json file, and the second path is where you want to save the converted .fbt file
python shac.py ../examples/hajson/waterTank.json fbt /Users/jinchen/Desktop/2016_Semester1/VS\ plugin/JsonToIEC/generatedHA/
python shac.py ../examples/hajson/gasBurner.json fbt /Users/jinchen/Desktop/2016_Semester1/VS\ plugin/JsonToIEC/generatedHA/
