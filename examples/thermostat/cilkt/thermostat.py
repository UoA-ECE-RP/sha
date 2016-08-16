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

# This is the Raskin model of the thermostat example
# K = 0.075 heating rate in t4, h = 150.

ode1 = Ode(sympify("diff(x(t))+x(t)-10"), S("x(t)"), 22.78, {})
ode2 = Ode(sympify("diff(x(t))+x(t)-37.78"), S("x(t)"), 22.78, {})


# The locations of the hybrid automaton
t1 = Loc("t1", [ode1], [],
         {S("x(t)"): [Guard(S("x>22.78"))]})
t2 = Loc("t2", [ode2], [],
         {S("x(t)"): [Guard(S("x<25"))]})


# The edges
e1 = Edge('t1', 't2', {S("x(t)"): [Guard(S("x<=22.78")),
                                   ]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [])
e2 = Edge('t2', 't1', {S("x(t)"): [Guard(S("x>=25"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [])


# thermostat = Ha("thermostat", [t1, t2], t2,
#                [e1, e2], [], [])

# Compile
#shac.compile(thermostat)

#shac.compile(thermostat,ABOF=True,Q=True)

