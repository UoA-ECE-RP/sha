#ifndef SA_OS_H_
#define SA_OS_H_

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
} SA_OS;

// Initialization function
void SA_OSInit(SA_OS* me);

// Execution function
void SA_OSRun(SA_OS* me);

#endif // SA_OS_H_
