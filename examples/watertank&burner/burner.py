import macropy.activate
from language import *
from gen import *
from sympy import *
import shac

signal_u=Symbol('signal_u')

# Burner for the watertank

ode0 = Ode(sympify("diff(y(t))"), sympify("y(t)"), 0, {})
ode1 = Ode(sympify("diff(y(t))-1"), sympify("y(t)"), 0, {})


# The locations of the hybrid automaton
b1 = Loc("b1", [ode0], [],
         {S("y(t)"): [Guard(S("y>=0")), Guard(S("y <= 0"))]})
b2 = Loc("b2", [ode1], [],
         {S("y(t)"): [Guard(S("y < 0.1"))]})
b3 = Loc("b3", [ode0], [],
         {S("y(t)"): [Guard(S("y>=0")), Guard(S("y <= 0"))]})
b4 = Loc("b4", [ode1], [],
         {S("y(t)"): [Guard(S("y < 0.1"))]})

# The edges
e1 = Edge('b1', 'b2', {S("y(t)"): [Guard(sympify("True"))]},
          [Update.Update1(Symbol('y'), Symbol('y'))],
          [Event("TURN_ON")])

e2 = Edge('b2', 'b3', {S("y(t)"): [Guard(S("y>= 0.1"))]},
          [Update.Update1(Symbol('y'), Symbol('0')),
           Update.Update1(Symbol('signal'), Symbol('1'))],
          [])

e3 = Edge('b3', 'b4', {S("y(t)"): [Guard(sympify("True"))]},
          [Update.Update1(Symbol('y'), Symbol('y'))],
          [Event("TURN_OFF")])

e4 = Edge('b4', 'b1', {S("y(t)"): [Guard(S("y>= 0.1"))]},
          [Update.Update1(Symbol('y'), Symbol('0')),
           Update.Update1(Symbol('signal'), Symbol('0'))],
          [])


burner = Ha("burner", [b1, b2, b3, b4], b1,
               [e1, e2, e3, e4], [], [signal_u])

# Compile
#shac.compile(burner)
