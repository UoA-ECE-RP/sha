#ifndef RBB1_RVA_H_
#define RBB1_RVA_H_

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
} RBB1_RVA;

// Initialization function
void RBB1_RVAInit(RBB1_RVA* me);

// Execution function
void RBB1_RVARun(RBB1_RVA* me);

#endif // RBB1_RVA_H_
