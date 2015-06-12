# Author: Avinash Malik
# Thu May  7 14:21:57 NZST 2015

# This is the HA language encoded in python

from macropy.case_classes import macros, case


@case
class Ode(expr, var, initValue):
    pass


@case
class Combinator(symbol, arithExpr, [rest]):
    pass


@case
class Event(s):
    pass


@case
class Guard(relationalExpr):
    pass


@case
class Update():

    class Update1(var, nat):
        pass

    class Update2(x, y):
        pass


@case
class Loc(name, odeList, combinatorList, invariant, {rest}):
    pass


@case
class Edge(l1, l2, guard, updateList, eventList):
    pass


@case
class Ha(name, locations, startLocation, edges, globalVars):
    pass
