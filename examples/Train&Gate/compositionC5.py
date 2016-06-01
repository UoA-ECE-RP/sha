#!/usr/bin/python

import macropy.activate
from macropy.experimental.pattern import macros, switch, patterns
print "i hha"
#from languageC1 import *
from languageNC1 import *


#print "ccc"

#print "bbb"

#import shac
import train
import gate
#print "ddd"

#from genChanged2 import *
#print "fff"
import shac
import pdb

halist = [train.train, gate.gate]
#print halist[0]
bind1 = Bind.Bind1(gate.gate.externalOutputVars, train.train.externalInputVars)
bind2 = Bind.Bind2(train.train.externalOutputEvent, gate.gate.externalInputEvent)
blist = [BindHa(gate.gate, bind1, train.train), BindHa(train.train, bind2, gate.gate)]
	

shac.compile(train.train,ABOF=True,Q=True)
shac.compile(gate.gate,ABOF=True,Q=True)
shac.compileMainF(halist, blist)

