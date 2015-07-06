import macropy.activate
from language import *
from gen import *
from sympy import *
import shac


# This the the three dimensional artificially paced cell without any
# value for f(lambda).

ode1x = Ode(S("diff(x(t))+0.1*x(t)"), S("x(t)"), 0.0001)
ode1y = Ode(S("diff(y(t))+0.1*y(t)"), S("y(t)"), 0.0001)
ode1z = Ode(S("diff(z(t))+0.1*z(t)"), S("z(t)"), 0.0001)

ode2x = Ode(S("diff(x(t))-800"), S("x(t)"), None)
ode2y = Ode(S("diff(y(t))-0.05"), S("y(t)"), None)
ode2z = Ode(S("diff(z(t))-0.3"), S("z(t)"), None)

ode3x = Ode(S("diff(x(t))-200.0*x(t)"), S("x(t)"), None)
ode3y = Ode(S("diff(y(t))"), S("y(t)"), None)
ode3z = Ode(S("diff(z(t))-100.0*z(t)"), S("z(t)"), None)

ode4x = Ode(S("diff(x(t))+0.002*x(t)"), S("x(t)"), None)
ode4y = Ode(S("diff(y(t))+0.036*y(t)"), S("y(t)"), None)
ode4z = Ode(S("diff(z(t))+0.008*z(t)"), S("z(t)"), None)

# The locations of the hybrid automaton
t1 = Loc("t1", [ode1x, ode1y, ode1z],
         [{S('v(t)'): (S('x(t) - y(t) + z(t)'), 0.0001, False)}],
         {S("v(t)"): [Guard(S("v<=20"))],
          # The below state that x(t)'s invariant depends upon some
          # other function. Only one such function can be given as a
          # dependency. Also, a chain of such dependencies cannot be
          # created, yet!
          S('x(t)'): [S('v(t)')],
          S('y(t)'): [S('v(t)')],
          S('z(t)'): [S('v(t)')]})
t2 = Loc("t2", [ode2x, ode2y, ode2z],
         [{S('v(t)'): (S('x(t) - y(t) + z(t)'), 20, True)}],
         {S("v(t)"): [Guard(S("v < 20"))],
          S('x(t)'): [S('v(t)')],
          S('y(t)'): [S('v(t)')],
          S('z(t)'): [S('v(t)')]})
t3 = Loc("t3", [ode3x, ode3y, ode3z],
         [{S('v(t)'): (S('x(t) - y(t) + z(t)'), 20, True)}],
         {S("v(t)"): [Guard(S("v >= 20")), Guard(S("v < 138"))],
          S('x(t)'): [S('v(t)')],
          S('y(t)'): [S('v(t)')],
          S('z(t)'): [S('v(t)')]})
t4 = Loc("t4", [ode4x, ode4y, ode4z],
         [{S('v(t)'): (S('x(t) - y(t) + z(t)'), 138, False)}],
         {S("v(t)"): [Guard(S("v > 20")), Guard(S("v <= 138"))],
          S('x(t)'): [S('v(t)')],
          S('y(t)'): [S('v(t)')],
          S('z(t)'): [S('v(t)')]})

# The edges
e1 = Edge('t1', 't2', {S("v(t)"): [Guard(S("v < 20"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('y'), Symbol('y')),
           Update.Update2(Symbol('z'), Symbol('z'))],
          [Event("VS")])
e2 = Edge('t2', 't1', {S("v(t)"): [Guard(S("v < 20"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('y'), Symbol('y')),
           Update.Update2(Symbol('z'), Symbol('z'))],
          [Event("VSP")])
e3 = Edge('t2', 't3', {S("v(t)"): [Guard(S("v <= 20")),
                                   Guard(S("v >= 20"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('y'), Symbol('y')),
           Update.Update2(Symbol('z'), Symbol('z'))],
          [])
e4 = Edge('t3', 't4', {S("v(t)"): [Guard(S("v <= 138")),
                                   Guard(S("v >= 138"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('y'), Symbol('y')),
           Update.Update2(Symbol('z'), Symbol('z'))],
          [])
e5 = Edge('t4', 't1', {S("x(t)"): [Guard(S("x <= 20")),
                                   Guard(S("x >= 20"))]},
          [Update.Update2(Symbol('x'), Symbol('x')),
           Update.Update2(Symbol('y'), Symbol('y')),
           Update.Update2(Symbol('z'), Symbol('z'))],
          [])

cell3D = Ha("cell3d", [t1, t2, t3, t4], t1,
            [e1, e2, e3, e4, e5], [], [])


# Compile
shac.compile(cell3D, ABOF=True)
