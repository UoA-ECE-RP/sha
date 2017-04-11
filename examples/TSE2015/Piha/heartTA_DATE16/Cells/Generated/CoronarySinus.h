#ifndef CORONARYSINUS_H_
#define CORONARYSINUS_H_

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

} CoronarySinus;

// Initialization function
void CoronarySinusInit(CoronarySinus* me);

// Execution function
void CoronarySinusRun(CoronarySinus* me);

#endif // CORONARYSINUS_H_
