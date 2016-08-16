#!/usr/bin/python

import macropy.activate
from macropy.experimental.pattern import macros, switch, patterns

from languageNC1 import *

import thermostat

import shac
import pdb


halist=[]
blist = []
n = 3081


for i in range(n):

  th = Ha("th"+str(i), [thermostat.t1, thermostat.t2], thermostat.t2, [thermostat.e1, thermostat.e2], [], [], [InternalVar("x")], [], [], [], [])
  

  halist.append(th)


if (n > 0):
  for i in range(n):
    
    # if (i != n -1):
    #   for m in range(i+1,n):
        # if not empty?
        # bind11 = Bind.Bind1(halist[i].externalOutputVars, halist[m].externalInputVars)
        # bind12 = Bind.Bind1(halist[m].externalOutputVars, halist[i].externalInputVars)
        # bind21 = Bind.Bind2(halist[i].externalOutputEvent, halist[m].externalInputEvent)
        # bind22 = Bind.Bind2(halist[m].externalOutputEvent, halist[i].externalInputEvent)

    # bind1 = Bind.Bind1(halist[i].externalOutputVars, halist[0].externalInputVars)
    
    # bind2 = Bind.Bind2(halist[0].externalOutputEvent, halist[i].externalInputEvent)
   
        
        # blist.append(BindHa(halist[i], bind11, halist[m]))
        # blist.append(BindHa(halist[m], bind12, halist[i]))
        # blist.append(BindHa(halist[i], bind21, halist[m]))
        # blist.append(BindHa(halist[m], bind22, halist[i]))

    # blist.append(BindHa(halist[i], bind1, halist[0]))
    
    # blist.append(BindHa(halist[0], bind2, halist[i]))
    


    # elif (i == n-1):
    #   pass
    #   bind1 = Bind.Bind1(halist[i].externalOutputVars, halist[0].externalInputVars)
    #   bind2 = Bind.Bind2(halist[0].externalOutputEvent, halist[i].externalInputEvent)
    #   blist = [BindHa(halist[i], bind1, halist[0]), BindHa(halist[0], bind2, halist[i]]
    shac.compile(halist[i],ABOF=True,Q=True)

# elif (n == 0):
#   shac.compile(halist[0],ABOF=True,Q=True)
else:
  raise Exception("Error")

# bind1 = Bind.Bind1(burner.burner.externalOutputVars, watertank.watertank.externalInputVars)
# bind2 = Bind.Bind2(watertank.watertank.externalOutputEvent, burner.burner.externalInputEvent)
# blist = [BindHa(burner.burner, bind1, watertank.watertank), BindHa(watertank.watertank, bind2, burner.burner)]
  
# for i in range(n):
#   shac.compile(halist[i],ABOF=True,Q=True)

# shac.compile(controller.controller,ABOF=True,Q=True)
# halist=[controller.controller]
# shac.compile(halist[0],ABOF=True,Q=True)
shac.compileMainF(halist, blist)

# shac.compile(watertank.watertank,ABOF=True,Q=True)
# shac.compile(controller.controller,ABOF=True,Q=True)
# shac.compileMainF(halist, blist)