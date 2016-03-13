#ifndef LVA_LV_H_
#define LVA_LV_H_

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
} LVA_LV;

// Initialization function
void LVA_LVInit(LVA_LV* me);

// Execution function
void LVA_LVRun(LVA_LV* me);

#endif // LVA_LV_H_
