# TODO: The combinator functions are not being used right now!  TODO:
# The codegen is not very efficient, because symbolic solutions are
# being regenerated every time

from macropy.experimental.pattern import macros, _matching, switch, patterns, LiteralMatcher, TupleMatcher, PatternMatchException, NameMatcher, ListMatcher, PatternVarConflict, ClassMatcher, WildcardMatcher
from language import *

from sympy import *
from sympy.utilities.codegen import codegen
import colorama
from termcolor import colored


# Function to generate code from Ode
def OdeCodegen(os, name):
    odes = [None]*len(os)
    vars = [None]*len(os)
    iValues = [None]*len(os)
    for i in xrange(0, len(os)):
        with patterns:
            Ode(ode, var, iValue) << os[i]
            odes[i] = ode
            vars[i] = var
            iValues[i] = iValue
    try:
        odes = map(lambda x, y: dsolve(x, y), odes, vars)
        # TODO: Check!!
        iodes = map(lambda o: o.subs(var, S(str(var.func)+'_u')),
                    odes)
        iodes = map(lambda o: o.subs(S('t'), 0), iodes)
        iodes = map(lambda o: solve(o, S('C1'))[0], iodes)
        odess = map(lambda o:
                    o.subs([(Symbol('t'),
                             Mul(Symbol('k'),
                                 Symbol('d')))]), odes)
        funcs = map(lambda o, i:
                    (name+"_ode_"+str(i+1), o.rhs), odess,
                    xrange(0, len(odess)))
        ifuncs = map(lambda (i, o): (name+"_init_"+(str(i+1)), o),
                     enumerate(iodes))
        [(c_name, c_code), (h_name, h_header)] = codegen(
            (funcs+ifuncs), "C", name,
            header=False, empty=False, to_files=False)
        return (c_code, h_name, h_header, [cv.func for cv in vars])
    except Exception as e:
        raise e


def getEventList(edge):
    with patterns:
        Edge(l1, l2, guard, ulist, eventList) << edge
        events = [None]*len(eventList)
        for i in xrange(len(eventList)):
            with patterns:
                Event(x) << eventList[i]
                events[i] = x
                return events


def getInvariantAndOdeExpr(loc, events, tab):
    with patterns:
        Loc(lname, odes, clist, guards) << loc
        exprs = [item for sl in guards.values() for item in sl]
        invs = [None]*len(exprs)
        for i, x in enumerate(exprs):
            with patterns:
                Guard(y) << x
                invs[i] = y
        # Adding not events as well to this expr
        stmts = []
        for i, od in enumerate(odes):
            with patterns:
                Ode(ode, var, iValue) << od
                # Get the initial value once!
                stmts += ['if (pstate != cstate)']
                rr = lname+'_init_'+str(i+1)+'('+str(var.func)+')'
                stmts += [tab+'C1 = '+rr+';']
                lhs = str(var.func)+'_u'
                # This if condition only works, because we make sure
                # that all odes have same worst case time in a given
                # location
                if loc.rest['time'] != S('oo'):
                    rhs = lname+'_ode_' + str(i+1)
                    r2 = '(C1, d, k)'
                    rhs += r2
                else:
                    rhs = lname+'_ode_'+str(i+1)
                    r2 = '(C1)'
                    rhs += r2
                stmts += [lhs + ' = ' + rhs + ';']
                # Now put the saturation function in
                o = dsolve(ode, var)
                if not (iValue is None):
                    i = solve(o.subs([(var, iValue),
                                      (Symbol('t'), 0)]),
                              Symbol('C1'))[0]
                    o = o.subs(S('C1'), i)
                    if not o.rhs.is_Number:
                        s = o.rhs.diff(S('t'))
                        s = s.subs(S('t'), 0)
                        if s.is_Number:
                            gs = guards[var]
                            mm = [None]*len(gs)
                            for i, g in enumerate(gs):
                                with patterns:
                                    Guard(xx) << g
                                    mm[i] = xx.rhs
                            if s > 0:
                                cb = str(max(mm))
                                stmts += ['if('+str(
                                    var.func)+'_u > ' + cb + ')']
                                stmts += [tab + str(
                                    var.func) + '_u = ' + cb + ';']
                            else:
                                # Decreasing function
                                cb = str(min(mm))
                                stmts += ['if('+str(
                                    var.func)+'_u < ' + cb + ')']
                                stmts += [tab + str(
                                    var.func) + '_u = ' + cb + ';']
                        else:
                            raise Exception('Don\'t know how to saturate')
                    else:
                        print ('Cannot saturate: ', str(o),
                               ' in loc: ', lname)
                else:
                    print ('Cannot saturate: ', str(o),
                           ' in loc: ', lname)
        nevents = map(lambda x: '!'+x, events)
        return (' && '.join((map(str, invs)+nevents)), stmts)


def edgesWithstateSource(edges, sname):
    ret = []
    for edge in edges:
        with patterns:
            Edge(t1, t2, guard, uList, eList) << edge
            if t1 == sname:
                ret.append(edge)
    return ret


def getEAndGAndU(edge, events):
    with patterns:
        Edge(t1, t2, guards, uList, eList) << edge
        guards = [item for sl in guards.values() for item in sl]
        gus = [None]*len(guards)
        for i, guard in enumerate(guards):
            with patterns:
                Guard(xx) << guard
                gus[i] = str(xx)
        egExpr = ' && '.join(filter(lambda x: not(x is None), gus))
        if egExpr == '':
            egExpr = 'False'
        # Now the event list
        eus = [None]*len(eList)
        for i, event in enumerate(eList):
            with patterns:
                Event(xx) << event
                eus[i] = str(xx)
        eus = filter(lambda x: not(x is None), eus)
        nevents = filter(lambda x: not(x in eus), events)
        nevents = map(lambda x: '!'+x, nevents)
        eeExpr = ' && '.join(eus+nevents)
        if eeExpr == '':
            eeExpr = 'False'
        # Now for the update statements
        updates = [None]*len(uList)
        for update in uList:
            with switch(update):
                if Update.Update1(v, xx):
                    updates[i] = str(v) + '=' + str(xx) + ';'
                elif Update.Update2(v, xx):
                    updates[i] = str(v) + '_u = ' + str(xx) + ';'
                else:
                    raise ("Unrecognized update: ", update)
        updates = filter(lambda x: not (x is None), updates)
        return (eeExpr, egExpr, updates, t2)


def makeReactionFunction(fname, locs, edges, snames, events):
    level = 1
    tab = ' '*2
    ret = ['enum states ' + fname +
           '(enum states cstate, enum states pstate) {']
    ret += [tab*level+'switch (cstate) {']

    # All code for state transition goes in here
    for i, state in enumerate(snames):
        ret += [tab*level+'case (' + state + '):']
        level += 1
        # Code for state transitions
        (invExpr, odeStmts) = getInvariantAndOdeExpr(locs[i],
                                                     events, tab)

        # If the ode is still begin solved
        ret += [tab*level+'if('+invExpr+'){']
        # The code for ode solving goes here!
        level += 1
        for stmt in odeStmts:
            ret += [tab*level+stmt]
        ret += [level*tab+'++k;']
        ret += [level*tab+'cstate = '+state+';']
        level -= 1
        ret += [tab*level+'}']

        # Ode is now solved or preempted by an event!
        done = False
        for edge in edgesWithstateSource(edges, state):
            (eeExpr, egExpr, uStmts, dState) = getEAndGAndU(edge,
                                                            events)
            ret += [tab*level+'else if('+(' && '.join([eeExpr,
                                                 egExpr]))+') {']
            level += 1
            # Saturate currently only works for non-combinator functions
            ret += [level*tab+'k=0;']
            ret += [level*tab+'cstate='+dState+';']
            # Put the updates from edge here!
            uStmts = map(lambda x: tab*level+x, uStmts)
            ret += uStmts
            level -= 1
            ret += [tab*level+'}']
            done = True
        if done:
            ret += [level*tab+'else {']
            level += 1
            rr = 'fprintf(stderr,"Unreachable state!");'
            ret += [level*tab+rr]
            ret += [level*tab+'exit(1);']
            level -= 1
            ret += [level*tab+'}']
        ret += [level*tab+'break;']
        level -= 1
    ret += [level*tab+'default: exit(1);']
    ret += [level*tab+'}']
    # Return the cstate variable for the next reaction
    ret += [level*tab+'return cstate;']
    ret += ['}']
    return ['\n'.join(ret)]


def makeMain(sloc, rName, cvars):
    tab = ' '*2
    level = 1
    main = ['int main(void) {']
    with patterns:
        Loc(name, ol, y, z) << sloc
        # Initialize the continous vars for the sloc
        for i, o in enumerate(ol):
            with patterns:
                Ode(ode, var, iValue) << o
                main += [tab*level + str(var.func) + ' = ' + str(iValue) + ';']
        main += [tab*level+'enum states pstate = -1;']
        main += [tab*level+'enum states cstate = '+name+';']
        main += [tab*level+'while(True) {']
        level += 1
        main += [tab*level+'readInput();']
        main += [tab*level+'enum states rstate = '+rName+'(cstate, pstate);']
        main += [tab*level+'pstate = cstate;']
        main += [tab*level+'cstate = rstate;']
        # Update the conts with uconts
        updates = map(lambda x: tab * level + x + ' = ' + x +
                      '_u;', cvars)
        main += updates
        main += [tab*level+'writeOutput();']
        level -= 1
        main += [tab*level+'}']
        main += [tab*level+'return 0;']
    main += ['}']
    return ['\n'.join(main)]


# Function to generate code from HA
def codeGen(ha):
    with patterns:
        Ha(han, ls, sloc, edges) << ha
        lnames = [None]*len(ls)
        cCodeFile = [None]*len(ls)
        hns = [None]*len(ls)
        hcs = [None]*len(ls)
        contVars = [None]*len(ls)
        for i in xrange(len(ls)):
            with patterns:
                Loc(name, odes, clist, y) << ls[i]
                (cCodeFile[i], hns[i],
                 hcs[i], contVars[i]) = OdeCodegen(odes, name)
                lnames[i] = name

        # Start generating code
        # First the required headers
        headers = ['#include<stdint.h>']
        headers += ['#include<stdlib.h>']
        headers += ['#include<stdio.h>']
        # Include other headers as needed here

        # The needed #defines
        defs = ['#define True 1', '#define False 0']

        # The string that declares all the Events
        eventList = map(getEventList, edges)
        eventSet = set([item for sl in eventList for item in sl])
        eventDecl = ['extern unsigned char ' + ', '
                     .join(eventSet) + ';']
        eventDecl += ['extern void readInput();']
        eventDecl += ['extern void writeOutput();']

        # Declare the continous variables as doubles
        contSet = set([str(item) for sl in contVars for item in sl])
        contDecl = ['double ' + ', '.join(contSet) + ';']
        # Declare the update continous variables
        uContSet = set([str(item)+"_u" for sl in contVars for item in sl])
        uContDecl = ['double ' + ', '.join(uContSet) + ';']

        # Build the main function

        # Append the included headers
        mainCFile = headers
        # Append the #defines
        mainCFile += defs
        # Append the event declarations
        mainCFile += ['//Events']
        mainCFile += eventDecl
        # Append the continous variables
        mainCFile += ['//Continous variables']
        mainCFile += contDecl
        # The updated continous variables
        mainCFile += ['//Continous variable update']
        mainCFile += uContDecl
        # The constant variable
        mainCFile += ['//The constant variable']
        mainCFile += ['double C1;']
        # Append the step-size and step declarations
        mainCFile += ['//Step-size constant d']
        mainCFile += ['extern double d;']
        mainCFile += ['//Nstep constant k']
        mainCFile += ['double k;']
        # Append state declaration
        mainCFile += ['//States']
        mainCFile += ['enum states {' + ' , '.join(lnames)+'};']
        # The previous state variable
        mainCFile += ['//Previous state variable']

        # Append the odes
        mainCFile += cCodeFile

        # Make the main reaction function
        mainCFile += makeReactionFunction(han, ls, edges, lnames,
                                          list(eventSet))

        # Make the main function
        mainCFile += makeMain(sloc, han, list(contSet))

        # This is the final set, write to files
        with open(han+".c", 'w') as cFile:
            cFile.write('\n\n'.join(mainCFile))

        # Write the header files out
        for i in xrange(len(hns)):
            with open(hns[i], 'w') as f:
                f.write(hcs[i])


# This is a very important function
def getShortestTimes(lname, ode, invariants):
    colorama.init(autoreset=True)
    warn = '[WARNING: Location '+lname+' needs fairness]'
    try:
        with patterns:
            Ode(od, var, iValue) << ode
            # This means you could not provide a static initial
            # condition
            if iValue is None:
                # Return infinity as the time-bound
                print(colored(warn, color='red',
                              attrs=['bold', 'blink']))
                return S('oo')
            else:
                o = dsolve(od, var)
                i = solve(o.subs([(var, iValue),
                                  (Symbol('t'), 0)]),
                          Symbol('C1'))[0]
                on = o.subs(S('C1'), i)
                if on.rhs.is_Number:
                    print(colored(warn, color='red',
                                  attrs=['bold', 'blink']))
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
        times = map(lambda o: getShortestTimes(n, o, y), odes)
        # This means that all odes in the
        # location evolve for same amout
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


# Function that checks that the ode is OK
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
