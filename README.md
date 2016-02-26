# sha
Generate synchronous code from subset of hybrid automata

## This is the procedure to run the code for the watertank example in the examples directory:

* To compile
```bash
cd ./language
export PYTHONPATH=`pwd`
cd ../examples/waterTank
python2.7 wr.py

gcc watertankR.c wior.c -o w -lm

```
* To run
```bash
./w
```
Plot the wout.csv file in excel!

## Python dependencies
1. sympy
2. macropy
3. colorama
4. termcolor
5. jsonlib2
6. Python version 2.7 only

## Installing dependencies 
``` bash
pip install sympy macropy colorama termcolor jsonlib2
```
