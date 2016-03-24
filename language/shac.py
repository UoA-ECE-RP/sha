#!/usr/bin/env python
import macropy.activate
import gen
import genChanged1
import sys
import compose
import hajson


def comp(haList):
    return compose.compose(haList)


def compile(ha, **kwargs):
    # Step-1: Make sure that the hybrid automaton is well-formed
    if 'COMPOSED' not in kwargs and 'Q' not in kwargs:
        #ha = gen.preprocess(ha)
        ha = genChanged1.preprocess(ha)
    if 'ABOF' in kwargs and kwargs['ABOF']:
        #gen.ALL_BETS_OFF = True
        genChanged1.ALL_BETS_OFF = True
    #if gen.isWha(ha):
    if genChanged1.isWha(ha):
        # Step-2 get a new ha with the Nsteps for each loc computed
        # FIXME: Nsteps might be None in the general case
        #sha = gen.getSha(ha)
        sha = genChanged1.getSha(ha)
        if sha is None:
            raise "Cannot generate code!"
        else:
            #gen.codeGen(sha)
            genChanged1.codeGen(sha)


def main(argv):
    # Parse JSON file
    ha = hajson.parseHA(argv[0])
    compile(ha, ABOF=True)


if __name__ == '__main__':
    main(sys.argv[1:])
