# This is the compiler main module
import gen
import sys


def compile(ha, **kwargs):
    # Step-1: Make sure that the hybrid automaton is well-formed
    if gen.isWha(ha):
        # Step-2 get a new ha with the Nsteps for each loc computed
        # FIXME: Nsteps might be None in the general case
        sha = gen.getSha(ha)
        # Step-3 generate code
        if sha is None:
            raise "Cannot generate code!"
        else:
            gen.codeGen(sha)


def main(argv):
    # Parse XML file
    # ha = parseHa(argv[0])
    ha = None
    compile(ha)


if __name__ == '__main__':
    main(sys.argv[1:])
