// This file is generated by FBC.

#ifndef WATERTANK_H_
#define WATERTANK_H_

#include "fbtypes.h"
#include "Plant.h"
#include "Controler.h"

typedef struct {
    Plant Plant;
    Controler Controler;
} Watertank;

/* Function block initialization function */
void Watertankinit(Watertank* me);

/* Function block execution function */
void Watertankrun(Watertank* me);

#endif // WATERTANK_H_
