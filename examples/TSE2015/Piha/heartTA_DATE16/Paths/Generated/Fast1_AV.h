#ifndef FAST1_AV_H_
#define FAST1_AV_H_

#include <stdlib.h>
#include <stdio.h>
#include "../../Generic/step.h"
#include "../States.h"


// Cell Data Struct
typedef struct {


	// Outputs
	char ACTcell;

	// Inputs
	char ACTpath;

	// Internal Variables
	 int t;
 	enum pathStates state; // State
} Fast1_AV;

// Initialization function
void Fast1_AVInit(Fast1_AV* me);

// Execution function
void Fast1_AVRun(Fast1_AV* me);

#endif // FAST1_AV_H_
