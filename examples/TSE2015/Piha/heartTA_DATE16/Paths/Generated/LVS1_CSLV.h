#ifndef LVS1_CSLV_H_
#define LVS1_CSLV_H_

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
} LVS1_CSLV;

// Initialization function
void LVS1_CSLVInit(LVS1_CSLV* me);

// Execution function
void LVS1_CSLVRun(LVS1_CSLV* me);

#endif // LVS1_CSLV_H_
