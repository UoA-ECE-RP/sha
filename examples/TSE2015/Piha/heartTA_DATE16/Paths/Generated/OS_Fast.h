#ifndef OS_FAST_H_
#define OS_FAST_H_

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
} OS_Fast;

// Initialization function
void OS_FastInit(OS_Fast* me);

// Execution function
void OS_FastRun(OS_Fast* me);

#endif // OS_FAST_H_
