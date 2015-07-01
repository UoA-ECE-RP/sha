import gen
from language import *
from macropy.experimental.pattern import macros, _matching, switch, patterns, LiteralMatcher, TupleMatcher, PatternMatchException, NameMatcher, ListMatcher, PatternVarConflict, ClassMatcher, WildcardMatcher
from sympy import Symbol, dsolve, solve, S, Max, Mul, Add, nsolve, solve_undetermined_coeffs, Eq, nsimplify, Function, ccode, N, Abs, sign, classify_ode
from itertools import *


def compile2SHA(ha):
    return gen.preprocess(ha)


def getShaEdges(sha):
    with patterns:
        Ha(n, ss, sss, e, gvs) << sha
        rets = [None]*len(e)
        for i, s in enumerate(e):
            with patterns:
                Edge(l1, l2, guard, updateList, eventList) << s
                rets[i] = Edge(n+'_'+l1, n+'_'+l2,
                               guard, updateList, eventList)
        return rets


def getShaLocations(sha):
    with patterns:
        Ha(n, ss, sss, e, gvs) << sha
        rets = [None]*len(ss)
        for i, s in enumerate(ss):
            with patterns:
                Loc(name, odeList, combinatorList, invariant) << s
                rets[i] = Loc(n+'_'+name, odeList, combinatorList, invariant)
        return rets


def compose(haList):
    # First generate the SHA
    shas = ([compile2SHA(r) for r in haList])

    name = []
    newgvs = []
    nsss = []
    for sha in shas:
        with patterns:
            Ha(n, ss, sss, e, gvs) << sha
            newgvs += gvs
            name += [n]
            with patterns:
                Loc(lname, odeList, combinatorList, invariant) << sss
                nsss += [n+'_'+lname]
    ha_name = '_'.join(name)
    init_loc_name = '_'+'_'.join(nsss)
    init_loc = None

    # get states
    states = [getShaLocations(s) for s in shas]
    pset = list(product(*states))
    newLoc = [None]*len(pset)
    for ii, i in enumerate(pset):
        newLocname = ''
        newLocodeList = []
        newLoccList = []
        newLocinvsdict = {}
        for loc in i:
            with patterns:
                Loc(name, odeList, cList, invs) << loc
                newLocname += '_'+name
                newLocodeList += odeList
                newLoccList += cList
                newLocinvsdict.update(invs)
        newLoc[ii] = Loc(newLocname, newLocodeList,
                         newLoccList, newLocinvsdict)
        if newLocname == init_loc_name:
            init_loc = newLoc[ii]

    # Now build the edges
    edges = [getShaEdges(s) for s in shas]
    pset = list(product(*edges))
    newEdges = [None]*len(pset)
    for ii, i in enumerate(pset):
        nl1 = ''
        nl2 = ''
        nguards = {}
        nupdateList = []
        neventList = []
        for edge in i:
            with patterns:
                Edge(l1, l2, guards, updateList, eventList) << edge
                nl1 += '_'+l1
                nl2 += '_'+l2
                nupdateList += updateList
                neventList += eventList
                # Dictionaries need to be handeled correctly
                for k in guards.iterkeys():
                    if k in nguards.keys():
                            nguards[k].append(*guards[k])
                    else:
                        nguards.update(guards)
        newEdges[ii] = Edge(nl1, nl2, nguards, nupdateList, neventList)

    # Now make the name of the Ha to be returned
    return Ha(ha_name, newLoc, init_loc, newEdges, newgvs)
