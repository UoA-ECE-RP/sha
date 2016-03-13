#ifndef LVA_LVS_H_
#define LVA_LVS_H_

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
} LVA_LVS;

// Initialization function
void LVA_LVSInit(LVA_LVS* me);

// Execution function
void LVA_LVSRun(LVA_LVS* me);

#endif // LVA_LVS_H_
