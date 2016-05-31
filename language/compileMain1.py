# TODO: The codegen is not very efficient, because symbolic solutions
# are being regenerated every time

from macropy.experimental.pattern import macros, _matching, switch, patterns, LiteralMatcher, TupleMatcher, PatternMatchException, NameMatcher, ListMatcher, PatternVarConflict, ClassMatcher, WildcardMatcher
from languageNC1 import *

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

def codeGen(hal, blist):
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
    
    HL = []

    for i in xrange(len(hal)):
        with patterns:
        
            Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << hal[i]
          
            hanlist = []
            hanlist += [han]
            HL += [han]
         
            externInt = map(lambda x: 
            'extern int '+x+'(int, int);', hanlist)
            mainCFile += externInt  

    tab = ' '*2
    level = 1

    for i in xrange(len(hal)):
        with patterns:

            Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << hal[i]
            
            for m in xrange(len(eiv)):
                with patterns:
                    ExternalInputVar(eivname) << eiv[m]
                    mainCFile += ['extern double ' + han + '_' + eivname + ';']


            for n in xrange(len(eov)):
                with patterns:
                    ExternalOutputVar(eovname) << eov[n]
                    mainCFile += ['extern double ' + han + '_' + eovname + ';']

            for o in xrange(len(eie)):
                with patterns:
                    ExternalInputEvent(eiename) << eie[o]
                    mainCFile += ['extern double ' + han + '_' + eiename + ';']

            for p in xrange(len(eoe)):
                with patterns:
                    ExternalOutputEvent(eoename) << eoe[p]
                    mainCFile += ['extern double ' + han + '_' + eoename + ';']

    
    mainCFile += ['int main(void) {']


    for i in xrange(len(hal)):
        with patterns:

            Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << hal[i]
          
            hanlist = []
            hanlist +=[han]
            sloclist = []
            sloclist +=[sloc]

            ps = map(lambda x: 
                tab*level+'int '+x+'_pstate = -1;', hanlist)
            mainCFile += ps

            for i in xrange(len(sloclist)):
                with patterns:
                    Loc(name, ol, y, z) << sloclist[i]

                    namelist = []
                    namelist +=[name]
                    nameIndex = []

                    for n in xrange(len(namelist)):
                        nameIndex += [n]
                        print nameIndex
                        print hanlist

                    print"debug1"
                    print type(hanlist)
                    print type(name)
                    print namelist
                    cs = map(lambda x, y: 
                        tab*level+'int '+ x +'_cstate = '+ str(y) + ';', hanlist, nameIndex)
                    
                    mainCFile += cs


    mainCFile += [tab*level+'while(True) {']
    level += 1
    mainCFile += [tab*level+'readInput();']
    
    

           
    for i in xrange(len(hal)):
        with patterns:

            Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << hal[i]
          
            hanlist = []
            hanlist +=[han]
            print "listttttttttttttttttttttt"
            print hanlist

            rs = map(lambda x: 
                tab*level+'int '+x+'_rstate = '+x+' (' +x+'_cstate, '+x+'_pstate);', hanlist)
            mainCFile += rs

            pc = map(lambda x: 
                tab*level+x+'_pstate = '+x+'_cstate;', hanlist)
            mainCFile += pc

            cr = map(lambda x: 
                tab*level+x+'_cstate = '+x+'_rstate;', hanlist)
            mainCFile += cr

    for i in blist:
        with patterns:
            BindHa(source_ha, bindlist, dest_ha) << i
            with switch(bindlist):
                if Bind.Bind1(vsl, vdl):
                    if len(vsl) != len(vdl):
                        raise Exception("WRONG!!")
                    for i in vsl:
                        if not (i in source_ha.externalOutputVars):
                            raise Exception("WRONG!")
                    for i in vdl:
                        if not (i in dest_ha.externalInputVars):
                            raise Exception("WRONG!")
                    print vsl, vdl
                    for (i,j) in zip(vsl, vdl):
                        mainCFile += [tab*level+ source_ha.name + '_' + i.name + ' = ' + dest_ha.name + '_' + j.name + ';\n']
                elif Bind.Bind2(esl, edl):
                    if len(esl) != len(edl):
                        raise Exception("WRONG!!")
                    for i in esl:
                        if not (i in source_ha.externalOutputEvent):
                            raise Exception("WRONG!")
                    for i in edl:
                        if not (i in dest_ha.externalInputEvent):
                            raise Exception("WRONG!")
                    print esl, edl
                    for (i,j) in zip(esl, edl):
                        mainCFile += [tab*level+ source_ha.name + '_' + i.name + ' = ' + dest_ha.name + '_' + j.name + ';\n']
                else:
                    raise ("Unrecognized option: ", bindlist)


    '''       
    for i in xrange(len(hal)):
        with patterns:

            Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << hal[i]
          
            hanlist = []
            hanlist +=[han]
            hanlist2 = []
            #v1 = map(lambda x: x +'.' + x + '.externalOutputVars', hanlist)
            #v2 = map(lambda x: x +'.' + x + '.externalInputVars', hanlist)
            #V3 = map(lambda x: x +'.' + x + '.externalOutputEvent', hanlist)
            #v4 = map(lambda x: x +'.' + x + '.externalInputEvent', hanlist)

            v1 = map(lambda x: x +'.' + x, hanlist)
            
            if i == 0:
                hanlist2 = [hanlist[1:]]
            elif i == len(hal):
                hanlist2 = [hanlist[:len(hal)-1]]
            else:
                hanlist2 = [hanlist[0:i]]
                hanlist2 += [hanlist2[i:len(hal)]]

            for n in xrange(len(hal) - 1):


               
                v2 = map(lambda x: x +'.' + x, hanlist2)

                mainCFile += [tab*level+'bind' + i + n + ' = Bind.Bind1' + '(' + v1 + '.externalOutputVars,' + v2 + '.externalInputVars)']
                mainCFile += [tab*level+'bind' + i + n + ' = Bind.Bind2' + '(' + v1 + '.externalOutputEvent,' + v2 + '.externalInputEvent)']

                mainCFile += [tab*level+'blist' +  ' = [BindHa(' + v1 + ', bind1, ' + v2 + '), BindHa(' + v1 + ', bind2, ' + v2 + ')]']

                mainCFile += [tab*level+'link' + i + n + ' = zip(' + v1 + '.externalOutputVars', v2 + '.externalInputVars)'] 
                mainCFile += [tab*level+'link' + i + n + ' = zip(' + v1 + '.externalOutputEvent', v2 + '.externalInputEvent)'] 
    '''

    '''
    for i in xrange(len(hal)):
        with patterns:

            Ha(han, ls, sloc, edges, gvs, igvs, iv, eiv, eov, eie, eoe) << hal[i]
            print "hahahahahahahaaaaaaaaaaaaaaa"
            print hal
            #hanlisteiv = []
            #hanlisteiv +=[han]
            hanlisteov = []

            if i == 0:
                hanlisteov = hal[1:len(hal)]
            elif i == len(hal)-1:
                hanlisteov = hal[:len(hal)-1]
            else:
                hanlisteov = hal[0:i]
                hanlisteov += hal[i+1:len(hal)]

            #print "ssssssss"
            #print hanlisteiv
            #print hanlisteov
            #cr = map(lambda x, y: 
             #   tab*level+ x + '_' + y + ' = '+x+'_rstate;', hanlist)
            
            for m in xrange(len(eiv)):
                with patterns:
                    ExternalInputVar(eivname) << eiv[m]
                    #print type(eivname)
                    #print type(han)

                    #linkVars = [tab*level+ han + '_' + eivname + ';']
                    #mainCFile += linkVars
                    
                    print "input signal name:", eiv[m], "for ha:", han, len(eiv)

            #print hal
            #print hanlisteov             
                    
                    for n in xrange(len(hanlisteov)):
                        with patterns:
                            print n, len (hanlisteov)
                            Ha(haneov, ls, sloc, edges, gvs, igvs, iv, eiv2, eov, eie, eoe) << hanlisteov[n]

                            print "output signal list:", eov, "for ha:", haneov, len(eov)
                            if len (eiv) != len(eov):
                                raise Exception ("Input and output lengths not equal for ha:")
                            
                            with patterns:
                                ExternalOutputVar(eovname) << eov[m]
                                linkVars2 = [tab*level+ han + '_' + eivname + ' = ' + haneov + '_' + eovname + ';']

                                #cnn = map(lambda x, y: tab*level+ x + '_' + y + ';', han, eivname)
                                mainCFile += linkVars2

             '''          

            #ExternalOutputVar(name)
            #ExternalInputEvent(name)
            #ExternalOutputEvent(name)




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
