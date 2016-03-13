#ifndef FAST_FAST1_H_
#define FAST_FAST1_H_

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
} Fast_Fast1;

// Initialization function
void Fast_Fast1Init(Fast_Fast1* me);

// Execution function
void Fast_Fast1Run(Fast_Fast1* me);

#endif // FAST_FAST1_H_
