// This file is generated by FBC.

#ifndef PLANT_H_
#define PLANT_H_

#include "fbtypes.h"
#include "global.h"

typedef union {
    UDINT events;
    struct {
        UDINT clock : 1; // 
    } event;
} PlantIEvents;

typedef union {
    UDINT events;
    struct {
        UDINT update : 1; // 
    } event;
} PlantOEvents;

typedef struct {
    UINT _state;
    BOOL _entered;
    PlantIEvents _input;
    INT fill1; // 
    INT _fill1;
    INT fill2; // 
    INT _fill2;
    PlantOEvents _output;
    REAL x1; // 
    REAL _x1;
    REAL x2; // 
    REAL _x2;
} Plant;

/* Function block initialization function */
void Plantinit(Plant* me);

/* Function block execution function */
void Plantrun(Plant* me);

/* ECC algorithms */
void Plant_init(Plant* me);
void Plant_generated_c_code(Plant* me);

#endif // PLANT_H_
