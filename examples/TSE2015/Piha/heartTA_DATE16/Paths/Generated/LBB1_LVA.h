#ifndef LBB1_LVA_H_
#define LBB1_LVA_H_

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
} LBB1_LVA;

// Initialization function
void LBB1_LVAInit(LBB1_LVA* me);

// Execution function
void LBB1_LVARun(LBB1_LVA* me);

#endif // LBB1_LVA_H_
