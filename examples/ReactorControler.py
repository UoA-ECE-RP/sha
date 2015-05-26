# The Reactor Plant example
# Taken from page 387 of Principles of Cyber-physical systems. - Rajeev Alur.
# See the inputvector described in reactorin.csv
# The environment interface is reactorIO.c


# TODO: Still need to write the parser

import macropy.activate
from language import *
from gen import *
from sympy import *
import shac

#Definition of the constant c (timer)
#c=10

# ODEs of the system

odey1 = Ode(sympify("diff(y1(t))-1"), sympify("y1(t)"), 10)
odey2 = Ode(sympify("diff(y2(t))-1"), sympify("y2(t)"), 10)

# The locations of the hybrid automaton
t0 = Loc("t0", [odey1,odey2], [],
         {S("x(t)"): [ Guard(S("x <= 550"))]})
t1 = Loc("t1", [odey1,odey2], [],
         {S("x(t)"): [Guard(S("x>=510"))]})
t2 = Loc("t2", [odey1,odey2], [],
         {S("x(t)"): [Guard(S("x>=510"))]})

# The edges
e1 = Edge('t0', 't1', {S("x(t)"): [Guard(S("x>=550"))],
                       S("y1(t)"): [Guard(S("y1>=10"))],
                       S("y2(t)"): [Guard(S("y2<10"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('y1'), Symbol('y1')),
           Update.Update2(Symbol('y2'), Symbol('y2'))],
          [Event("add1_control")])
e2 = Edge('t1', 't0', {S("x(t)"): [Guard(S("x<=510"))],
                       S("y1(t)"): [Guard(S("y1<=0")),
                                   Guard(S("y1>=0"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('y1'), Symbol('0')),
           Update.Update2(Symbol('y2'), Symbol('y2'))],
          [Event("remove1_control")])
e3 = Edge('t0', 't2', {S("x(t)"): [Guard(S("x>=550")),
                                   Guard(S("y2>=10"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('y1'), Symbol('y1')),
           Update.Update2(Symbol('y2'), Symbol('y2'))],
          [Event("add2_control")])
e4 = Edge('t2', 't0', {S("x(t)"): [Guard(S("x<=510")),
                                   Guard(S("y2<=0")),
                                   Guard(S("y2>=0")),]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('y1'), Symbol('y1')),
           Update.Update2(Symbol('y2'), Symbol('0'))],
          [Event("remove2_control")])


ReactorControler = Ha("ReactorControler", [t0, t1, t2], t0,
               [e1, e2, e3, e4])


# Compile
shac.compile(ReactorControler)
