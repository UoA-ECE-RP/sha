# compiler

This is a compiler from Hybrid Automata in Python to IEC-61499 in XML.

Developed and tested on Python 2.7 

Make sure to supply the Python Hybrid Automata models in the correct format. Have a look at the examples folder for the right format and the generated sample XML files. The pdf report file contains information about the code. 

##Python Dependencies 

Have these in your sys.path

1. lxml 3.5.0
2. sympy 0.7.6.1
3. macropy

You'll also need to have the dependencies required by your Hybrid Automata Python model in your sys.path

##To run the compiler 

1. Make the Hybrid Automata python model file you would like to compile visible to the compiler by exporting its path to the PYTHONPATH (or placing it in sys.path) so that it can be imported.

2. Open the src/HAIEC.py file. 

3. In HAIEC.py file, import your Hybrid Automaton model file and the Ha class from it. watertank HA is shown imported as example in the code.

4. Modify the write_path variable to the absolute path of the location the generated XML file should
be written. This is typically a folder accessible to BlokIDE to load them.

5. cd ./src and run the compiler with Python using " Python2 HAIEC.py "

##Modifications

Some classes from the original repository have been modified for this work.

1. language.py - Added two new classes and a list of optional arguments to the Ha class
(see src/language.py for the modifications)

2. HA model files - Added extEves and extVars instances to help buid the Interface function blocks
(see the models in the examples folder and the report for the modification)

##Issues

Issues with BlokIDE might cause some && symbols to be improperly parsed and displayed with extra unnecessary parentheses. There are also restricitions in the naming of varaibles. See the issues section of the report for more details.
