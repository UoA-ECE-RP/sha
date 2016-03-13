#ifndef LVS_LVS1_H_
#define LVS_LVS1_H_

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
} LVS_LVS1;

// Initialization function
void LVS_LVS1Init(LVS_LVS1* me);

// Execution function
void LVS_LVS1Run(LVS_LVS1* me);

#endif // LVS_LVS1_H_
