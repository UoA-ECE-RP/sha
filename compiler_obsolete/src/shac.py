#!/usr/bin/env python
import macropy.activate
import gen
import sys
import compose
import hajson
import HAIEC2


def comp(haList):
    return compose.compose(haList)


def compile(ha, **kwargs):
    # Step-1: Make sure that the hybrid automaton is well-formed
    if 'COMPOSED' not in kwargs:
        ha = gen.preprocess(ha)
    if 'ABOF' in kwargs and kwargs['ABOF']:
        gen.ALL_BETS_OFF = True
    if gen.isWha(ha):
        # Step-2 get a new ha with the Nsteps for each loc computed
        # FIXME: Nsteps might be None in the general case
        sha = gen.getSha(ha)
        if sha is None:
            raise "Cannot generate code!"
        else:
            gen.codeGen(sha)


def main(argv):
    # Parse JSON file
    ha = hajson.parseHA(argv[0])
    if argv[1] == 'fbt':
		HAIEC2.compileToFBT(ha, argv[2])
    else:
		compile(ha, ABOF=True)



if __name__ == '__main__':
    main(sys.argv[1:])
