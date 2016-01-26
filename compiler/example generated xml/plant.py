# The Reactor Plant example
# Taken from page 387 of Principles of Cyber-physical systems. - Rajeev Alur.


# TODO: Still need to write the parser

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
extEves = ExternalEvents({ Event("add1") : [], Event("add2") : [], Event("remove1"):[], Event("remove2"):[] }, { Event("update") : [Symbol("x")]})

extVars =  ExternalVars([],[Symbol("x")])

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


plant = Ha("plant", [t0, t1, t2], t0,
               [e1, e2, e3, e4],[],[], extEves, extVars)


# Compile
#shac.compile(ReactorPlant)
