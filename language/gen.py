# TODO: The combinator functions are not being used right now!  TODO:
# The codegen is not very efficient, because symbolic solutions are
# being regenerated every time

from macropy.experimental.pattern import macros, _matching, switch, patterns, LiteralMatcher, TupleMatcher, PatternMatchException, NameMatcher, ListMatcher, PatternVarConflict, ClassMatcher, WildcardMatcher
from language import *

from sympy import *
from sympy.utilities.codegen import codegen


# Function to generate code from Ode
def OdeCodegen(os, name):
    odes = [None]*len(os)
    vars = [None]*len(os)
    iValues = [None]*len(os)
    for i in range(0, len(os)):
        with patterns:
            Ode(ode, var, iValue) << os[i]
            odes[i] = ode
            vars[i] = var
            iValues[i] = iValue
    try:
        odes = map(lambda x, y: dsolve(x, y), odes, vars)
        initcs = map(lambda i, o, v:
                     solve(o.subs([(v, i),
                                   (Symbol('t'), 0)]),
                           Symbol('C1'))[0],
                     iValues, odes, vars)
        odess = map(lambda i, o:
                    o.subs([(Symbol('C1'), i),
                            (Symbol('t'),
                                Mul(Symbol('k'),
                                    Symbol('d')))]), initcs, odes)
        funcs = map(lambda o, i: (name+"_ode_"+str(i+1), o.rhs), odess,
                    range(0, len(odess)))
        [(c_name, c_code), (h_name, h_header)] = codegen(
            funcs, "C", name, header=False, empty=False, to_files=False)
        return (c_code, h_name, h_header)
    except Exception as e:
        raise e


def getEventList(edge):
    with patterns:
        Edge(l1, l2, guard, ulist, eventList) << edge
        events = [None]*len(eventList)
        for i in range(len(eventList)):
            with patterns:
                Event(x) << eventList[i]
                events[i] = x
                return events


# Function to generate code from HA
def codeGen(ha):
    with patterns:
        Ha(han, ls, sloc, edges) << ha
        lnames = [None]*len(ls)
        cCodeFile = [None]*len(ls)
        hns = [None]*len(ls)
        hcs = [None]*len(ls)
        for i in range(len(ls)):
            with patterns:
                Loc(name, odes, clist, y) << ls[i]
                (cCodeFile[i], hns[i], hcs[i]) = OdeCodegen(odes, name)
                lnames[i] = name

        # Start generating code
        # First the required headers
        headers = ['#include<stdint.h>']
        # Include other headers as needed here

        # The needed #defines
        defs = ['#define TRUE 1', '#define FALSE 0']

        # The string that declares all the Events
        eventList = map(getEventList, edges)
        eventSet = set([item for sl in eventList for item in sl])
        eventDecl = ['uint8_t ' + ', '.join(eventSet) + ';']

        # Build the main function

        # Append the included headers
        mainCFile = headers
        # Append the #defines
        mainCFile += defs
        # Append the event declarations
        mainCFile += eventDecl
        # Append state declaration
        mainCFile += ['enum states {' + ' , '.join(lnames)+'};']

        # Append the odes
        mainCFile = mainCFile + cCodeFile

        # This is the final set, write to files
        with open(han+".c", 'w') as cFile:
            cFile.write('\n\n'.join(mainCFile))

        # Write the header files out
        for i in range(len(hns)):
            with open(hns[i], 'w') as f:
                f.write(hcs[i])


# This is a very important function
def getShortestTimes(ode, invariants):
    try:
        with patterns:
            Ode(od, var, iValue) << ode
            # This means you could not provide a static initial
            # condition
            if iValue is None:
                # Return infinity as the time-bound
                return S('oo')
            else:
                o = dsolve(od, var)
                i = solve(o.subs([(var, iValue),
                                  (Symbol('t'), 0)]),
                          Symbol('C1'))[0]
                on = o.subs(S('C1'), i)
                if on.rhs.is_Number:
                    return S('oo')
                else:
                    invvs = ([y.rhs for x in invariants[var]
                              for y in x])
                    # Used for increasing functions
                    inv_max = max(invvs)
                    # Used for decreasing functions
                    inv_min = min(invvs)
                    time_max = solve(on.rhs-inv_max, S('t'))[0]
                    time_min = solve(on.rhs-inv_min, S('t'))[0]
                    time = Max(time_max, time_min)
                    return time
    except Exception as k:
        print k.__doc__
    return None


# NOTE: There should be an invariant for each ode on the location.
def updateLocNsteps(loc):
    with patterns:
        Loc(n, odes, clist, y) << loc
        times = map(lambda o: getShortestTimes(o, y), odes)
        # This means that all odes in the location evolve for same amout
        # of time in the worst case
        tts = map(lambda x: x == times[0], times[1:])
        if all(tts):
            return Loc(n, odes, clist, y, time=times[0])
        else:
            None


def getSha(ha):
    with patterns:
        Ha(n, ls, sloc, edges) << ha
        return Ha(n, map(updateLocNsteps, ls), sloc, edges)


# Function that checks the ode is OK
def isOdeOK(odee):
    with switch(odee):
        if Ode(ode, var, iValue):
            try:
                o = dsolve(ode, var)
                s = o.rhs.diff(Symbol('t'))
                # TODO: check that this root finding is enough for
                # monotonicity
                m = solve(s, Symbol('t'))
                return (m == [])
            except Exception as e:
                print e.__doc__
                return False
        else:
            return False


# Function to test if location is WHA amenable
def isWhaLoc(loc):
    with switch(loc):
        if Loc(x, odes, clist, y):
            return reduce(lambda init, ode: isOdeOK(ode) and init,
                          odes, True)
        else:
            return False


# Function to test if the ha is wha
def isWha(ha):
    with switch(ha):
        if Ha(n, ls, sloc, edges):
            return reduce(lambda init, x: isWhaLoc(x) and init,
                          ls, True)
        else:
            return False
