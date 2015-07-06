import controller
import plant
import shac

ha = shac.comp([controller.controller, plant.plant])
shac.compile(ha, COMPOSED=True, ABOF=True)
