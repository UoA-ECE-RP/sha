#ifndef FAST_H_
#define FAST_H_

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

} Fast;

// Initialization function
void FastInit(Fast* me);

// Execution function
void FastRun(Fast* me);

#endif // FAST_H_
