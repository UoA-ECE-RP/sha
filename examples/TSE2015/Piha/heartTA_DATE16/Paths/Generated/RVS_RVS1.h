#ifndef RVS_RVS1_H_
#define RVS_RVS1_H_

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
} RVS_RVS1;

// Initialization function
void RVS_RVS1Init(RVS_RVS1* me);

// Execution function
void RVS_RVS1Run(RVS_RVS1* me);

#endif // RVS_RVS1_H_
