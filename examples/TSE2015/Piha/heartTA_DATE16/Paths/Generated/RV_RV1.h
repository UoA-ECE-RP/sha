#ifndef RV_RV1_H_
#define RV_RV1_H_

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
} RV_RV1;

// Initialization function
void RV_RV1Init(RV_RV1* me);

// Execution function
void RV_RV1Run(RV_RV1* me);

#endif // RV_RV1_H_
