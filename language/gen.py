# TODO: The codegen is not very efficient, because symbolic solutions
# are being regenerated every time

from macropy.experimental.pattern import macros, _matching, switch, patterns, LiteralMatcher, TupleMatcher, PatternMatchException, NameMatcher, ListMatcher, PatternVarConflict, ClassMatcher, WildcardMatcher
from language import *

from sympy import Symbol, dsolve, solve, S, Max, Mul, Add, nsolve, solve_undetermined_coeffs, Eq, nsimplify, Function, ccode, N, Abs, sign, classify_ode
from sympy.utilities.codegen import codegen, make_routine
from functools import partial
import colorama
import copy
from termcolor import colored

ALL_BETS_OFF = False


# Solving odes with free variables
def solve_ode_system(count, odee):
    with patterns:
        Ode(ode, var, iValue, rFuncs) << odee
        if rFuncs == {} and count > 0:
            sol = dsolve(ode)
            sol = sol.rhs.subs(Symbol('C1'), S('C1'+str(var.func)))
            return sol
        elif rFuncs != {}:
            rrFuncs = {}
            for k, v in rFuncs.iteritems():
                rrFuncs[k] = solve_ode_system(count+1, v)
                rft = [(k, v) for k, v in rrFuncs.iteritems()]
            ode = ode.subs(rft)
            if count > 0:
                ode = dsolve(ode).rhs.subs(Symbol('C1'), S('C1'+str(var.func)))
                return ode
            odee = Ode(ode, var, iValue, {})
            return odee
        else:
            return odee


# Function to generate code from Ode
def OdeCodegen(os, name):
    odes = [None]*len(os)
    vars = [None]*len(os)
    iValues = [None]*len(os)
    for i in xrange(0, len(os)):
        with patterns:
            Ode(ode, var, iValue, rFuncs) << os[i]
            odes[i] = ode
            vars[i] = var
            iValues[i] = iValue
    try:
        odes = map(lambda x, y: dsolve(x, y), odes, vars)
        # TODO: Check!!
        iodes = map(lambda o, v: o.subs(v, S(str(v.func)+'_u')),
                    odes, vars)
        iodes = map(lambda o: o.subs(S('t'), 0), iodes)
        iodes = map(lambda o: solve(o, S('C1'))[0], iodes)
        # BAD HACK IN PROGRESS
        riodes = map(lambda o, v: o.subs(v, S(str(v.func))),
                     odes, vars)
        riodes = map(lambda o: o.subs(S('t'), 0), riodes)
        riodes = map(lambda o: solve(o, S('C1'))[0], riodes)
        # BAD HACK FINISHED
        odess = map(lambda o, v:
                    o.subs([(Symbol('t'),
                             Mul(Symbol('k'),
                                 Symbol('d'))),
                            (Symbol('C1'), S('C1'+str(v.func)))]),
                    odes, vars)
        funcs = map(lambda o, i:
                    (name+"_ode_"+str(i+1), o.rhs), odess,
                    xrange(0, len(odess)))
        ifuncs = map(lambda (i, o): (name+"_init_"+(str(i+1)), o),
                     enumerate(iodes))
        # make the routine to see the arguments
        func_rs = map(lambda o, i:
                      make_routine(name+"_ode_"+str(i+1), o.rhs),
                      odess, xrange(len(odess)))
        ifunc_rs = map(lambda (i, o):
                       make_routine(name+"_init_"+(str(i+1)), o),
                       enumerate(riodes))
        [(c_name, c_code), (h_name, h_header)] = codegen(
            (funcs+ifuncs), "C", name,
            header=False, empty=False, to_files=False)
        return (c_code, h_name, h_header, [cv.func for cv in vars],
                func_rs, ifunc_rs)
    except Exception as e:
        raise e


def getEventList(edge):
    with patterns:
        Edge(l1, l2, guard, ulist, eventList) << edge
        events = []
        for i in xrange(len(eventList)):
            with patterns:
                Event(x) << eventList[i]
                if x is not None:
                    events.append(x)
        return events


def subb(oexpr, expr, contVars, u):
    if str(expr.func) in contVars:
        if not u:
            return oexpr.subs(expr, S(str(expr.func)))
        else:
            return oexpr.subs(expr, S(str(expr.func)+'_u'))
    else:
        for arg in expr.args:
            oexpr = subb(oexpr, arg, contVars, u)
    return oexpr


def subsc(c, contVars, u):
    for k, v in c.iteritems():
        c[k] = (subb(v[0], v[0], contVars, u), v[1])
    return c


def outcode(stmts, tab, sfk, odes, lname, funcrs):
    stmts += [tab+ccode(sfk, assign_to=S('fk'))]
    for i, od in enumerate(odes):
        with patterns:
            Ode(ode, var, ii, rFuncs) << od
            lhs = str(var.func)+'_u'
            rhs = lname+'_ode_' + str(i+1)
            mfuncrs = map(lambda x: 'fk'
                          if str(x.name) == 'k' else str(x.name),
                          funcrs[i].arguments)
            rhs += '(' + ', '.join(mfuncrs) + ')'
            stmts += [tab+lhs + ' = ' + rhs + ';']


def getInvariantAndOdeExpr(loc, events, tab, contVars,
                           funcrs, ifuncrs):
    with patterns:
        Loc(lname, odes, clist, guards) << loc
        exprs = [item for sl in guards.values() for item in sl]
        invs = [None]*len(exprs)
        for i, x in enumerate(exprs):
            with switch(x):
                if Guard(y):
                    invs[i] = y
        invs = filter(lambda x: x is not None, invs)
        # Adding not events as well to this expr
        stmts = []
        cstmts = []
        cks = []
        # Compute the combinator function values. This needs to be done
        # using a recursive function call
        cllist = map(lambda c: subsc(c, contVars, False),
                     copy.deepcopy(clist))
        for c in cllist:
            for k, v in c.iteritems():
                cstmts += [str(k.func) + ' = ' + str(v[0]) + ';']
                cks.append(str(k.func))
                cks.append(str(k.func)+'_u')
        for i, od in enumerate(odes):
            with patterns:
                Ode(ode, var, iValue, rFuncs) << od
                # Get the initial value once!
                stmts += ['if (pstate != cstate)']
                rr = lname + '_init_' + str(
                    i+1) + '(' + ', '.join(
                        [str(arg.name) for arg in ifuncrs[i].arguments]) + ')'
                stmts += [tab+'C1'+str(var.func)+' = '+rr+';']
                lhs = str(var.func)+'_u'
                rhs = lname+'_ode_' + str(i+1)
                rhs += '(' + ', '.join(
                    [str(arg.name) for arg in funcrs[i].arguments]) + ')'
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
                        gs = guards[var]
                        mm = []
                        for g in gs:
                            with switch(g):
                                if Guard(xx):
                                    if not isinstance(xx, bool):
                                        mm.append(xx.rhs)
                        if sign(s).is_Number:
                            if mm != []:
                                if sign(s) > 0:
                                    cb = str(max(mm))
                                    stmts += ['if('+str(var.func)+'_u > ' +
                                              cb + ' && C1'+str(var.func) +
                                              ' < ' + cb + ')']
                                    stmts += [tab + str(
                                        var.func) + '_u = ' + cb + ';']
                                else:
                                    # Decreasing or non-increasing function
                                    cb = str(min(mm))
                                    stmts += ['if('+str(var.func) +
                                              '_u < ' + cb + ' && C1' +
                                              str(var.func)+' > ' + cb + ')']
                                    stmts += [tab + str(
                                        var.func) + '_u = ' + cb + ';']
                            else:
                                pass
                        elif ALL_BETS_OFF:
                            warn = '[WARNING: ALL_BETS_OFF '
                            warn += 'ENABLED, ANYTHING CAN HAPPEN]'
                            print(colored(warn, color='red',
                                          attrs=['bold', 'blink']))
                            if mm != []:
                                cb = str(max(mm))
                                stmts += ['if((' + str(s) + ' > 0) && ' +
                                          str(var.func)+'_u > ' +
                                          cb + ' && C1'+str(var.func) +
                                          ' < ' + cb + ')']
                                stmts += [tab + str(
                                    var.func) + '_u = ' + cb + ';']
                                # Decreasing or non-increasing function
                                cb = str(min(mm))
                                stmts += ['if((' + str(s) + ' < 0) &&' +
                                          str(var.func) +
                                          '_u < ' + cb + ' && C1' +
                                          str(var.func)+' > ' + cb + ')']
                                stmts += [tab + str(
                                    var.func) + '_u = ' + cb + ';']
                            else:
                                pass
                        else:
                            raise Exception("Don't know how to saturate:"+str(
                                o) + ' with slope: ' + str(s))
                    else:
                        print 'Cannot saturate: ', str(o), ' in loc: ', lname
                else:
                    print 'Cannot saturate: ', str(o), ' in loc: ', lname
        # Add the saturation function for combinators
        # Step-1 solve odes
        os = [None]*len(odes)
        for i, o in enumerate(odes):
            with patterns:
                Ode(ode, v, iValue, rFuncs) << o
                os[i] = (v, dsolve(ode, v).subs(S('C1'),
                                                Symbol('C1'+str(v.func),
                                                       real=True)).rhs)
        # Step-2 compose the odes according to combinator functions.
        composed = copy.deepcopy(clist)
        for c in composed:
            for k, v in c.iteritems():
                c[k] = (v[0].subs(os), v[1])
        # Step-3 saturate!
        for c in copy.deepcopy(composed):
            for k, v in c.iteritems():
                # This code below is just a copy of the above code.
                # Later on refractor this code and the above code
                # into a single function.
                gs = guards[k]
                mm = []
                for g in gs:
                    with patterns:
                        Guard(xx) << g
                        if not isinstance(xx, bool):
                            mm.append(xx.rhs)
                if mm != []:
                    # Compute the combinator expression
                    cluist = map(lambda c: subsc(c, contVars, True),
                                 copy.deepcopy(clist))
                    for i, cu in enumerate(cluist):
                        for k, v in cu.iteritems():
                            stmts += [str(k.func) + '_u = ' + str(
                                v[0]) + ';']
                            # TODO: If ALL_BETS_OFF is enabled then we
                            # can also compute the slope at runtime
                            if clist[i][k][2]:
                                cb = str(max(mm))
                                stmts += ['// Increasing function']
                                stmts += ['if('+str(k.func)+'_u > ' + cb +
                                          ' && '+str(k.func)+' < ' + cb +
                                          ' && ' + str(k.func)+'_u >= ' +
                                          str(k.func) + '){']
                            else:
                                cb = str(min(mm))
                                stmts += ['// Decreasing function']
                                stmts += ['if('+str(k.func)+'_u < ' + cb +
                                          ' &&  '+str(k.func)+' > ' + cb +
                                          ' && ' + str(k.func) + '_u < ' +
                                          str(k.func)+'){']
                            # First compute "k"
                            fk = Add(composed[i][k][0].subs(S('t'),
                                                            S('k*d')),
                                     Mul(S(cb), -1))
                            sfk = solve(fk, S('k'), check=False)
                            sfk = [r for r in sfk
                                   if ('I' not in str(r) and
                                       r.is_finite is not False)]
                            if sfk != []:
                                sfk = sfk[0]
                            elif ALL_BETS_OFF:
                                warn = '[WARNING: ALL_BETS_OFF '
                                warn += 'ENABLED, ANYTHING CAN HAPPEN]'
                                print(colored(warn, color='red',
                                              attrs=['bold', 'blink']))
                            else:
                                print(colored(('Not a WHA!: ' + str(fk)),
                                              color='red',
                                              attrs=['bold', 'blink']))
                            if sfk == [] and not ALL_BETS_OFF:
                                stmts += [tab +
                                          'fprintf(stderr, "Not a WHA!");']
                                stmts += [tab+'exit(1);']
                            elif sfk == [] and ALL_BETS_OFF:
                                # Here one can compute the fk at runtime
                                # itself!
                                outcode(stmts, tab, fk, odes, lname, funcrs)
                            else:
                                outcode(stmts, tab, sfk, odes, lname, funcrs)
                            stmts += ["}"]
                else:
                    pass
        nevents = map(lambda x: '!'+x, events)
        return (' && '.join((map(str, invs)+nevents)), stmts, cstmts,
                set(cks))


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
        gus = []
        for i, guard in enumerate(guards):
            with patterns:
                Guard(xx) << guard
                gus.append(str(xx))
        egExpr = ' && '.join(filter(lambda x: not(x is None), gus))
        if egExpr == '':
            egExpr = 'False'
        # Now the event list
        eus = []
        for i, event in enumerate(eList):
            with patterns:
                Event(xx) << event
                eus.append(str(xx))
        eus = filter(lambda x: not(x is None), eus)
        nevents = filter(lambda x: not(x in eus), events)
        nevents = map(lambda x: '!'+x, nevents)
        eeExpr = ' && '.join(eus+nevents)
        # TODO: CHECK IF THIS IS TRUE!!  This means if there is no event
        # then there is an enabling event generated automatically
        if eeExpr == '':
            eeExpr = 'True'
        # Now for the update statements
        updates = []
        for update in uList:
            with switch(update):
                if Update.Update1(v, xx):
                    updates.append(str(v) + '_u =' + str(xx) + ';')
                elif Update.Update2(v, xx):
                    updates.append(str(v) + '_u = ' + str(xx) + ';')
                else:
                    raise ("Unrecognized update: ", update)
        updates = filter(lambda x: not (x is None), updates)
        return (eeExpr, egExpr, updates, t2)


def makeReactionFunction(fname, locs, edges, snames, events,
                         contVars, funcrs, ifuncrs):
    level = 1
    tab = ' '*2
    ret = ['enum states ' + fname +
           '(enum states cstate, enum states pstate) {']
    ret += [tab*level+'switch (cstate) {']

    # All code for state transition goes in here
    for i, state in enumerate(snames):
        # Code for state transitions
        (invExpr, odeStmts,
         cstmts, cks) = getInvariantAndOdeExpr(locs[i],
                                               events, tab,
                                               contVars,
                                               funcrs[i], ifuncrs[i])
        cks = list(cks) + ['fk']
        if (i == 0):
            ret += [tab*level+'double '+', '.join(cks)+';']
        ret += [tab*level+'case (' + state + '):']
        level += 1
        # If the ode is still begin solved
        for cst in cstmts:
            ret += [tab*level+cst]
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
            ret += [level*tab+'k=1;']
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
                Ode(ode, var, iValue, rFuncs) << o
                main += [tab*level + str(var.func) + ' = ' +
                         str(iValue) + ';']
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
        Ha(han, ls, sloc, edges, gvs) << ha
        lnames = [None]*len(ls)
        cCodeFile = [None]*len(ls)
        hns = [None]*len(ls)
        hcs = [None]*len(ls)
        funcrs = [None]*len(ls)
        ifuncrs = [None]*len(ls)
        contVars = [None]*len(ls)
        for i in xrange(len(ls)):
            with patterns:
                Loc(name, odes, clist, y) << ls[i]
                (cCodeFile[i], hns[i],
                 hcs[i], contVars[i],
                 funcrs[i], ifuncrs[i]) = OdeCodegen(odes, name)
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

        # Global variable declarations
        gv = ['// Global variables from outside this HA']
        ggvs = [str(name) for name in gvs]
        if ggvs != []:
            gv += ['extern double ' + ', '.join(ggvs) + ';']

        # Build the main function

        # Append the included headers
        mainCFile = headers
        # Append the #defines
        mainCFile += defs
        # Append the global variables
        mainCFile += gv
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
        constSet = {"C1"+x for x in contSet}
        constDecl = ['double ' + ', '.join(constSet) + ';']
        mainCFile += constDecl
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
                                          list(eventSet), list(contSet),
                                          funcrs, ifuncrs)

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
def getShortestTimes(excludes, lname, ode, invariants):
    colorama.init(autoreset=True)
    warn = '[WARNING: Location '+lname+' needs fairness]'
    try:
        with patterns:
            Ode(od, var, iValue, rFuncs) << ode
            # This means you could not provide a static initial
            # condition
            if iValue is None:
                # Return infinity as the time-bound
                print(colored(warn, color='green',
                              attrs=['bold', 'blink']))
                return {var: (S('oo'), None, False)}
            else:
                o = dsolve(od, var)
                i = solve(o.subs([(var, iValue),
                                  (Symbol('t'), 0)]),
                          Symbol('C1'))[0]
                on = o.subs(S('C1'), i)
                if on.rhs.is_Number:
                    print(colored(warn, color='green',
                                  attrs=['bold', 'blink']))
                    return {var: (S('oo'), None, False)}
                else:
                    invvs = [y for y in invariants[var]
                             if not isinstance(y, Function)]
                    for i, g in enumerate(invvs):
                        with patterns:
                            Guard(xx) << g
                            if not isinstance(xx, bool):
                                invvs[i] = xx.rhs
                            else:
                                invvs[i] = None
                    invvs = filter(lambda x: x is not None, invvs)
                    if invvs != []:
                        # Used for increasing functions
                        inv_max = max(invvs)
                        # Used for decreasing functions
                        inv_min = min(invvs)
                        time_max = solve(on.rhs-inv_max, S('t'),
                                         exclude=excludes, check=False)
                        if time_max == []:
                            ss = "Could not find MAX time for: "
                            raise Exception(ss + str(on) +
                                            " with invariant " + str(inv_max))
                        time_max = time_max[0]
                        if len(invvs) == 1:
                            time_min = time_max
                        else:
                            time_min = solve(on.rhs-inv_min, S('t'),
                                             exclude=excludes, check=False)
                            if time_min == []:
                                ss = "Could not find MIN time for: "
                                raise Exception(ss + str(on) +
                                                " with invariant " +
                                                str(inv_min))
                            time_min = time_min[0]
                        time = Max(N(Abs(time_max)), N(Abs(time_min)))
                        return {var: (time, on, False)}
                    else:
                        invvs = [y for y in invariants[var]
                                 if isinstance(y, Function)]
                        if invvs != []:
                            return {var: (-1, on, True)}
                        else:
                            print(colored(warn, color='green',
                                          attrs=['bold', 'blink']))
                            return {var: (S('oo'), None, False)}
    except Exception as k:
        raise k


def updateLocNsteps(excludes, loc):
    with patterns:
        Loc(n, odes, cf, invariants) << loc
        times = map(lambda o: getShortestTimes(excludes, n, o, invariants),
                    odes)
        (tt, g, mine) = times[0].values()[0]
        tts = [True]
        for yoo in times:
            for u, vv, oot in yoo.values():
                tts.append(u == tt)
        if all(tts) and (not mine):
            return Loc(n, odes, cf, invariants, time=tt)
        elif all(tts) and mine:
            cc = copy.deepcopy(cf)
            for y in times:
                for i in y.items():
                    (b, (m, v, oot)) = i
                    for c in cc:
                        for k, val in c.iteritems():
                            c[k] = (val[0].subs(b, v.rhs), val[1])
            # Now we can check if the invariants hold on the combinator
            # functions
            tts = []
            for c in cc:
                for k in c:
                    if c[k][0].is_Number:
                        print(colored(warn, color='green', attrs=['bold',
                                                                  'blink']))
                        return Loc(n, odes, cf, invariants, time=S('oo'))
                    else:
                        try:
                            invvs = ([y for x in invariants[k]
                                      for y in x if not isinstance(y, bool)])
                            if invvs != []:
                                invvs = map(lambda x: x.rhs, invvs)
                                # Used for increasing functions
                                inv_max = max(invvs)
                                # Used for decreasing functions
                                inv_min = min(invvs)
                                time_max = solve(c[k][0]-inv_max, S('t'))[0]
                                time_min = solve(c[k][0]-inv_min, S('t'))[0]
                                tts.append(Max(N(Abs(time_max)),
                                               (N(Abs(time_min)))))
                        except KeyError:
                            raise Exception("Not a WHA!!")
            if all(tts):
                return Loc(n, odes, cf, invariants, time=tts[0])
            elif ALL_BETS_OFF:
                return loc
            else:
                raise Exception("Not a WHA!!: " + str(times))
        elif ALL_BETS_OFF:
            return loc
        else:
            raise Exception("Not a WHA!!: " + str(times))


def getSha(ha):
    with patterns:
        Ha(n, ls, sloc, edges, gvs) << ha
        return Ha(n, map(partial(updateLocNsteps, gvs), ls),
                  sloc, edges, gvs)


# Function that checks that the ode is OK
def isOdeOK(odee):
    if ALL_BETS_OFF:
        return True
    else:
        with switch(odee):
            if Ode(ode, var, iValue, rFuncs):
                try:
                    o = dsolve(ode, var)
                    s = o.rhs.diff(Symbol('t'))
                    # TODO: check that this root finding is enough for
                    # monotonicity
                    m = solve(s, Symbol('t'), check=True)
                    return (m == [])
                except Exception as e:
                    print e
                    return False
            else:
                return False


# Function to test if location is WHA amenable
def isWhaLoc(loc):
    with switch(loc):
        if Loc(x, odes, clist, y):
            # TODO: Check that the combinator functions are also
            # monotonic
            return reduce(lambda init, ode: isOdeOK(ode) and init,
                          odes, True)
        else:
            return False


# Function to test if the ha is wha
def isWha(ha):
    with switch(ha):
        if Ha(n, ls, sloc, edges, gvs):
            return reduce(lambda init, x: isWhaLoc(x) and init,
                          ls, True)
        else:
            return False


def preprocess(ha):
    with switch(ha):
        if Ha(n, ls, sloc, edges, gvs):
            for i, loc in enumerate(ls):
                with switch(loc):
                    if Loc(x, odes, clist, y):
                        ls[i] = Loc(x,
                                    map(partial(solve_ode_system, 0), odes),
                                    clist, y)
            return Ha(n, ls, sloc, edges, gvs)
        else:
            raise Exception("Not a HA: " + str(ha))
