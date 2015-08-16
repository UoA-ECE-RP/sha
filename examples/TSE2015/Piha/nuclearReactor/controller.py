# The Reactor Plant example
# Taken from page 387 of Principles of Cyber-physical systems. - Rajeev Alur.


# TODO: Still need to write the parser

import macropy.activate
from language import *
from gen import *
from sympy import *
import shac

signal_u=Symbol('signal_u')

#Definition of the constant c (timer)
#c=10

# ODEs of the system

odety1 = Ode(sympify("diff(ty1(t))-1"), sympify("ty1(t)"), 10, {})
odety2 = Ode(sympify("diff(ty2(t))-1"), sympify("ty2(t)"), 10, {})

# The locations of the hybrid automaton
t0 = Loc("t0", [odety1,odety2], [],
         {S("x(t)"): [ Guard(S("x < 550"))],
          S("ty1(t)"): [ Guard(S("ty1 <= 100000"))],
          S("ty2(t)"): [ Guard(S("ty2 <= 100000"))]})
t1 = Loc("t1", [odety1,odety2], [],
         {S("x(t)"): [Guard(S("x>510"))],
          S("ty1(t)"): [ Guard(S("ty1 <= 100000"))],
          S("ty2(t)"): [ Guard(S("ty2 <= 100000"))]})
t2 = Loc("t2", [odety1,odety2], [],
         {S("x(t)"): [Guard(S("x>510"))],
          S("ty1(t)"): [ Guard(S("ty1 <= 100000"))],
          S("ty2(t)"): [ Guard(S("ty2 <= 100000"))]})

# The edges
e1 = Edge('t0', 't1', {S("x(t)"): [Guard(S("x>=550"))],
                       S("ty1(t)"): [Guard(S("ty1>=10"))],
                       S("ty2(t)"): [Guard(S("ty2<10"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('ty1'), Symbol('ty1')),
           Update.Update2(Symbol('ty2'), Symbol('ty2')),
           Update.Update1(Symbol('signal'), Symbol('1'))],
          [])
e2 = Edge('t1', 't0', {S("x(t)"): [Guard(S("x<=510"))],
                                   },
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update1(Symbol('ty1'), Symbol('0')),
           Update.Update2(Symbol('ty2'), Symbol('ty2')),
           Update.Update1(Symbol('signal'), Symbol('0.1'))],
          [])
e3 = Edge('t0', 't2', {S("x(t)"): [Guard(S("x>=550")),],
                       S("ty2(t)"): [Guard(S("ty2>=10"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('ty1'), Symbol('ty1')),
           Update.Update2(Symbol('ty2'), Symbol('ty2')),
           Update.Update1(Symbol('signal'), Symbol('2'))],
          [])
e4 = Edge('t2', 't0', {S("x(t)"): [Guard(S("x<=510"))],
                                    },
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('ty1'), Symbol('ty1')),
           Update.Update1(Symbol('ty2'), Symbol('0')),
           Update.Update1(Symbol('signal'), Symbol('0.2'))],
          [])


controller = Ha("controller", [t0, t1, t2], t0,
               [e1, e2, e3, e4],[],[signal_u])


# Compile
#shac.compile(ReactorControler)
