# Author: Avinash Malik
# Thu May  7 14:21:57 NZST 2015

# This is the HA language encoded in python

from macropy.case_classes import macros, case


@case
class Ode(expr, var, initValue, replaceFuncs):
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
class InternalVar(name):
    pass

@case
class ExternalInputVar(name):
    pass

@case
class ExternalOutputVar(name):
    pass

@case
class ExternalInputEvent(name):
    pass

@case
class ExternalOutputEvent(name):
    pass

@case
class Ha(name, locations, startLocation, edges, globalVars, igvs, internalVars, externalInputVars, externalOutputVars, externalInputEvent, externalOutputEvent):
    pass

@case
class Bind:
    class Bind1(externalOutputVars, externalInputVars):
        pass
    class Bind2(exterOutputEvent, externalInpuEvent):
        pass

@case
class BindHa(outha, bindlist, inha):
    pass
