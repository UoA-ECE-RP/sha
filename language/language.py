# Author: Avinash Malik
# Thu May  7 14:21:57 NZST 2015

# This is the HA language encoded in python

from macropy.case_classes import macros, case


@case
class Ode(ode, arithExpr):
    pass


@case
class Combinator(symbol, arithExpr):
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
class Loc(name, odeList, combinatorList, invariant):
    pass


@case
class Edge(locationTuple, guard, updateList, eventList):
    pass


@case
class Ha(locations, startLocation, edges):
    pass
