import train
import gate
import shac

ha = shac.comp([train.train, gate.gate])
shac.compile(ha, COMPOSED=True, ABOF=True)
