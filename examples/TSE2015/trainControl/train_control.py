import macropy.activate
from language import *
from gen import *
from sympy import *
import shac

#Train Control from 
# http://symbolaris.com/course/lahs/LAHS-04-hybrid-examples.pdf


ode_v1 = Ode(sympify("diff(v(t))-5"), sympify("v(t)"), 0, {})
ode_z1 = Ode(sympify("diff(z(t))-v(t)"), sympify("z(t)"), 0,
             {S('v(t)'): ode_v1})

ode_v2 = Ode(sympify("diff(v(t))+10"), sympify("v(t)"), 1000, {})
ode_z2 = Ode(sympify("diff(z(t))-v(t)"), sympify("z(t)"), 100000,
             {S('v(t)'): ode_v2})

# The locations of the hybrid automaton
t1 = Loc("t1", [ode_v1, ode_z1], [],
         {S("z(t)"): [Guard(S("z>=0"))],
          S("v(t)"): [Guard(S("v>=0")),
                      Guard(S("v<1000"))]})

t2 = Loc("t2", [ode_v2, ode_z2], [],
         {S("z(t)"): [Guard(S("z>=0"))],
          S("v(t)"): [Guard(S("v> 20"))]})


# The edges
e1 = Edge('t1', 't2', {S("v(t)"): [Guard(S("v>=1000"))]},
          [Update.Update2(Symbol("z"), Symbol("z")),
           Update.Update2(Symbol("v"), Symbol("v"))],
          [])
e2 = Edge('t2', 't1', {S("v(t)"): [Guard(S("v<=20"))]},
          [Update.Update2(Symbol("z"), Symbol("z")),
           Update.Update2(Symbol("v"), Symbol("v"))],
          [])


train_control = Ha("train_control", [t1, t2], t1,
                   [e1, e2], [], [])

# Compile
shac.compile(train_control, ABOF=True)
