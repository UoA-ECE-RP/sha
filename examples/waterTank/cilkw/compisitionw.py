 #!/usr/bin/python

import macropy.activate
from macropy.experimental.pattern import macros, switch, patterns

from languageNC1 import *


import controller
import wr

import shac
import pdb


halist=[]
blist = []
n = 10

# def haname(ha):
#   with patterns:
#     Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << ha
#     han = "watertank" + i

for i in range(n):
  # haname(wr.watertank)
  # with patterns:
  #   Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << ha
  #   han = "watertank" + str(i)
  watertank = Ha("watertank"+str(i), [wr.t1, wr.t2, wr.t3, wr.t4], wr.t4, [wr.e1, wr.e2, wr.e3, wr.e4, wr.e5, wr.e6], [], [], [], [], [externalOutputVars("x")], [externalInputEvent("ON"), externalInputEvent("OFF")], [])
  
  # if (watertank.InternalVar == 20){

  # }

  halist.append(watertank)


# halist = [watertank.watertank, burner.burner]
#print halist[0]
if (n > 0):
  for i in range(n):
    
    if (i != n -1):
      for m in range(i+1,n):
        # if not empty?
        bind11 = Bind.Bind1(halist[i].externalOutputVars, halist[m].externalInputVars)
        bind12 = Bind.Bind1(halist[m].externalOutputVars, halist[i].externalInputVars)
        bind21 = Bind.Bind2(halist[i].externalOutputEvent, halist[m].externalInputEvent)
        bind22 = Bind.Bind2(halist[m].externalOutputEvent, halist[i].externalInputEvent)
        # blist.append(BindHa(halist[i], bind11, halist[m]), BindHa(halist[m], bind12, halist[i]), BindHa(halist[i], bind21, halist[m]), BindHa(halist[m], bind22, halist[i]))
        blist.append(BindHa(halist[i], bind11, halist[m]))
        blist.append(BindHa(halist[m], bind12, halist[i]))
        blist.append(BindHa(halist[i], bind21, halist[m]))
        blist.append(BindHa(halist[m], bind22, halist[i]))



    elif (i == n-1):
      pass
    #   bind1 = Bind.Bind1(halist[i].externalOutputVars, halist[0].externalInputVars)
    #   bind2 = Bind.Bind2(halist[0].externalOutputEvent, halist[i].externalInputEvent)
    #   blist = [BindHa(halist[i], bind1, halist[0]), BindHa(halist[0], bind2, halist[i]]
    shac.compile(halist[i],ABOF=True,Q=True)

elif (n == 0):
  shac.compile(halist[0],ABOF=True,Q=True)
else:
  raise Exception("Error")

# bind1 = Bind.Bind1(burner.burner.externalOutputVars, watertank.watertank.externalInputVars)
# bind2 = Bind.Bind2(watertank.watertank.externalOutputEvent, burner.burner.externalInputEvent)
# blist = [BindHa(burner.burner, bind1, watertank.watertank), BindHa(watertank.watertank, bind2, burner.burner)]
  
# for i in range(n):
#   shac.compile(halist[i],ABOF=True,Q=True)

# shac.compile(controller.controller,ABOF=True,Q=True)
shac.compileMainF(halist, blist)

# shac.compile(watertank.watertank,ABOF=True,Q=True)
# shac.compile(controller.controller,ABOF=True,Q=True)
# shac.compileMainF(halist, blist)