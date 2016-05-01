# TODO: The codegen is not very efficient, because symbolic solutions
# are being regenerated every time

from macropy.experimental.pattern import macros, _matching, switch, patterns, LiteralMatcher, TupleMatcher, PatternMatchException, NameMatcher, ListMatcher, PatternVarConflict, ClassMatcher, WildcardMatcher
from languageC1 import *

from sympy import Symbol, dsolve, solve, S, Max, Mul, Add, nsolve, solve_undetermined_coeffs, Eq, nsimplify, Function, ccode, N, Abs, sign, classify_ode
from sympy.utilities.codegen import codegen, make_routine
from functools import partial
import colorama
import copy
from termcolor import colored
from sympy.abc import x, d, t
import pdb

ALL_BETS_OFF = False


#def makeMain(sloc, rName, cvars):
def makeMain(sloc, rName):
    #print type(sloc[0])
    tab = ' '*2
    level = 1

    main = []

    for i in xrange(len(sloc)):
        print "range"
        with patterns:
            print "range1"
            print sloc[i]
            print rName
            print type(sloc[i])
            Loc(name, ol, y, z) << sloc[i]


            print "hahahahaha"
            print type(name)
            print type(rName[0])
            #main += [tab*level+'enum states pstate = -1;']

            '''
            ps = map(lambda x: 
                tab*level+'int '+x+'_pstate = -1;', rName)
            main += ps
            print ps
            #main += [tab*level+'enum states cstate = '+name+';']
            print rName
            print name
            #cs = map(lambda x, y: 
             #   tab*level+'int '+x+'_cstate = '+y+';', rName, name)
            #main += cs

            main += [tab*level+'while(True) {']
            level += 1
            main += [tab*level+'readInput();']
            '''
            #main += [tab*level+'enum states rstate = '+rName+'(cstate, pstate);']
            rs = map(lambda x: 
                tab*level+'int '+x+'_rstate = '+x+' (' +x+'_cstate, '
                    +x+'_pstate);', rName)
            main += rs

            #main += [tab*level+'pstate = cstate;']
            pc = map(lambda x: 
                tab*level+x+'_pstate = '+x+'_cstate;', rName)
            main += pc

            #main += [tab*level+'cstate = rstate;']
            cr = map(lambda x: 
                tab*level+x+'_cstate = '+x+'_rstate;', rName)
            main += cr

           
            '''
            # Update the conts with uconts
            updates = map(lambda x: tab * level + x + ' = ' + x +
                          '_u;', cvars)
            main += updates
            ''' 
            
            main += [tab*level+'writeOutput();']
            level -= 1
            main += [tab*level+'}']
            main += [tab*level+'return 0;']
    main += ['}']
    return ['\n'.join(main)]


# Function to generate code from HA

def codeGen(hal):
    print "ccc"
    print len(hal)
    mainCFile = []

    headers = ['#include<stdint.h>']
    headers += ['#include<stdlib.h>']
    headers += ['#include<stdio.h>']
    headers += ['#include<math.h>']

    defs = ['#define True 1', '#define False 0']

    eventDecl = []
    eventDecl += ['extern void readInput();']
    eventDecl += ['extern void writeOutput();']

    mainCFile += headers

    mainCFile += defs

    # Append the event declarations
    mainCFile += ['//Events']
    mainCFile += eventDecl
    
    for i in xrange(len(hal)):
        with patterns:
        
            Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << hal[i]
          
            hanlist = []
            hanlist +=[han]
         
            externInt = map(lambda x: 
            'extern int '+x+'(int, int);', hanlist)
            mainCFile += externInt  

    tab = ' '*2
    level = 1
    
    mainCFile += ['int main(void) {']


    for i in xrange(len(hal)):
        with patterns:

            Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << hal[i]
          
            hanlist = []
            hanlist +=[han]
            ps = map(lambda x: 
                tab*level+'int '+x+'_pstate = -1;', hanlist)
            mainCFile += ps


    mainCFile += [tab*level+'while(True) {']
    level += 1
    mainCFile += [tab*level+'readInput();']


    for i in xrange(len(hal)):
        with patterns:

            Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << hal[i]
          
            hanlist = []
            hanlist +=[han]

            rs = map(lambda x: 
                tab*level+'int '+x+'_rstate = '+x+' (' +x+'_cstate, '+x+'_pstate);', hanlist)
            mainCFile += rs

            pc = map(lambda x: 
                tab*level+x+'_pstate = '+x+'_cstate;', hanlist)
            mainCFile += pc

            cr = map(lambda x: 
                tab*level+x+'_cstate = '+x+'_rstate;', hanlist)
            mainCFile += cr


    mainCFile += [tab*level+'writeOutput();']
    level -= 1
    mainCFile += [tab*level+'}']
    mainCFile += [tab*level+'return 0;']
    mainCFile += ['}']


    '''
    for i in xrange(len(hal)):
        with patterns:
            #Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov) << ha[i]
            #for i in xrange(len(hal)):
            print "bbb"
            Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << hal[i]
            print "aaa"
            print sloc
        
            print han
      

            print "iiiiiiiiiii"
            #print "list han"
            #print type(han)

            # Append the step-size and step declarations

            # Make the main function
            #mainCFile += makeMain(list(sloc), list(han), list(contSet))
            sloclist = []
            hanlist = []
            #print type(sloc), type(list(sloc))
            sloclist += [sloc]
            hanlist +=[han]
            print type(sloclist)
            #mainCFile += makeMain(list(sloc), list(han))
            #mainCFile += makeMain(sloclist, hanlist)

            mainCFile += makeMain(sloclist, hanlist)
            print "tmain"
            print type(mainCFile)
            '''

    # This is the final set, write to files
    # with open(han+".c", 'w') as cFile:
    with open("main.c", 'w') as cFile:
        cFile.write('\n\n'.join(mainCFile))

    '''
            # Write the header files out
            for i in xrange(len(hns)):
                with open(hns[i], 'w') as f:
                    f.write(hcs[i])
    '''
