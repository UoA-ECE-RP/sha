#ifndef SLOW_SLOW1_H_
#define SLOW_SLOW1_H_

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
} Slow_Slow1;

// Initialization function
void Slow_Slow1Init(Slow_Slow1* me);

// Execution function
void Slow_Slow1Run(Slow_Slow1* me);

#endif // SLOW_SLOW1_H_
