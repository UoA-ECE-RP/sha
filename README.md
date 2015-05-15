# sha
Generate synchronous code from subset of hybrid automata

This is the procedure to run the code for the watertank example in the
examples directory:

* To compile
```bash
cd ./language
export PYTHONPATH=`pwd`
cd ../examples
python2.7 watertank.py

gcc watertank.c wio.c -o w -lm

```
* To run
```bash
./w
```
Plot the wout.csv file in excel!

# Python dependencies
