#ifndef OS_SLOW_H_
#define OS_SLOW_H_

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
} OS_Slow;

// Initialization function
void OS_SlowInit(OS_Slow* me);

// Execution function
void OS_SlowRun(OS_Slow* me);

#endif // OS_SLOW_H_
