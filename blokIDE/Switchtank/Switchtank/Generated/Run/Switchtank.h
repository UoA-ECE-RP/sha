// This file is generated by FBC.

#ifndef SWITCHTANK_H_
#define SWITCHTANK_H_

#include "fbtypes.h"
#include "Controller.h"
#include "Plant.h"

typedef struct {
    Controller Controller;
    Plant Plant;
} Switchtank;

/* Function block initialization function */
void Switchtankinit(Switchtank* me);

/* Function block execution function */
void Switchtankrun(Switchtank* me);

#endif // SWITCHTANK_H_
