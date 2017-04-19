# TODO: Still need to write the parser

import macropy.activate
from language import *
from gen import *
from sympy import *
import shac

PATHS_INFO = [["P1", "SA", "C1"]]
pathHAs = []
# Example of an external signal declaration
signal_u = Symbol('signal_u')

# This the the single dimension in "x" example artificially paced cell
# without any value for f(lambda).

ode1 = Ode(S("diff(x(t))"), S("x(t)"), 0, {})
ode2 = Ode(S("diff(x(t))-1"), S("x(t)"), 0, {})
ode3 = Ode(S("diff(x(t))-1"), S("x(t)"), 0, {})

# The locations of the hybrid automaton
Idle = Loc("Idle", [ode1], [],
           {S("x(t)"): [Guard(sympify("True"))]})
ActA = Loc("ActA", [ode2], [],
           {S("x(t)"): [Guard(S("x<= 20"))]})
ActB = Loc("ActB", [ode3], [],
           {S("x(t)"): [Guard(S("x<= 25"))]})

for p in PATHS_INFO:
    id = p[0]
    A = p[1]
    B = p[2]
    # The edges
    e1 = Edge('Idle', 'ActA', {S("x(t)"): [Guard(sympify("True"))]},
              [Update.Update1(Symbol('x'), 0)],
              # reset x to zero
              [Event("ACTnext_"+B)])
    e2 = Edge('Idle', 'ActB', {S("x(t)"): [Guard(sympify("True"))]},
              [Update.Update1(Symbol('x'), 0)],
              # reset x to zero
              [Event("ACTnext_"+A)])

    e3 = Edge('ActA', 'Idle', {S("x(t)"): [Guard(S("x>=20"))]},
              # reset x to zero
              [Update.Update1(Symbol('x'), 0)],
              [Event("ACTnext_"+A)])
    e4 = Edge('ActA', 'Idle', {S("x(t)"): [Guard(sympify("True"))]},
              # reset x to zero
              [Update.Update1(Symbol('x'), 0)],
              [Event("ACTnext_"+A)])

    e5 = Edge('ActB', 'Idle', {S("x(t)"): [Guard(S("x>=25"))]},
              # reset x to zero
              [Update.Update1(Symbol('x'), 0)],
              [Event("ACTnode_"+B)])
    e6 = Edge('ActB', 'Idle', {S("x(t)"): [Guard(sympify("True"))]},
              # reset x to zero
              [Update.Update1(Symbol('x'), 0)],
              [Event("ACTnext_"+B)])

    pathHA = Ha("path_"+id, [Idle, ActA, ActB], Idle,
                [e1, e2, e3, e4, e5, e6], [], [signal_u])

    pathHAs.append(pathHA)
# Compile
#shac.compile(path)
