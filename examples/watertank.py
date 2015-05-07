# The water-tank example coded in Python

# TODO: Still need to write the parser

import macropy.activate
from language import *
from gen import *
from sympy import *


# K = 100, h = 20
ode1 = Ode(sympify("diff(x(t))-100*(20-x(t))"), sympify("x(t)"), 20)
ode2 = Ode(sympify("diff(x(t))"), sympify("x(t)"), 100)
ode3 = Ode(sympify("diff(x(t))+100*x(t)"), sympify("x(t)"), 100)
ode4 = Ode(sympify("diff(x(t))"), sympify("x(t)"), 20)

# The locations of the hybrid automaton
t1 = Loc("t1", [ode1], [], sympify("x>=20 & x<=100"))
t2 = Loc("t2", [ode2], [], sympify("x>=100 & x<=100"))
t3 = Loc("t3", [ode3], [], sympify("x>=20 & x<=100"))
t4 = Loc("t4", [ode4], [], sympify("x>=20 & x<=20"))

# The edges
e1 = Edge(t1, t2, sympify("x>=100 & x<=100"),
          [Update.Update2(Symbol('x'), Symbol('x'))],
          Event("B"))
e2 = Edge(t2, t3, sympify("True"),
          [Update.Update2(Symbol('x'), Symbol('x'))],
          Event("OFF"))
e3 = Edge(t1, t3, sympify("True"),
          [Update.Update2(Symbol('x'), Symbol('x'))],
          Event("OFF"))
e4 = Edge(t3, t1, sympify("True"),
          [Update.Update2(Symbol('x'), Symbol('x'))],
          Event("ON"))
e5 = Edge(t3, t4, sympify("x>=20 & x<=20"),
          [Update.Update2(Symbol('x'), Symbol('x'))],
          Event("C"))
e6 = Edge(t3, t1, sympify("True"),
          [Update.Update2(Symbol('x'), Symbol('x'))],
          Event("ON"))

waterTank = Ha([t1, t2, t3, t4], t4, [e1, e2, e3, e4, e5, e6])

# Check if the HA is well defined

print waterTank
print isWha(waterTank)
