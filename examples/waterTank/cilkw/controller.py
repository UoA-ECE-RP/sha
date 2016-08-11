# The water-tank example coded in Python

# TODO: Still need to write the parser

# import macropy.activate
# from language import *
# from gen import *
# from sympy import *
# import shac


import macropy.activate
from languageNC1 import *
from genChanged3 import *
from sympy import *
import shac
import wr


# This is the Raskin model of the waterTank example
# K = 0.075 heating rate in t4, h = 150.


# The locations of the hybrid automaton
t1 = Loc("t1", [], [],
         {S("x(t)"): [Guard(S("x>=20")), Guard(S("x <= 100"))]})
t2 = Loc("t2", [], [],
         {S("x(t)"): [Guard(S("x>=20")), Guard(S("x <= 100"))]})


# The edges
e1 = Edge('t1', 't2', {S("x(t)"): [Guard(S("x>=100")),
                                   Guard(S("x <= 100"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
            Update.Update1(Symbol('ON'), Symbol('1'),
              Update.Update1(Symbol('OFF'),Symbol('0')])

e1 = Edge('t1', 't2', {S("x(t)"): [Guard(S("x>=20")),
                                   Guard(S("x <= 20"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
            Update.Update1(Symbol('OFF'),Symbol('1'),
              Update.Update1(Symbol('ON'),Symbol('0')])


# waterTank = Ha("watertankR", [t1, t2, t3, t4], t4,
#                [e1, e2, e3, e4, e5, e6], [], [])
# watertank = Ha("watertank", [t1, t2, t3, t4], t4, [e1, e2, e3,e4, e5, e6], [], [], [InternalVar("x")], [], [], [], [])
controller = Ha("controller", [t1, t2], t4, [e1, e2], [], [], [], [externalInputVars("x")], [], [], [externalOutputEvent("ON"), externalOutputEvent("OFF")])

# Compile
# shac.compile(waterTank,ABOF=True,Q=True)
