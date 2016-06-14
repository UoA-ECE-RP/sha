#!/bin/bash 

cd ./language
export PYTHONPATH=`pwd`

#the json file should be put in the language folder for now, and the last parameter is the path you want to save the generated .cfb file
python shac.py gasBurner_waterTank_Interface.json cfb /Users/jinchen/Desktop/2016_Semester1/VS\ plugin/JsonToIEC/generatedHA/
