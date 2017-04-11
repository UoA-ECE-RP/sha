#ifndef SLOW1_AV_H_
#define SLOW1_AV_H_

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
} Slow1_AV;

// Initialization function
void Slow1_AVInit(Slow1_AV* me);

// Execution function
void Slow1_AVRun(Slow1_AV* me);

#endif // SLOW1_AV_H_
