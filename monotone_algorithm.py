# Example of the water-tank system odes whose witness functions need to
# be monotone!

from sympy import *

t = Symbol('t')
x = Function('x')

# The odes in the water-tank example
K = Symbol('K')
h = Symbol('h')

odes = [dsolve(diff(x(t))-K*(h-x(t)), x(t)),
        dsolve(diff(x(t)), x(t)),
        dsolve(diff(x(t))+K*x(t), x(t)),
        dsolve(diff(x(t)), x(t))]

# Debug
map(lambda x: pprint(x), odes)

# TODO: There is no error checking here!
# Differentiate the symbolic solutions to get the slope
slopes = map(lambda x: x.rhs.diff(t), odes)

# Get the roots of the symbolic functions
ismonotones = map(lambda x: solve(x, t), slopes)

# Can the HA be solved?
if (reduce(lambda y, x: (x == []) and y, ismonotones, True) == True):
    print "All odes in HA are monotone"
else:
    print "HA cannot be solved"
