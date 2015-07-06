import controler
import plant
import shac

ha = shac.comp([controler.controler, plant.plant])
shac.compile(ha, COMPOSED=True, ABOF=True)
