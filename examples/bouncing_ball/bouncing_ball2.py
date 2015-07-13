from __future__ import division
import macropy.activate
from language import *
from gen import *
from sympy import *
import shac


ode_v1 = Ode(sympify("diff(v(t))+9.81"),
             sympify("v(t)"), 10.001, {})

ode_h1 = Ode(sympify("diff(h(t))-v(t)"),
             sympify("h(t)"), 100, {S('v(t)'): ode_v1})


# The locations of the hybrid automaton
t1 = Loc("t1", [ode_v1, ode_h1], [],
         {S('h(t)'): [Guard(S('h>0'))],
          S('v(t)'): [Guard(True)]})


# The edges
e1 = Edge('t1', 't1', {S("v(t)"): [Guard(S("h>=0")),
                                   Guard(S("h<=0")),
                                   Guard(S("v<=0"))]},
          [Update.Update2(Symbol('h'), Symbol('h+0.001')),
           Update.Update2(Symbol('v'), Symbol('-0.5*v'))],
          [])

bouncing_ball2 = Ha("bouncing_ball2", [t1], t1, [e1], [], [])


# Compile
shac.compile(bouncing_ball2, ABOF=True)