# TODO: Still need to write the parser

import macropy.activate
from language import *
from gen import *
from sympy import *
import shac

# Example of an external signal declaration
signal_u = Symbol('signal_u')

# This the the single dimension in "x" example artificially paced cell
# without any value for f(lambda).

ode1 = Ode(S("diff(x(t))-1"), S("x(t)"), 0, {})
ode2 = Ode(S("diff(x(t))-1"), S("x(t)"), 0, {})
ode3 = Ode(S("diff(x(t))-1"), S("x(t)"), 0, {})
ode4 = Ode(S("diff(x(t))-1"), S("x(t)"), 0, {})

# The locations of the hybrid automaton
Rest = Loc("Rest", [ode1], [],
           {S("x(t)"): [Guard(S("x<=300"))]})
Cond = Loc("Cond", [ode2], [],
           {S("x(t)"): [Guard(S("x<= 10"))]})
ERP = Loc("ERP", [ode3], [],
          {S("x(t)"): [Guard(S("x<=200"))]})
RRP = Loc("RRP", [ode4], [],
          {S("x(t)"): [Guard(S("x<=100"))]})

# The edges
e1 = Edge('Rest', 'Cond', {S("x(t)"): [Guard(S("x>=300"))]},
          [Update.Update1(Symbol('x'), 0)],
          # reset x to zero
          [])
e2 = Edge('Rest', 'Cond', {S("x(t)"): [Guard(sympify("True"))]},
          # reset x to zero
          [Update.Update1(Symbol('x'), 0)],
          # ACTnode is an input
          [Event("ACTnode")])
e3 = Edge('RRP', 'Cond', {S("x(t)"): [Guard(sympify("True"))]},
          # reset x to zero
          [Update.Update1(Symbol('x'), 0)],
          # ACTnode is an input
          [Event("ACTnode")])

e4 = Edge('Cond', 'ERP', {S("x(t)"): [Guard(S("x>=10"))]},
          # reset x to zero
          [Update.Update1(Symbol('x'), 0)],
          # ACTnext is an output event
          [Event("ACTnext")])

e5 = Edge('ERP', 'RRP', {S("x(t)"): [Guard(S("x >= 200"))]},
          # reset x to zero
          [Update.Update1(Symbol('x'), 0)],
          # no events
          [])
e6 = Edge('RRP', 'Rest', {S("x(t)"): [Guard(S("x >= 100"))]},
          # reset x to zero
          [Update.Update1(Symbol('x'), 0)],
          # no events
          [])

cell1D = Ha("cell_TA", [Rest, Cond, ERP, RRP], Rest,
            [e1, e2, e3, e4, e5, e6], [], [signal_u])


# Compile
shac.compile(cell1D)
