# The water-tank example coded in Python

# TODO: Still need to write the parser

import macropy.activate
from language import *
from gen import *
from sympy import *
import shac


# This the the single dimension in "x" example artificially paced cell
# without any value for f(lambda).

ode1 = Ode(S("diff(x(t))+0.1*x(t)"), S("x(t)"), 0.0001, {})
ode2 = Ode(S("diff(x(t))-800"), S("x(t)"), 20, {})
ode3 = Ode(S("diff(x(t))-200.0*x(t)"), S("x(t)"), 20, {})
ode4 = Ode(S("diff(x(t))+0.002*x(t)"), S("x(t)"), 138, {})

# The locations of the hybrid automaton
t1 = Loc("t1", [ode1], [],
         {S("x(t)"): [Guard(S("x<=20"))]})
t2 = Loc("t2", [ode2], [],
         {S("x(t)"): [Guard(S("x < 20"))]})
t3 = Loc("t3", [ode3], [],
         {S("x(t)"): [Guard(S("x>=20")), Guard(S("x < 138"))]})
t4 = Loc("t4", [ode4], [],
         {S("x(t)"): [Guard(S("x>20")), Guard(S("x <= 138"))]})

# The edges
e1 = Edge('t1', 't2', {S("x(t)"): [Guard(S("x < 20"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("VS")])
e2 = Edge('t2', 't1', {S("x(t)"): [Guard(S("x < 20"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("VSP")])
e3 = Edge('t2', 't3', {S("x(t)"): [Guard(S("x <= 20")),
                                   Guard(S("x >= 20"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [])
e4 = Edge('t3', 't4', {S("x(t)"): [Guard(S("x <= 138")),
                                   Guard(S("x >= 138"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [])
e5 = Edge('t4', 't1', {S("x(t)"): [Guard(S("x <= 20")),
                                   Guard(S("x >= 20"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [])

cell1D = Ha("cell1D", [t1, t2, t3, t4], t1,
            [e1, e2, e3, e4, e5], [], [])


# Compile
shac.compile(cell1D)
