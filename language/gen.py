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
        funcs = map(lambda o, i: ("ode"+str(i+1), o.rhs), odess,
                    range(0, len(odess)))
        codegen(funcs, "C", name, header=False, empty=False, to_files=True)
    except Exception as e:
        raise e


# Function to generate code from HA
def WhaCodegen(ha):
    with patterns:
        Ha(ls, sloc, edges) << ha
        for i in range(len(ls)):
            with patterns:
                Loc(name, odes, clist, y) << ls[i]
                # This function will write out the c files
                OdeCodegen(odes, name+(str(i)))


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
        if Ha(ls, sloc, edges):
            return reduce(lambda init, x: isWhaLoc(x) and init,
                          ls, True)
        else:
            return False
