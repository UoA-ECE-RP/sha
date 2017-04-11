#ifndef CT_CT1_H_
#define CT_CT1_H_

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
} CT_CT1;

// Initialization function
void CT_CT1Init(CT_CT1* me);

// Execution function
void CT_CT1Run(CT_CT1* me);

#endif // CT_CT1_H_
