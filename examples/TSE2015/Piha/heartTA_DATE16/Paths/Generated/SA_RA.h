#ifndef SA_RA_H_
#define SA_RA_H_

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
} SA_RA;

// Initialization function
void SA_RAInit(SA_RA* me);

// Execution function
void SA_RARun(SA_RA* me);

#endif // SA_RA_H_
