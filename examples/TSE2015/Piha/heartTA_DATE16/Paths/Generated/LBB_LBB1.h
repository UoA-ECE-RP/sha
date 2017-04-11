#ifndef LBB_LBB1_H_
#define LBB_LBB1_H_

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
} LBB_LBB1;

// Initialization function
void LBB_LBB1Init(LBB_LBB1* me);

// Execution function
void LBB_LBB1Run(LBB_LBB1* me);

#endif // LBB_LBB1_H_
