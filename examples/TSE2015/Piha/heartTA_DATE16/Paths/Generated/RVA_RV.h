#ifndef RVA_RV_H_
#define RVA_RV_H_

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
} RVA_RV;

// Initialization function
void RVA_RVInit(RVA_RV* me);

// Execution function
void RVA_RVRun(RVA_RV* me);

#endif // RVA_RV_H_
