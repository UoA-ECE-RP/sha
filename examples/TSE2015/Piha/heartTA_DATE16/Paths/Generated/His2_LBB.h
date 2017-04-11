#ifndef HIS2_LBB_H_
#define HIS2_LBB_H_

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
} His2_LBB;

// Initialization function
void His2_LBBInit(His2_LBB* me);

// Execution function
void His2_LBBRun(His2_LBB* me);

#endif // HIS2_LBB_H_
