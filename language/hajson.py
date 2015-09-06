# This the files that converts the JASON format to HA
# Author: Avinash Malik
# Date: Sun Sep  6 23:07:14 NZST 2015

from sympy import S, Function
import jsonlib2 as json
from language import *


# Recursively get all the derivatives
def get_Derivatives(expr, ret):
    if expr.is_Derivative:
        ret.append(expr)
    for arg in expr.args:
        get_Derivatives(arg, ret)


# Recursively get the functions from the derivatives
def get_Functions(der, ff):
    if der.is_Function:
        ff.append(der)
    for arg in der.args:
        get_Functions(arg, ff)


def parseHA(fileName):
    """
    The function that creates the python description of the HA from JSON
    """
    with open(fileName, 'r') as jsonFile:
        ha = json.read(jsonFile.read())
        locs = []
        # Building locations
        for loc in ha['locations']:
            # Get the odes in this location I am just giving the default
            # initial value right now (0)

            # The JSON needs to have an initial
            # value Similarly, I am giving an empty dictionary as the
            # dependent odes.

            # JSON needs to have the list of dependent odes

            # First get the function from the derivative
            funcs = [S(o) for o in loc['ode']]
            odes = [None]*len(funcs)
            for i, f in enumerate(funcs):
                ders = []
                ff = []
                get_Derivatives(f, ders)
                if not all(ders):
                    raise Exception('More than one der in:' + f)
                get_Functions(ders[0], ff)
                if not all(ff):
                    raise Exception('Not a first order derivative:' + f)
                odes[i] = Ode(S(o), ff[0], 0, {})

            # Get the key for the invariant
            invsS = [S(i) for i in loc['invariants']]
            invK = set([Function(str(i.lhs))(S('t')) for i in invsS])
            # Now make the dictionary of invariants
            invs = {k: [] for k in invK}
            for i in invsS:
                for k in invK:
                    if str(i.lhs) == str(k.func):
                        invs[k] += [Guard(i)]
            locs += [Loc(loc['name'][0], odes, [], invs)]

        # Now build the edges
        edges = [None]*len(ha['edges'])
        for ei, e in enumerate(ha['edges']):
            # Names
            [s, t] = e['name']

            # TODO: ZHAN needs to have events, guards, and updates
            # separate

            # Events and Guards are in invariant!

            # Check there can only be events and relations in invariant
            alls = map(lambda x: S(x).is_Relational or S(x).is_Symbol,
                       e['invariants'])
            allOK = reduce(lambda x, y: y and x, alls, True)
            if not allOK:
                raise Exception('Only symbols and relations allowed: ' +
                                str(e['invariants']))

            # First get the events if any
            events = [Event(g) for g in e['invariants'] if S(g).is_Symbol]

            # Second get the relations if any
            rels = [S(g) for g in e['invariants'] if S(g).is_Relational]
            # Build the key needed to put in the relations
            relsK = set([Function(str(i.lhs))(S('t')) for i in rels])
            relsD = {k: [] for k in relsK}
            for i in rels:
                for k in relsK:
                    if str(i.lhs) == str(k.func):
                        relsD[k].append(Guard(i))

            # The update is in guards key!
            ups = []
            for u in e['guards']:
                [x1, x2] = u.split('=')
                if x1 == x2:
                    x1, x2 = S(x1), S(x2)
                    if x1.is_Symbol and x2.is_Symbol:
                        ups.append(Update.Update2(x1, x2))
                    elif x1.is_Symbol and x2.is_Integer:
                        ups.append(Update.Update1(x1, x2))
                    else:
                        raise Exception('Invalid Updates: ' + u)

            # Make the edges
            edges[ei] = Edge(s, t, relsD, ups, events)

        # Finally make the HA
        # XXX: ZHAN needs to give me the unique start location
        # TODO: How to declare local and global vars in the HA model??
        ha = Ha(ha['modelName'], locs, locs[0], edges, [], [])
        return ha
