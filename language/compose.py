import gen
from language import *
from macropy.experimental.pattern import macros, _matching, switch, patterns, LiteralMatcher, TupleMatcher, PatternMatchException, NameMatcher, ListMatcher, PatternVarConflict, ClassMatcher, WildcardMatcher
from itertools import *


def compile2SHA(ha):
    return gen.preprocess(ha)


def getShaEdges(sha):
    with patterns:
        Ha(n, ss, sss, e, gvs, igvs) << sha
        rets = [None]*len(e)
        for i, s in enumerate(e):
            with patterns:
                Edge(l1, l2, guard, updateList, eventList) << s
                rets[i] = Edge(n+'_'+l1, n+'_'+l2,
                               guard, updateList, eventList)
        return rets


def getShaLocations(sha):
    with patterns:
        Ha(n, ss, sss, e, gvs, igvs) << sha
        rets = [None]*len(ss)
        for i, s in enumerate(ss):
            with patterns:
                Loc(name, odeList, combinatorList, invariant) << s
                rets[i] = Loc(n+'_'+name, odeList, combinatorList, invariant)
        return rets


def compose(haList):
    # First generate the SHA
    shas = ([compile2SHA(r) for r in haList])

    name = []
    newgvs = []
    newigvs = []
    nsss = []
    for sha in shas:
        with patterns:
            Ha(n, ss, sss, e, gvs, igvs) << sha
            newgvs += gvs
            newigvs += igvs
            name += [n]
            with patterns:
                Loc(lname, odeList, combinatorList, invariant) << sss
                nsss += [n+'_'+lname]
    ha_name = '_'.join(name)
    init_loc_name = '_'+'_'.join(nsss)
    init_loc = None

    # get states
    states = [getShaLocations(s) for s in shas]
    pset = list(product(*states))
    newLoc = [None]*len(pset)
    newLocNames = [None]*len(pset)
    for ii, i in enumerate(pset):
        newLocname = ''
        newLocodeList = []
        newLoccList = []
        newLocinvsdict = {}
        for loc in i:
            with patterns:
                Loc(name, odeList, cList, invs) << loc
                newLocname += '_'+name
                newLocodeList += odeList
                newLoccList += cList
                #newLocinvsdict.update(invs)
                for k in invs.iterkeys():
                    if k in newLocinvsdict.keys() and invs[k] != newLocinvsdict[k]:
                        for jk in invs[k]:
                            newLocinvsdict[k].append(jk)
                    else:
                        newLocinvsdict.update(invs)
        newLocNames[ii] = newLocname
        newLoc[ii] = Loc(newLocname, newLocodeList,
                         newLoccList, newLocinvsdict)
        if newLocname == init_loc_name:
            init_loc = newLoc[ii]

    # Now build the edges
    edges = [getShaEdges(s) for s in shas]
    pset = list(product(*edges))
    newEdges = [None]*len(pset)
    for ii, i in enumerate(pset):
        nl1 = ''
        nl2 = ''
        nguards = {}
        nupdateList = []
        neventList = []
        for edge in i:
            with patterns:
                Edge(l1, l2, guards, updateList, eventList) << edge
                nl1 += '_'+l1
                nl2 += '_'+l2
                nupdateList += updateList
                neventList += eventList
                # Dictionaries need to be handeled correctly
                for k in guards.iterkeys():
                    if k in nguards.keys() and guards[k] != nguards[k]:
                        for jk in guards[k]:
                            nguards[k].append(jk)
                    else:
                        nguards.update(guards)
        newEdges[ii] = Edge(nl1, nl2, nguards, nupdateList, neventList)

    # Making the xtra edges
    names = []
    same_edge_names = []
    for edges in pset:
        for edge in edges:
            with patterns:
                Edge(l1, l2, u, r) << edge
                names += [l1, l2]
                same_edge_names += [(l1, l2)]
    names = set(names)
    same_edge_names = set(same_edge_names)
    name_permutations = permutations(names, len(pset[0]))
    res = []
    for i in name_permutations:
        there = False
        for (x, y) in same_edge_names:
            if x in i and y in i:
                there = True
                break
        if not there:
            res += [i]

    # Now make the init_state and dest_state
    xtraEdges = []
    for edges in pset:
        counter = 0
        for edge in edges:
            if counter > 0:
                break
            counter += 1
            oedges = filter(lambda x: x != edge, edges)
            with patterns:
                Edge(l1, l2, myg, myu, mye) << edge
                init_name = [l1]
                dest_name = [l2]
                all_others = [l1, l2]
                for oe in oedges:
                    with patterns:
                        Edge(on1, on2, ou, ur) << oe
                        init_name += [on1]
                        dest_name += [on2]
                        all_others += [on1, on2]
                # Get all the permutations that contain me or my
                # destination
                pps = []
                for pp in res:
                    there = True
                    for p in pp:
                        if p not in all_others:
                            there = False
                            break
                    if there:
                        pps += [pp]
                # Remove all permutation elements that are the same as
                # the init_name
                pps = filter(lambda x: sorted(x) != sorted(tuple(init_name)),
                             pps)
                pps = filter(lambda x: sorted(x) != sorted(tuple(dest_name)),
                             pps)
                # Finally remove all the names that are not in the
                # states! They are just extras!!
                pps = filter(lambda x: '_'+'_'.join(x) in newLocNames, pps)
                # Now we can finally build these xtraEdges
                nl1 = '_' + '_'.join(init_name)
                for pp in pps:
                    nl2 = ''
                    nguards = {}
                    nupdateList = []
                    neventList = []
                    for p in pp:
                        nl2 += '_'+p
                        # This means the combined destination state
                        # contains edges destination state
                        if p == l2:
                            nupdateList += myu
                            # These are the updates from other
                            # locations!
                            for oe in oedges:
                                with patterns:
                                    Edge(ol1, ol2, og, ou, oev) << oe
                                    for uu in ou:
                                        with switch(uu):
                                            if Update.Update2(x):
                                                nupdateList += [uu]
                            neventList += mye
                            for k in myg.iterkeys():
                                if k in nguards.keys() and myg[k] != nguards[k]:
                                    for jm in myg[k]:
                                        nguards[k].append(jm)
                                    print nguards[k]
                                else:
                                    nguards.update(myg)
                        else:
                            for oe in oedges:
                                with patterns:
                                    Edge(ol1, ol2, oguards, oupdateList,
                                         oeventList) << oe
                                    if ol2 == p:
                                        nupdateList += oupdateList
                                        neventList += oeventList
                                        for k in oguards.iterkeys():
                                            if k in nguards.keys() and oguards[k] != nguards[k]:
                                                for jo in oguards:
                                                    nguards[k].append(jo)
                                                print nguards[k]
                                            else:
                                                nguards.update(oguards)
                                    else:
                                        for uu in oupdateList:
                                            with switch(uu):
                                                if Update.Update2(x):
                                                    nupdateList += [uu]
                            # These are the edges updates!
                            for uu in myu:
                                with switch(uu):
                                    if Update.Update2(x):
                                        nupdateList += [uu]
                    xtraEdges += [Edge(nl1, nl2,
                                       nguards, nupdateList, neventList)]
    # Now make the name of the Ha to be returned
    return Ha(ha_name, newLoc, init_loc,
              newEdges+xtraEdges, newgvs, newigvs)
