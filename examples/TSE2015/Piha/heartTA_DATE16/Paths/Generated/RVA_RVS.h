#ifndef RVA_RVS_H_
#define RVA_RVS_H_

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
} RVA_RVS;

// Initialization function
void RVA_RVSInit(RVA_RVS* me);

// Execution function
void RVA_RVSRun(RVA_RVS* me);

#endif // RVA_RVS_H_
