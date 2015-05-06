# Example of the water-tank system odes whose witness functions
# need to be monotone including C code generation!

from sympy import *
from sympy.utilities.codegen import codegen


C1 = Symbol('C1')
t = Symbol('t')
x = Function('x')

# The initial conditions for the odes
inits = [20, 100, 100, 20]

# The odes in the water-tank example

# These should come in from Ocaml as sexpressions
odes = [dsolve(diff(x(t))-100*(2-x(t)), x(t), ics={x(0): 20}),
        dsolve(diff(x(t)), x(t), ics={x(0): 100}),
        dsolve(diff(x(t))+100*x(t), x(t), ics={x(0): 100}),
        dsolve(diff(x(t)), x(t), ics={x(0): 20})]

# Solve the initial condition
initcs = [None]*len(odes)
for i in range(0, len(odes)):
    initcs[i] = (solve(odes[i].subs([(x(t), inits[i]), (t, 0)]),
                       Symbol('C1')))[0]
# Backsubstitue for C1
odess = [None]*len(odes)
for i in range(0, len(odes)):
    odess[i] = odes[i].subs(C1, initcs[i])

# TODO: There is no error checking here!
# Differentiate the symbolic solutions to get the slope
slopes = map(lambda x: x.rhs.diff(t), odess)

# Get the roots of the symbolic functions
ismonotones = map(lambda x: solve(x, t), slopes)

# Can the HA be solved?
if (reduce(lambda y, x: (x == []) and y, ismonotones, True) == True):
    print "All odes in HA are monotone"
else:
    print "HA cannot be solved"

funcs = [None]*len(odess)
for i in range(0, len(odess)):
    funcs[i] = "ode"+str(i+1), odess[i].rhs

print funcs

# Need to produce 'C' code from odess
[(c_name, c_code), (h_name, h_header)] = codegen(funcs, "C", "odes",
                                                 header=False,
                                                 empty=False)

# Debug
print(c_name)
print(c_code)

print(h_name)
print(h_header)
