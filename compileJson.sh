#!/bin/bash 

cd ./language
export PYTHONPATH=`pwd`
python shac.py ../examples/hajson/waterTankJason.json fbt C:\\vsplugin\\sha-compiler\\compiler\\cj\\
