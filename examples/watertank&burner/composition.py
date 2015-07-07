import watertank
import burner
import shac

ha = shac.comp([watertank.watertank, burner.burner])
shac.compile(ha, COMPOSED=True, ABOF=True)
