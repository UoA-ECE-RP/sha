# The Billard ball example
# Taken from page 385 of Principles of Cyber-physical systems. - Rajeev Alur.
# See the inputvector described in billardBallin.csv
# The environment interface is billardBallIO.c


# TODO: Still need to write the parser

import macropy.activate
from language import *
from gen import *
from sympy import *
import shac

# x_i = 5, y_i=5
# theta = 30 degrees -> Kc = 0.866 and Ks=0.500
# length l = 33, b = 10
# Initaial velocity = 1

# ODEs of the system

ode0x =  Ode(sympify("diff(x(t))"), sympify("x(t)"), 5) #intial location of the ball is (5,5)
ode0y =  Ode(sympify("diff(y(t))"), sympify("y(t)"), 5)
ode1x =  Ode(sympify("diff(x(t))-0.866*x(t)+0"), sympify("x(t)"), 0)
ode1y =  Ode(sympify("diff(y(t))-0.500*y(t)+0"), sympify("y(t)"), 0) #initalisation to zero does not make sense
ode2x =  Ode(sympify("diff(x(t))-0.866*x(t)+0"), sympify("x(t)"), 0)
ode2y =  Ode(sympify("diff(y(t))+0.500*y(t)+0"), sympify("y(t)"), 0)
ode3x =  Ode(sympify("diff(x(t))+0.866*x(t)+0"), sympify("x(t)"), 0)
ode3y =  Ode(sympify("diff(y(t))+0.500*y(t)+0"), sympify("y(t)"), 0)
ode4x =  Ode(sympify("diff(x(t))+0.866*x(t)+0"), sympify("x(t)"), 0)
ode4y =  Ode(sympify("diff(y(t))-0.500*y(t)+0"), sympify("y(t)"), 0)

# The locations of the hybrid automaton
t0 = Loc("t0", [ode0x,ode0y], [],
         {S("x(t)"): [ Guard(S("x >= 0")),
                       Guard(S("x <= 33")) ],
          S("y(t)"):[  Guard(S("y >= 0")),
                       Guard(S("y <= 10")) ]
          })
t1 = Loc("t1", [ode1x,ode1y], [],
         {S("y(t)"): [ Guard(S("y < 10"))  ]})
t2 = Loc("t2", [ode2x,ode2y], [],
         {S("x(t)"): [ Guard(S("x < 33"))  ]})
t3 = Loc("t3", [ode3x,ode3y], [],
         {S("y(t)"): [ Guard(S("y > 0"))  ]})
t4 = Loc("t4", [ode4x,ode4y], [],
         {S("x(t)"): [ Guard(S("x > 0"))  ]})


# The edges
e1 = Edge('t0', 't1', {S("x(t)"): [Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('y'), Symbol('y'))],
          [Event("shot")])
e2 = Edge('t1', 't2', {S("x(t)"): [Guard(S("y>=10"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
          Update.Update2(Symbol('y'), Symbol('y'))],
          [Event("valid")])
e3 = Edge('t2', 't3', {S("x(t)"): [Guard(S("x>=33"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
          Update.Update2(Symbol('y'), Symbol('y'))],
          [Event("valid")])
e4 = Edge('t3', 't4', {S("x(t)"): [Guard(S("y<=0"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
          Update.Update2(Symbol('y'), Symbol('y'))],
          [Event("valid")])
e5 = Edge('t4', 't1', {S("x(t)"): [Guard(S("x<=0"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
          Update.Update2(Symbol('y'), Symbol('y'))],
          [Event("valid")])
e6 = Edge('t1', 't4', {S("x(t)"): [Guard(S("x>=33"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
          Update.Update2(Symbol('y'), Symbol('y'))],
          [Event("valid")])
e7 = Edge('t4', 't3', {S("x(t)"): [Guard(S("y>=10"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
          Update.Update2(Symbol('y'), Symbol('y'))],
          [Event("valid")])
e8 = Edge('t3', 't2', {S("x(t)"): [Guard(S("x<=0"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
          Update.Update2(Symbol('y'), Symbol('y'))],
          [Event("valid")])
e9 = Edge('t2', 't1', {S("x(t)"): [Guard(S("y<=0"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
          Update.Update2(Symbol('y'), Symbol('y'))],
          [Event("valid")])
          


billardBall= Ha("billardBall", [t0, t1, t2,t3,t4], t0,
               [e1, e2, e3, e4, e5, e6, e7, e8, e9])


# Compile
shac.compile(billardBall)
