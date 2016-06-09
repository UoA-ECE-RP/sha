# Author : Kawsihen Elankumaran
# Author : Jin Chen

# This is the compiler from Hybrid Automata in Python to IEC-61499 in XML

from lxml import etree
from sympy import dsolve, N
from sympy.solvers import solve
from random import randint  

import macropy.activate
import language
import gen 
import uuid
#import pdb

def compileToCFB(haList, interface, outPath):
    ids = {}
    CFB = etree.Element('compositeFunctionBlockModel', Name='CFBlock', Comment='Combined function block')
    IDENT = etree.SubElement(CFB, 'Identification', Standard='61499')
    VERSIONINFO = etree.SubElement(CFB, 'VersionInfo', Organization='Jin_s Macintosh', Version='1.0', Author='Jin Chen', Date='06/06/2016 13:00 PM', modelType='Composite')

    #---------------------------------------
    # Building functionBlockInterface 
    #---------------------------------------
    functionBlockInterface = etree.SubElement(CFB, 'functionBlockInterface')
    cFBModelHasFBInterface = etree.SubElement(functionBlockInterface, 'cFBModelHasFBInterface')
    Interface = etree.SubElement(cFBModelHasFBInterface, 'functionBlockInterface', name=interface.sysName, x="1006.25", y="962.5", modelType="Composite")

    events = etree.SubElement(Interface, 'events')
    variables = etree.SubElement(Interface, 'variables')
    inputEventPorts = etree.SubElement(Interface, 'inputEventPorts')
    outputEventPorts = etree.SubElement(Interface, 'outputEventPorts')
    inputVariablePorts = etree.SubElement(Interface, 'inputVariablePorts')
    outputVariablePorts = etree.SubElement(Interface, 'outputVariablePorts')

    for ExposedInterface in interface.exposedInterface:
        module_name, interface_Type, value_Type, interface_Name = ExposedInterface.split("/")
        if(interface_Type == "inputEvent"):
            functionBlockHasEvents = etree.SubElement(events, 'functionBlockHasEvents')
            event = etree.SubElement(functionBlockHasEvents, 'event', name=ExposedInterface, scope='Input')

            functionBlockHasInputEventPorts = etree.SubElement(inputEventPorts, 'functionBlockHasInputEventPorts')
            inputEventPort = etree.SubElement(functionBlockHasInputEventPorts, 'inputEventPort')
            proxyTargetPorts = etree.SubElement(inputEventPort, 'proxyTargetPorts')
            proxyConnection = etree.SubElement(proxyTargetPorts, 'proxyConnection')
            eventId=str(uuid.uuid4())
            for connection in interface.connectionList:
                if(connection.inputName == module_name + '/Event/' + interface_Name):
                    eventId=str(connection.inputId)
            ids[module_name+"/"+interface_Type+"/"+interface_Name] = eventId
            inputEventPortMoniker = etree.SubElement(proxyConnection, 'inputEventPortMoniker', Id=eventId)
            inputEventPort_event = etree.SubElement(inputEventPort, 'event')
            inputEventPortReferencesEvent = etree.SubElement(inputEventPort_event, 'inputEventPortReferencesEvent')
            eventMoniker = etree.SubElement(inputEventPortReferencesEvent, 'eventMoniker', name=ExposedInterface)

        elif(interface_Type == "outputEvent"):
            functionBlockHasEvents = etree.SubElement(events, 'functionBlockHasEvents')
            event = etree.SubElement(functionBlockHasEvents, 'event', name=ExposedInterface, scope='Output')

            functionBlockHasOutputEventPorts = etree.SubElement(outputEventPorts, 'functionBlockHasOutputEventPorts')
            outputEventPort = etree.SubElement(functionBlockHasOutputEventPorts, 'outputEventPort')
            proxyTargetPorts = etree.SubElement(outputEventPort, 'proxyTargetPorts')
            proxyConnection = etree.SubElement(proxyTargetPorts, 'proxyConnection')
            eventId=str(uuid.uuid4())
            for connection in interface.connectionList:
                if(connection.inputName == module_name + '/Event/' + interface_Name):
                    eventId=str(connection.inputId)
            ids[module_name+"/"+interface_Type+"/"+interface_Name] = eventId
            outputEventPortMoniker = etree.SubElement(proxyConnection, 'outputEventPortMoniker', Id=eventId)
            outputEventPort_event = etree.SubElement(outputEventPort, 'event')
            outputEventPortReferencesEvent = etree.SubElement(outputEventPort_event, 'outputEventPortReferencesEvent')
            eventMoniker = etree.SubElement(outputEventPortReferencesEvent, 'eventMoniker', name=ExposedInterface)

        elif(interface_Type == "inputVariable"):
            functionBlockHasVariables = etree.SubElement(variables, 'functionBlockHasVariables')
            variable = etree.SubElement(functionBlockHasVariables, 'variable', name=ExposedInterface, scope='Input', type=value_Type)

            functionBlockHasInputVariablePorts = etree.SubElement(inputVariablePorts, 'functionBlockHasInputVariablePorts')
            inputVariablePort = etree.SubElement(functionBlockHasInputVariablePorts, 'inputVariablePort')
            proxyTargetPorts = etree.SubElement(inputVariablePort, 'proxyTargetPorts')
            proxyConnection = etree.SubElement(proxyTargetPorts, 'proxyConnection')
            variableId=str(uuid.uuid4())
            for connection in interface.connectionList:
                if(connection.inputName == module_name + '/Variable/' + interface_Name):
                    variableId=str(connection.inputId)
            ids[module_name+"/"+interface_Type+"/"+interface_Name] = variableId
            inputVariablePortMoniker = etree.SubElement(proxyConnection, 'inputVariablePortMoniker', Id=variableId)
            inputVariablePort_variable = etree.SubElement(inputVariablePort, 'variable')
            inputVariablePortReferencesVariable = etree.SubElement(inputVariablePort_variable, 'inputVariablePortReferencesVariable')
            variableMoniker = etree.SubElement(inputVariablePortReferencesVariable, 'variableMoniker', name=ExposedInterface)

        else:
            functionBlockHasVariables = etree.SubElement(variables, 'functionBlockHasVariables')
            variable = etree.SubElement(functionBlockHasVariables, 'variable', name=ExposedInterface, scope='Output', type=value_Type)

            functionBlockHasOutputVariablePorts = etree.SubElement(outputVariablePorts, 'functionBlockHasOutputVariablePorts')
            outputVariablePort = etree.SubElement(functionBlockHasOutputVariablePorts, 'outputVariablePort')
            proxyTargetPorts = etree.SubElement(outputVariablePort, 'proxyTargetPorts')
            proxyConnection = etree.SubElement(proxyTargetPorts, 'proxyConnection')
            variableId=str(uuid.uuid4())
            for connection in interface.connectionList:
                if(connection.inputName == module_name + '/Variable/' + interface_Name):
                    variableId=str(connection.inputId)
            ids[module_name+"/"+interface_Type+"/"+interface_Name] = variableId
            outputVariablePortMoniker = etree.SubElement(proxyConnection, 'outputVariablePortMoniker', Id=variableId)
            outputVariablePort_variable = etree.SubElement(outputVariablePort, 'variable')
            outputVariablePortReferencesVariable = etree.SubElement(outputVariablePort_variable, 'outputVariablePortReferencesVariable')
            variableMoniker = etree.SubElement(outputVariablePortReferencesVariable, 'variableMoniker', name=ExposedInterface)

    #---------------------------------------
    # Building functionBlockReferences 
    #---------------------------------------
    functionBlockReferences = etree.SubElement(CFB, 'functionBlockReferences')
    for ha in haList:
        ha_model = ha
        cFBModelHasFBReferences = etree.SubElement(functionBlockReferences, 'cFBModelHasFBReferences')
        functionBlockReference = etree.SubElement(cFBModelHasFBReferences, 'functionBlockReference', name=ha.name, x="1531.25", y="218.75", creationMode="Resource", referencedFile=ha.name + ".fb")

        functionBlockReferences_events = etree.SubElement(functionBlockReference, 'events')
        functionBlockReferences_variables = etree.SubElement(functionBlockReference, 'variables')
        functionBlockReferences_inputEventPorts = etree.SubElement(functionBlockReference, 'inputEventPorts')
        functionBlockReferences_outputEventPorts = etree.SubElement(functionBlockReference, 'outputEventPorts')
        functionBlockReferences_inputVariablePorts = etree.SubElement(functionBlockReference, 'inputVariablePorts')
        functionBlockReferences_outputVariablePorts = etree.SubElement(functionBlockReference, 'outputVariablePorts')

        for ext_inp_eve, asso_vars in ha_model.rest[0].externalInputEvents.iteritems():
            functionBlockHasEvents = etree.SubElement(functionBlockReferences_events, 'functionBlockHasEvents')
            eventRef = etree.SubElement(functionBlockHasEvents, 'eventRef', Name=ext_inp_eve.name, scope="Input")

            functionBlockHasInputEventPorts = etree.SubElement(functionBlockReferences_inputEventPorts, 'functionBlockHasEvents')
            eventId=""
            for connection in interface.connectionList:
                if(connection.inputName == ha.name + '/Event/' + ext_inp_eve.name):
                    eventId = str(connection.inputId)
            if(eventId==""):
                if(ids.has_key(ha.name + '/inputEvent/' + ext_inp_eve.name)):
                    eventId = ids[ha.name + '/inputEvent/' + ext_inp_eve.name]
            inputEventPort = etree.SubElement(functionBlockHasInputEventPorts, 'inputEventPort', Id=eventId)
            event = etree.SubElement(inputEventPort, 'event')
            inputEventPortReferencesEvent = etree.SubElement(event, 'inputEventPortReferencesEvent')
            eventRefMoniker = etree.SubElement(inputEventPortReferencesEvent, 'eventRefMoniker', name=interface.sysName+"/"+ha.name+"/"+ext_inp_eve.name)

        for ext_outp_eve, asso_vars in ha_model.rest[0].externalOutputEvents.iteritems():
            functionBlockHasEvents = etree.SubElement(functionBlockReferences_events, 'functionBlockHasEvents')
            eventRef = etree.SubElement(functionBlockHasEvents, 'eventRef', Name=ext_outp_eve.name, scope="Output")

            functionBlockHasOutputEventPorts = etree.SubElement(functionBlockReferences_outputEventPorts, 'functionBlockHasOutputEventPorts')
            eventId=str(uuid.uuid4())
            if(ids.has_key(ha.name + '/outputEvent/' + ext_outp_eve.name)):
                    eventId = ids[ha.name + '/outputEvent/' + ext_outp_eve.name]
            outputEventPort = etree.SubElement(functionBlockHasOutputEventPorts, 'outputEventPort', Id=eventId)
            for connection in interface.connectionList:
                if(connection.outputName == ha.name + '/Event/' + ext_outp_eve.name):
                    wireTargetPorts = etree.SubElement(outputEventPort, 'wireTargetPorts')
                    wireConnection = etree.SubElement(wireTargetPorts, 'wireConnection', unitDelayed="false")
                    inputEventPortMoniker = etree.SubElement(wireConnection, 'inputEventPortMoniker', Id=str(connection.inputId))
            event = etree.SubElement(outputEventPort, 'event')
            outputEventPortReferencesEvent = etree.SubElement(event, 'outputEventPortReferencesEvent')
            eventRefMoniker = etree.SubElement(outputEventPortReferencesEvent, 'eventRefMoniker', name=interface.sysName+"/"+ha.name+"/"+ext_outp_eve.name)

        for ext_inp_var in ha_model.rest[1].externalInputVars:
            functionBlockHasVariables = etree.SubElement(functionBlockReferences_variables, 'functionBlockHasVariables')
            variableRef = etree.SubElement(functionBlockHasVariables, 'variableRef', Name=ext_inp_var.name, scope="Input", type=ext_inp_var.type)

            functionBlockHasInputVariablePorts = etree.SubElement(functionBlockReferences_inputVariablePorts, 'functionBlockHasInputVariablePorts')
            variableId=""
            for connection in interface.connectionList:
                if(connection.inputName == ha.name + '/Variable/' + ext_inp_var.name):
                    variableId=str(connection.inputId)
            if(variableId==""):
                if(ids.has_key(ha.name + '/inputVariable/' + ext_inp_var.name)):
                    variableId = ids[ha.name + '/inputVariable/' + ext_inp_var.name]
            inputVariablePort = etree.SubElement(functionBlockHasInputVariablePorts, 'inputVariablePort', Id=variableId)
            variable = etree.SubElement(inputVariablePort, 'variable')
            inputVariablePortReferencesVariable = etree.SubElement(variable, 'inputVariablePortReferencesVariable')
            variableRefMoniker = etree.SubElement(inputVariablePortReferencesVariable, 'variableRefMoniker', name=interface.sysName+"/"+ha.name+"/"+ext_inp_var.name)

        for ext_outp_var in ha_model.rest[1].externalOutputVars:
            functionBlockHasVariables = etree.SubElement(functionBlockReferences_variables, 'functionBlockHasVariables')
            variableRef = etree.SubElement(functionBlockHasVariables, 'variableRef', Name=ext_outp_var.name, scope="Output", type=ext_outp_var.type)

            functionBlockHasOutputVariablePorts = etree.SubElement(functionBlockReferences_outputVariablePorts, 'functionBlockHasOutputVariablePorts')
            variableId=str(uuid.uuid4())
            if(ids.has_key(ha.name + '/outputVariable/' + ext_outp_var.name)):
                variableId = ids[ha.name + '/outputVariable/' + ext_outp_var.name]
            outputVariablePort = etree.SubElement(functionBlockHasOutputVariablePorts, 'outputVariablePort', Id=variableId)
            for connection in interface.connectionList:
                if(connection.outputName == ha.name + '/Variable/' + ext_outp_var.name):
                    wireTargetPorts = etree.SubElement(outputVariablePort, 'wireTargetPorts')
                    wireConnection = etree.SubElement(wireTargetPorts, 'wireConnection', unitDelayed="false")
                    inputVariablePortMoniker = etree.SubElement(wireConnection, 'inputVariablePortMoniker', Id=str(connection.inputId))
            variable = etree.SubElement(outputVariablePort, 'variable')
            outputVariablePortReferencesVariable = etree.SubElement(variable, 'outputVariablePortReferencesVariable')
            variableRefMoniker = etree.SubElement(outputVariablePortReferencesVariable, 'variableRefMoniker', name=interface.sysName+"/"+ha.name+"/"+ext_outp_var.name)

    # writing the generated XML tree to the output file
    fHandle = open(outPath +'cjtest.cfb','w')

    fHandle.write('<?xml version="1.0" encoding="UTF-8"?>\n')

    fHandle.write(etree.tostring(CFB, pretty_print=True))

    fHandle.close()


def compileToFBT(ha, outPath):
    ha_model = ha
    #pdb.set_trace()
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
        EVENT1 = etree.SubElement(EVENTINPUTS, 'Event', Name=ext_inp_eve.name , Comment='')

        for asso_var in asso_vars:
            WITH1 = etree.SubElement(EVENT1, 'With', Var=str(asso_var['variableName']))  

    # input update clock and associations with all input variables
    EVENT = etree.SubElement(EVENTINPUTS, 'Event', Name='update_in' , Comment='')

    for ext_inp_var in ha_model.rest[1].externalInputVars:
        WITH = etree.SubElement(EVENT, 'With', Var=str(ext_inp_var))  

    # output events and their associated variables
    EVENTOUTPUTS = etree.SubElement(INTERFACELIST, 'EventOutputs')

    for ext_outp_eve, asso_vars in ha_model.rest[0].externalOutputEvents.iteritems():

        EVENT2 = etree.SubElement(EVENTOUTPUTS, 'Event', Name=ext_outp_eve.name, Comment='')
        
        for asso_var in asso_vars:
            WITH2 = etree.SubElement(EVENT2, 'With', Var=str(asso_var['variableName']))

    # output update clock and associations with all output variables
    EVENT = etree.SubElement(EVENTOUTPUTS, 'Event', Name='update_out' , Comment='')

    for ext_outp_var in ha_model.rest[1].externalOutputVars:
        WITH = etree.SubElement(EVENT, 'With', Var=str(ext_outp_var.name))  

    # input variables
    INPUTVARS = etree.SubElement(INTERFACELIST, 'InputVars')

    for ext_inp_var in ha_model.rest[1].externalInputVars:
        VARDECLARATION1 = etree.SubElement(INPUTVARS, 'VarDeclaration', Name=str(ext_inp_var.name), Type=ext_inp_var.type, Comment='')

    # output variables
    OUTPUTVARS = etree.SubElement(INTERFACELIST, 'OutputVars')

    for ext_outp_var in ha_model.rest[1].externalOutputVars:
        VARDECLARATION2 = etree.SubElement(OUTPUTVARS, 'VarDeclaration', Name=str(ext_outp_var.name), Type=ext_outp_var.type, Comment='')

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
    #pdb.set_trace()
    for edge in ha_model.edges:

        ECSTATE = etree.SubElement(ECC, 'ECState', Name='t_state'+str(i), Comment='', x=str(randint(0,2000)), y=str(randint(0,2000)))

        ECACTION = etree.SubElement(ECSTATE, 'ECAction', Algorithm='t_state'+str(i)+'Algo' , Output='')

        ALGORITHM = etree.SubElement(BASICFB, 'Algorithm', Name='t_state'+str(i)+'Algo', Comment='')

        # extracting the updates and adding them as algorithms to the intermediate states
        update_str = ''
        
        for update in edge.updateList:
            #pdb.set_trace()
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
            condition_str1 = condition_str1 + event.name + ' && '  
        
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
    fHandle = open(outPath + ha_model.name +'.fbt','w')

    fHandle.write('<?xml version="1.0" encoding="UTF-8"?>\n')

    fHandle.write(etree.tostring(FBTYPE, pretty_print=True))

    fHandle.close()
