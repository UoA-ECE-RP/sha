# The water-tank example coded in Python

'''
*No need to include any internal events as the resulting IEC-61499 has nothing such defined.
*Supply the initial state as the first element in the list of locations to the Ha class. This eliminates the need to 
have additional isInitial flags.
*Do not duplicate any event name or variable name (internal, output or input) as BlokIDE at this point does not 
permit identically named elements and won't load the file. The variable the ODE is in (the internal variable) is declared 
by the compiler automatically. Abstain from using the same ODE variable elsewhere. This issue needs to be fixed.
'''

import macropy.activate
from language import *
from gen import *
from sympy import *
import shac

# This is the Raskin model of the waterTank example
# K = 0.075 heating rate in t4, h = 150.

ode1 = Ode(sympify("diff(x(t))-(0.075*(150-x(t)))"), sympify("x(t)"), 20, {})
ode2 = Ode(sympify("diff(x(t))"), sympify("x(t)"), 100, {})
ode3 = Ode(sympify("diff(x(t))+(0.075*x(t))"), sympify("x(t)"), 100, {})
ode4 = Ode(sympify("diff(x(t))"), sympify("x(t)"), 20, {})

# CHANGED : Added the external interface of the hybrid automaton

# Keys are the external events and the values are a list of external variables those events are associated with.
# First dictionary correponds to the input and the second to the output. 
extEves = ExternalEvents({ Event("ON") : [], Event("OFF") : [] }, {})
# List of external variables. Fist list corresponds to the input and second to the output.
extVars =  ExternalVars([],[Symbol("y")])

# The locations of the hybrid automaton
t1 = Loc("t1", [ode1], [],
         {S("x(t)"): [Guard(S("x>=20")), Guard(S("x <= 100"))]})
t2 = Loc("t2", [ode2], [],
         {S("x(t)"): [Guard(S("x>=100")), Guard(S("x <= 100"))]})
t3 = Loc("t3", [ode3], [],
         {S("x(t)"): [Guard(S("x>=20")), Guard(S("x <= 100"))]})
t4 = Loc("t4", [ode4], [],
         {S("x(t)"): [Guard(S("x>=20")), Guard(S("x <= 20"))]})

e1 = Edge('t1', 't2', {S("x(t)"): [Guard(S("x>=100")),
                                   Guard(S("x <= 100"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [])
e2 = Edge('t2', 't3', {S("x(t)"): [Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("OFF")])
e3 = Edge('t1', 't3', {S("x(t)"): [Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("OFF")])
e4 = Edge('t3', 't1', {S("x(t)"): [Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("ON")])
e5 = Edge('t3', 't4', {S("x(t)"): [Guard(S("x>=20")),
                                   Guard(S("x <= 20"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [])
e6 = Edge('t4', 't1', {S("x(t)"): [Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("ON")])

# CHANGED : Added extEves, extVars arguments
waterTank = Ha("watertankR", [t1, t2, t3, t4], t4,
               [e1, e2, e3, e4, e5, e6], [], [], extEves, extVars)

#shac.compile(waterTank)
