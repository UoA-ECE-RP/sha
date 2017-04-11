#ifndef RBB_RBB1_H_
#define RBB_RBB1_H_

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
} RBB_RBB1;

// Initialization function
void RBB_RBB1Init(RBB_RBB1* me);

// Execution function
void RBB_RBB1Run(RBB_RBB1* me);

#endif // RBB_RBB1_H_
