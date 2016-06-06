#!/bin/bash 

cd ./language
export PYTHONPATH=`pwd`

python shac.py gasBurner_waterTank_Interface.json cfb /Users/jinchen/Desktop/2016_Semester1/VS\ plugin/JsonToIEC/generatedHA/
