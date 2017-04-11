# Author : Kawsihen Elankumaran

# This is the compiler from Hybrid Automata in Python to IEC-61499 in XML

from lxml import etree
from sympy import dsolve, N
from sympy.solvers import solve
from random import randint  

import macropy.activate
import language 

# import the HA file here
import watertank

# import the Ha class from the HA file here
ha_model = watertank.waterTank

# put the complete path of the directory the output should be written to 
write_path = '/Users/kawsihenelankumaran/Desktop/Windows Shared/New Folder/'

FBTYPE = etree.Element('FBType', Name='FBlock', Comment='Basic function block')
IDENT = etree.SubElement(FBTYPE, 'Identification', Standard='61499')
VERSIONINFO = etree.SubElement(FBTYPE, 'VersionInfo', Organization='Kawsihen_s Macintosh', Version='1.0', Author='Kawsihen', Date='11/20/2015 9:00 AM', Remarks='')
COMPILERINFO = etree.SubElement(FBTYPE, 'CompilerInfo', header='package mypackage')
COMPILERINFO.text=''

#---------------------------------------
# Building the function block interface 
#---------------------------------------

INTERFACELIST = etree.SubElement(FBTYPE, 'InterfaceList')

# input events and their associated variables
EVENTINPUTS = etree.SubElement(INTERFACELIST, 'EventInputs')

for ext_inp_eve, asso_vars in ha_model.rest[0].externalInputEvents.iteritems():

	EVENT1 = etree.SubElement(EVENTINPUTS, 'Event', Name=ext_inp_eve.s , Comment='')

	for asso_var in asso_vars:
		WITH1 = etree.SubElement(EVENT1, 'With', Var=str(asso_var))  

# input update clock and associations with all input variables
EVENT = etree.SubElement(EVENTINPUTS, 'Event', Name='update_in' , Comment='')

for ext_inp_var in ha_model.rest[1].externalInputVars:
	WITH = etree.SubElement(EVENT, 'With', Var=str(ext_inp_var))  

# output events and their associated variables
EVENTOUTPUTS = etree.SubElement(INTERFACELIST, 'EventOutputs')

for ext_outp_eve, asso_vars in ha_model.rest[0].externalOutputEvents.iteritems():

	EVENT2 = etree.SubElement(EVENTOUTPUTS, 'Event', Name=ext_outp_eve.s, Comment='')
	
	for asso_var in asso_vars:
		WITH2 = etree.SubElement(EVENT2, 'With', Var=str(asso_var))

# output update clock and associations with all output variables
EVENT = etree.SubElement(EVENTOUTPUTS, 'Event', Name='update_out' , Comment='')

for ext_outp_var in ha_model.rest[1].externalOutputVars:
	WITH = etree.SubElement(EVENT, 'With', Var=str(ext_outp_var))  

# input variables
INPUTVARS = etree.SubElement(INTERFACELIST, 'InputVars')

for ext_inp_var in ha_model.rest[1].externalInputVars:
	VARDECLARATION1 = etree.SubElement(INPUTVARS, 'VarDeclaration', Name=str(ext_inp_var), Type='BOOL', Comment='')

# output variables
OUTPUTVARS = etree.SubElement(INTERFACELIST, 'OutputVars')

for ext_outp_var in ha_model.rest[1].externalOutputVars:
	VARDECLARATION2 = etree.SubElement(OUTPUTVARS, 'VarDeclaration', Name=str(ext_outp_var), Type='BOOL', Comment='')

#------------------------------
# Building ECC and Algorithms
#------------------------------

BASICFB = etree.SubElement(FBTYPE, 'BasicFB')

# declaring internl variables. d - step size  k - step counter
INTERNALVARS = etree.SubElement(BASICFB, 'InternalVars')
VARDECLARATION3 = etree.SubElement(INTERNALVARS, 'VarDeclaration', Name='k', Type='REAL', Comment='')
VARDECLARATION3 = etree.SubElement(INTERNALVARS, 'VarDeclaration', Name='d', Type='REAL', Comment='')

# declaring global variables from HA model
for gVar in ha_model.globalVars:
	VARDECLARATION3 = etree.SubElement(INTERNALVARS, 'VarDeclaration', Name=str(gVar), Type='REAL', Comment='')

# delcaring internal global variables form HA model
for igVar in ha_model.iglobalVars:
	VARDECLARATION3 = etree.SubElement(INTERNALVARS, 'VarDeclaration', Name=str(igVar), Type='REAL', Comment='')

ECC = etree.SubElement(BASICFB, 'ECC')

ECSTATE1 = etree.SubElement(ECC, 'ECState', Name='Start', Comment='',x=str(randint(0,2000)), y=str(randint(0,2000)))

internal_var_set = set()

for loc in ha_model.locations:

	# creating  the main states
	ECSTATE = etree.SubElement(ECC, 'ECState', Name=loc.name, Comment='', x=str(randint(0,2000)), y=str(randint(0,2000)))
	ECACTION = etree.SubElement(ECSTATE, 'ECAction', Algorithm=loc.name+'Algo' , Output='')

	ALGORITHM = etree.SubElement(BASICFB, 'Algorithm', Name=loc.name+'Algo', Comment='')

	solution_str = ''

	# solving the ODEs, discretizing them in time and adding them as algorithm to the states.
	for ode in loc.odeList:

		sol = dsolve(ode.expr, ode.var)

		# using the initial condition at t=0 to deduce the constant C1
		expr = str(sol.rhs).replace('t','0') + '-(' + str(ode.initValue) + ')'
		C1value = solve(expr, 'C1')
		C1soln_str = 'me->C1' + str(ode.var.func) + ' = ' + str(N(C1value[0], 5)) + ';\n'

		solution_str = solution_str + C1soln_str + str(sol).replace(str(ode.var)+' ==','me->'+  str(ode.var.func) + ' =').replace('t','me->d*me->k').replace('C1','(float) me->C1'+ str(ode.var.func)) + ';\n'
		
		internal_var_set.add(str(ode.var.func))

	# algorithm to increment the step counter in every cycle
	solution_str = solution_str + 'me->k++;'

	OTHER = etree.SubElement(ALGORITHM, 'Other', Language='C' , Text=solution_str)

# declaring the collected internal variables and constants of integration
for var in internal_var_set:
	VARDECLARATION3 = etree.SubElement(INTERNALVARS, 'VarDeclaration', Name=var, Type='REAL', Comment='')
	VARDECLARATION3 = etree.SubElement(INTERNALVARS, 'VarDeclaration', Name='C1'+var, Type='REAL', Comment='')

i = 1

# creating the start state
ECACTION1 = etree.SubElement(ECSTATE1, 'ECAction', Algorithm='init', Ouptput='')
ALGORITHM = etree.SubElement(BASICFB, 'Algorithm', Name='init', Comment='')

first_loc = ha_model.locations[0]

# initializing the varialbles needed for simulation
init_str = 'me->d = 0.01;\nme->k = 0;\n'

OTHER = etree.SubElement(ALGORITHM, 'Other', Language='C' , Text=init_str)
ECTRANSITION = etree.SubElement(ECC, 'ECTransition', Source='Start', Destination=first_loc.name, Condition='True', x=str(randint(0,2000)), y=str(randint(0,2000)))

# creating intermediate states
for edge in ha_model.edges:

	ECSTATE = etree.SubElement(ECC, 'ECState', Name='t_state'+str(i), Comment='', x=str(randint(0,2000)), y=str(randint(0,2000)))

	ECACTION = etree.SubElement(ECSTATE, 'ECAction', Algorithm='t_state'+str(i)+'Algo' , Output='')

	ALGORITHM = etree.SubElement(BASICFB, 'Algorithm', Name='t_state'+str(i)+'Algo', Comment='')

	# extracting the updates and adding them as algorithms to the intermediate states
	update_str = ''
	for update in edge.updateList:
		if(isinstance(update,language.Update.Update2)):
			update_str = update_str +  'me->' + str(update.x)  + ' = '+ 'me->' + str(update.y) + ';\n' 
		elif(isinstance(update,language.Update.Update1)):
			update_str = update_str +  'me->' + str(update.var)  + ' = '+ str(update.nat) + ';\n' 

	# reset the discrete counter during after transition
	update_str = update_str + 'me->k = 0;'

	OTHER = etree.SubElement(ALGORITHM, 'Other', Language='C' , Text=update_str)

	# buiding the condition strings for transition to and from the created intermediate state
	condition_str1 = ''

	# condition string for the events
	for event in edge.eventList:
		condition_str1 = condition_str1 + event.s + ' && '	
	
	if(condition_str1 == ''):
		condition_str1 = 'true && ' 

	condition_str2 = ''
	final_condition = ''

	# condition string for the guard conditions
	for condition_list in edge.guard.itervalues():
		for condition_element in condition_list:
				if(str(condition_element.relationalExpr) == 'True'): # multiple True unnecesssary
					continue
				condition_str2 = condition_str2 + str(condition_element.relationalExpr) + ' && '

	condition_str2 = condition_str2[:-4]

	if(condition_str2 != ''):
		final_condition = condition_str1 + ' (' + condition_str2 + ')'
	else:
		final_condition = condition_str1[:-4]

	# connecting the intermediate state to the existing states
	ECTRANSITION = etree.SubElement(ECC, 'ECTransition', Source=edge.l1, Destination="t_state"+str(i), Condition=final_condition, x=str(randint(0,2000)), y=str(randint(0,2000)))

	ECTRANSITION = etree.SubElement(ECC, 'ECTransition', Source="t_state"+str(i), Destination=edge.l2, Condition="True", x=str(randint(0,2000)), y=str(randint(0,2000)))

	i = i+1

# creating self transitions
for loc in ha_model.locations:
	
	condition_str = ''

	# building the self transition condition 
	for condition_list in loc.invariant.itervalues():
		for condition_element in condition_list:
			condition_str = condition_str + str(condition_element.relationalExpr) + ' && '

	condition_str = condition_str[:-4]

	ECTRANSITION = etree.SubElement(ECC, 'ECTransition', Source=loc.name, Destination=loc.name, Condition=condition_str, x=str(randint(0,2000)), y=str(randint(0,2000)))

# writing the generated XML tree to the output file
fHandle = open(write_path + ha_model.name +'.fbt','w')

fHandle.write('<?xml version="1.0" encoding="UTF-8"?>\n')

fHandle.write(etree.tostring(FBTYPE, pretty_print=True))

fHandle.close()
