import cell
import path
import shac

for cHA in cell.cellHAs:
    print cHA;

for pHA in path.pathHAs:
    print pHA;

ha = shac.comp(cell.cellHAs+path.pathHAs);
shac.compile(ha, COMPOSED=True, ABOF=True)