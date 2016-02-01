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


signal_u=Symbol('signal_u')

# Burner for the watertank

ode0 = Ode(sympify("diff(y(t))"), sympify("y(t)"), 0, {})
ode1 = Ode(sympify("diff(y(t))-1"), sympify("y(t)"), 0, {})

# CHANGED : Added the external interface of the hybrid automaton

# Keys are the external events and the values are a list of external variables those events are associated with.
# First dictionary correponds to the input and the second to the output. 
extEves = ExternalEvents({ Event("TURNON") : [], Event("TURNOFF") : [] }, { Event("ON") : [], Event("OFF") : []})
# List of external variables. Fist list corresponds to the input and second to the output.
extVars =  ExternalVars([],[Symbol("x")])

# The locations of the hybrid automaton
b1 = Loc("b1", [ode0], [],
         {S("y(t)"): [Guard(S("y>=0")), Guard(S("y <= 0"))]})
b2 = Loc("b2", [ode1], [],
         {S("y(t)"): [Guard(S("y < 0.1"))]})
b3 = Loc("b3", [ode0], [],
         {S("y(t)"): [Guard(S("y>=0")), Guard(S("y <= 0"))]})
b4 = Loc("b4", [ode1], [],
         {S("y(t)"): [Guard(S("y < 0.1"))]})

# The edges
e1 = Edge('b1', 'b2', {S("y(t)"): [Guard(sympify("True"))]},
          [Update.Update2(Symbol('y'), Symbol('y'))],
          [Event("TURNON")])

e2 = Edge('b2', 'b3', {S("y(t)"): [Guard(S("y>= 0.1"))]},
          [Update.Update1(Symbol('y'), Symbol('0')),
           Update.Update1(Symbol('signal'), Symbol('1'))],
          [])

e3 = Edge('b3', 'b4', {S("y(t)"): [Guard(sympify("True"))]},
          [Update.Update2(Symbol('y'), Symbol('y'))],
          [Event("TURNOFF")])

e4 = Edge('b4', 'b1', {S("y(t)"): [Guard(S("y>= 0.1"))]},
          [Update.Update1(Symbol('y'), Symbol('0')),
           Update.Update1(Symbol('signal'), Symbol('0'))],
          [])

# CHANGED : Added extEves, extVars arguments
burner = Ha("burner", [b1, b2, b3, b4], b1,
               [e1, e2, e3, e4], [], [signal_u, Symbol('signal')], extEves, extVars)

# Compile
# shac.compile(burner)
