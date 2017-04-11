#ifndef SLOW_H_
#define SLOW_H_

#include <stdlib.h>
#include <stdio.h>
#include "../../Generic/step.h"
#include "../States.h"

// Cell Data Struct
typedef struct {

	// Outputs
	char ACTpath;

	// Inputs
	char ACTcell;

	// Internal Variables
	int t;
  enum cellStates state;

} Slow;

// Initialization function
void SlowInit(Slow* me);

// Execution function
void SlowRun(Slow* me);

#endif // SLOW_H_
