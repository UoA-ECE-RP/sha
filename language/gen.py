from macropy.experimental.pattern import macros, _matching, switch, patterns, LiteralMatcher, TupleMatcher, PatternMatchException, NameMatcher, ListMatcher, PatternVarConflict, ClassMatcher, WildcardMatcher
from language import *

from sympy import *
from sympy.utilities.codegen import codegen


# Function to generate code from Ode
def OdeCodegen(ode):
    with patterns:
        Ode(ode, var, iValue) << ode
        try:
            # Symbolically solve the ode
            o = dsolve(ode, var)
            i = solve(o.subs([(var, iValue),
                              (Symbol('t'), 0)]), Symbol('C1'))[0]
            o = o.subs([(Symbol('C1'), i),
                        (Symbol('t'),
                         Mul(Symbol('k'),
                             Symbol('d')))])
            [(c_name, c_code),
             (h_name, h_header)] = codegen(funcs, "C", "odes",
                                           header=False,
                                           empty=False)
            return (c_name, c_code, h_name, h_header)
        except Exception as e:
            print e.__doc__
            return None
    return None


# Function to generate code from HA
def WhaCodegen(ha):
    # Call odecode gen from here
    return None

# Function that checks the ode is OK
def isOdeOK(odee):
    with switch(odee):
        if Ode(ode, var, iValue):
            # Get the
            try:
                # Symbolically solve the ode
                o = dsolve(ode, var)
                # Get the slope of the ode
                s = o.rhs.diff(Symbol('t'))
                # Check if this is monotone
                m = solve(s, Symbol('t'))
                if m == []:
                    return True
                else:
                    return False
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
