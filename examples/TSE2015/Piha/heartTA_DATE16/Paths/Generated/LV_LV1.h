#ifndef LV_LV1_H_
#define LV_LV1_H_

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
} LV_LV1;

// Initialization function
void LV_LV1Init(LV_LV1* me);

// Execution function
void LV_LV1Run(LV_LV1* me);

#endif // LV_LV1_H_
