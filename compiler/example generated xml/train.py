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

ode_y  = Ode(sympify("diff(y(t))-1"), sympify("y(t)"), 0, {})

# CHANGED : Added the external interface of the hybrid automaton 

# Keys are the external events and the values are a list of external variables those events are associated with.
# First dictionary correponds to the input and the second to the output. 
extEves = ExternalEvents({}, {})
# List of external variables. Fist list corresponds to the input and second to the output.
extVars =  ExternalVars([Symbol("x")],[Symbol("z")])

# The locations of the hybrid automaton
t1 = Loc("t1", [ode_y], [],
         {S('y(t)'): [Guard(S('y<5'))]})

t2 = Loc("t2", [ode_y], [],
         {S('y(t)'): [Guard(S('y>=5')), 
                      Guard(S('y<15'))]})

t3 = Loc("t3", [ode_y], [],
         {S('y(t)'): [Guard(S('y>=15')), 
                      Guard(S('y<25'))]})


# The edges
e1 = Edge('t1', 't2', {S("x(t)"): [Guard(S("y>=5")),
                                   Guard(S("y<=5"))]},
          [Update.Update2(Symbol('y'), Symbol('y')),
           Update.Update1(Symbol('signal'), Symbol('1'))],
          [])

e2 = Edge('t2', 't3', {S("x(t)"): [Guard(S("y>=15")),
                                   Guard(S("y<=15"))]},
          [Update.Update2(Symbol('y'), Symbol('y')),
           Update.Update1(Symbol('signal'), Symbol('0'))],
          [])

e3 = Edge('t3', 't1', {S("x(t)"): [Guard(S("y>=25")),
                                   Guard(S("y<=25"))]},
          [Update.Update1(Symbol('y'), Symbol('0'))],
          [])

# CHANGED : Added extEves, extVars arguments
train = Ha("train", [t1, t2, t3], t1, [e1, e2, e3], [Symbol("signal")], [], extEves, extVars)


# Compile
# shac.compile(train)