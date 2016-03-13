#ifndef LVA_RVA_H_
#define LVA_RVA_H_

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
} LVA_RVA;

// Initialization function
void LVA_RVAInit(LVA_RVA* me);

// Execution function
void LVA_RVARun(LVA_RVA* me);

#endif // LVA_RVA_H_
