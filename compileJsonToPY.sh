#!/bin/bash 

cd ./language
export PYTHONPATH=`pwd`

python shac.py ../examples/hajson/waterTank.json
