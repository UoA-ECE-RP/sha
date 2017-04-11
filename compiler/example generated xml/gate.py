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

#Train and Gate from 
# http://www.eecs.tufts.edu/~khan/Courses/Spring2013/EE194/Lecs/Hybrid_Systems_Presentation_Elliott_Costello.pdf

ode_x_down = Ode(sympify("diff(x(t))-(0-x(t))/2"), sympify("x(t)"), 10, {})
ode_x_up = Ode(sympify("diff(x(t))-(11-x(t))/2"), sympify("x(t)"), 1, {})

# CHANGED : Added the external interface of the hybrid automaton 

# Keys are the external events and the values are a list of external variables those events are associated with.
# First dictionary correponds to the input and the second to the output. 
extEves = ExternalEvents({ Event("UP") : [], Event("DOWN") : [] }, {})
# List of external variables. Fist list corresponds to the input and second to the output.
extVars =  ExternalVars([],[Symbol("y")])

# The locations of the hybrid automaton
t1 = Loc("t1", [ode_x_down],[],
         {S("x(t)"): [Guard(S("x>=1")), Guard(S("x <= 10"))]})

t2 = Loc("t2", [ode_x_up],[],
         {S("x(t)"): [Guard(S("x>=1")), Guard(S("x <= 10"))]})


# The edges
e1 = Edge('t1', 't2', {S("x(t)"): [Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("UP")])
e2 = Edge('t2', 't1', {S("x(t)"): [Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("DOWN")])


# CHANGED : Added extEves, extVars arguments
gate = Ha("gate", [t1, t2], t2, [e1, e2], [], [], extEves, extVars)


# Compile
# shac.compile(gate)
