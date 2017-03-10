# The water-tank example coded in Python

# TODO: Still need to write the parser

import macropy.activate
from language import *
from gen import *
from sympy import *
import shac

# SwitchTank From http://robotics.eecs.berkeley.edu/~sastry/ee291e/lygeros.pdf
# w=1 ; v1=0.3 ; v2 = 0.5
# Max height of a tank : 1. At the beginning, both tanks are half full
# r1 = r2 = 0.25
# To have a WHA, replace maximum height (whch is 1) by 0.75 and set v1=v2=0.5
# Don't forget then to erase ABOF=True in the compile command

ode_x1f = Ode(sympify("diff(x1(t))+0.3-1"), sympify("x1(t)"), 0.5, {})
ode_x1e = Ode(sympify("diff(x1(t))+0.3"), sympify("x1(t)"), 0.5, {})

ode_x2f = Ode(sympify("diff(x2(t))+0.4-1"), sympify("x2(t)"), 0.5, {})
ode_x2e = Ode(sympify("diff(x2(t))+0.4"), sympify("x2(t)"), 0.5, {})

# The locations of the hybrid automaton
t1 = Loc("t1", [ode_x1f, ode_x2e], [],
         {S("x1(t)"): [Guard(S("x1<=1"))], S("x2(t)"): [Guard(S("x2>0.25"))]})
t2 = Loc("t2", [ode_x1e, ode_x2f], [],
         {S("x1(t)"): [Guard(S("x1>0.25"))], S("x2(t)"): [Guard(S("x2<=1"))]})


# The edges
e1 = Edge('t1', 't2', {S("x2(t)"): [Guard(S("x2<=0.25"))]},
          [Update.Update2(Symbol('x1'), Symbol('x1')),
           Update.Update2(Symbol('x2'), Symbol('x2'))],
          [])

e2 = Edge('t2', 't1', {S("x1(t)"): [Guard(S("x1<=0.25"))]},
          [Update.Update2(Symbol('x1'), Symbol('x1')),
          Update.Update2(Symbol('x2'), Symbol('x2'))],
          [])


SwitchTank = Ha("SwitchTank", [t1, t2], t1,
                [e1, e2], [], [])

# Compile
shac.compile(SwitchTank, ABOF=True)
