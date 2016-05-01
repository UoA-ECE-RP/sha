import macropy.activate
#from language import *
from languageC1 import *
#from gen import *
from genChanged2 import *
from sympy import *
import shac

#Train and Gate from 
# http://www.eecs.tufts.edu/~khan/Courses/Spring2013/EE194/Lecs/Hybrid_Systems_Presentation_Elliott_Costello.pdf

ode_x_down = Ode(sympify("diff(x(t))-(0-x(t))/2"), sympify("x(t)"), 10, {})
ode_x_up = Ode(sympify("diff(x(t))-(11-x(t))/2"), sympify("x(t)"), 1, {})

# The locations of the hybrid automaton
t1 = Loc("t1", [ode_x_down], [],
         {S("x(t)"): [Guard(S("x>=1")), Guard(S("x <= 10"))]})

t2 = Loc("t2", [ode_x_up], [],
         {S("x(t)"): [Guard(S("x>=1")), Guard(S("x <= 10"))]})


# The edges
e1 = Edge('t1', 't2', {S("x(t)"): [Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("UP")])
e2 = Edge('t2', 't1', {S("x(t)"): [Guard(sympify("True"))]},
          [Update.Update2(Symbol('x'), Symbol('x'))],
          [Event("DOWN")])


gate = Ha("gate", [t1, t2], t2, [e1, e2], [], [], [InternalVar("x")], [], [ExternalOutputVar("l"), ExternalOutputVar("m"), ExternalOutputVar("n")],
	[ExternalInputEvent("trianSignalIn")], [])


# Compile
# shac.compile(gate)

#shac.compile(gate,ABOF=True,Q=True)
