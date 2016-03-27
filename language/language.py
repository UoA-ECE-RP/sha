# Author: Avinash Malik

# This is the HA language encoded in python

from macropy.case_classes import macros, case

@case
class Ode(expr, var, initValue, replaceFuncs):
    pass


@case
class Combinator(symbol, arithExpr, [rest]):
    pass

@case
class Variable(name, type, value):
    pass

#@case
#class Event(s):
    #pass
    
@case
class Event(type, name):
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

# CHANGED : newly added class 

@case
class ExternalEvents(externalInputEvents,externalOutputEvents):
    pass

# CHANGED : newly added class

@case 
class ExternalVars(externalInputVars,externalOutputVars):
    pass

# CHANGED : included [rest] list of optional arguments. rest[0] - ExternalEvents , rest[1] - ExternalVars

@case
class Ha(name, locations, startLocation, edges, globalVars, iglobalVars, [rest]):
    pass
