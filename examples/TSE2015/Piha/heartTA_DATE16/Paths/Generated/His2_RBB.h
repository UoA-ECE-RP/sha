#ifndef HIS2_RBB_H_
#define HIS2_RBB_H_

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
} His2_RBB;

// Initialization function
void His2_RBBInit(His2_RBB* me);

// Execution function
void His2_RBBRun(His2_RBB* me);

#endif // HIS2_RBB_H_
