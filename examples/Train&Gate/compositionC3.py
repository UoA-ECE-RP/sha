#!/usr/bin/python

import macropy.activate
from macropy.experimental.pattern import macros, switch, patterns
from languageC1 import *


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

def comp():
	print train.train.externalOutputVars, train.train.externalInputVars
	print gate.gate.externalOutputVars, gate.gate.externalInputVars

	#bind1 = Bind.Bind1(train.train.externalOutputVars, gate.gate.externalInputVars)
	bind1 = Bind.Bind1(gate.gate.externalOutputVars, train.train.externalInputVars)
	bind2 = Bind.Bind2(train.train.externalOutputEvent, gate.gate.externalInputEvent)
	blist = [BindHa(gate.gate, bind1, train.train), BindHa(train.train, bind2, gate.gate)]

	link1 = zip(gate.gate.externalOutputVars, train.train.externalInputVars)
	link2 = zip(train.train.externalOutputEvent, gate.gate.externalInputEvent)
	'''
	with switch(hh):
		if Ha(name, locations, startLocation, edges, globalVars, igvs, internalVars, mm, eov, eine, nn):
			print "NNN"
		else:
			print "Screwed"
	with patterns:
		Ha(name, locations, startLocation, edges, globalVars, igvs, internalVars, eiv, xx, yy, eoe) << train.train
		bind1 = Bind.Bind1(eov, eiv)
		bind2 = Bind.Bind2(eoe, eine)
		blist = [BindHa(gate.gate, [Bind1], train.train), BindHa(train.train, [bind2], gate.gate)]

		link1 = zip(eov, eiv)
		link2 = zip(eoe, eine)
	'''
	print "sth"
	
comp()
shac.compile(train.train,ABOF=True,Q=True)
shac.compile(gate.gate,ABOF=True,Q=True)
shac.compileMainF(halist)

