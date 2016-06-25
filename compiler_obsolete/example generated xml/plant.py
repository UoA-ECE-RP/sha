'''
*No need to include any internal events as the resulting IEC-61499 has nothing such defined.
*Supply the initial state as the first element in the list of locations to the Ha class. This eliminates the need to 
have additional isInitial flags.
*Do not duplicate any event name or variable name (internal, output or input) as BlokIDE at this point does not 
permit identically named elements and won't load the file. The variable the ODE is in (the internal variable) is declared 
by the compiler automatically. Abstain from using the same ODE variable elsewhere. This issue needs to be fixed.
'''

# The Reactor Plant example
# Taken from page 387 of Principles of Cyber-physical systems. - Rajeev Alur.

import macropy.activate
from language import *
from gen import *
from sympy import *
import shac


# ODEs of the system

ode0 = Ode(sympify("diff(x(t))-0.1*x(t)+50"), sympify("x(t)"), 510, {})
ode1 = Ode(sympify("diff(x(t))-0.1*x(t)+56"), sympify("x(t)"), 550, {})
ode2 = Ode(sympify("diff(x(t))-0.1*x(t)+60"), sympify("x(t)"), 550, {})

# CHANGED : Added the external interface of the hybrid automaton 

# Keys are the external events and the values are a list of external variables those events are associated with.
# First dictionary correponds to the input and the second to the output. 
extEves = ExternalEvents({ Event("add1") : [], Event("add2") : [], Event("remove1"):[], Event("remove2"):[] }, { Event("update") : [Symbol("x")]})
# List of external variables. Fist list corresponds to the input and second to the output.
extVars =  ExternalVars([],[Symbol("y")])

# The locations of the hybrid automaton
t0 = Loc("t0", [ode0], [],
         {S("x(t)"): [Guard(sympify("True"))]})
t1 = Loc("t1", [ode1], [],
         {S("x(t)"): [Guard(sympify("True"))]})
t2 = Loc("t2", [ode2], [],
         {S("x(t)"): [Guard(sympify("True"))]})

# The edges
e1 = Edge('t0', 't1', {S("x(t)"):[Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("add1")])
e2 = Edge('t1', 't0', {S("x(t)"):[Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("remove1")])
e3 = Edge('t0', 't2', {S("x(t)"):[Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("add2")])
e4 = Edge('t2', 't0', {S("x(t)"):[Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("remove2")])

# CHANGED : Added extEves, extVars arguments
plant = Ha("plant", [t0, t1, t2], t0,
               [e1, e2, e3, e4],[],[], extEves, extVars)


# Compile
#shac.compile(ReactorPlant)
