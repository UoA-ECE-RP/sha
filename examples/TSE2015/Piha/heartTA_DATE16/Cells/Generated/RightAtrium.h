#ifndef RIGHTATRIUM_H_
#define RIGHTATRIUM_H_

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

} RightAtrium;

// Initialization function
void RightAtriumInit(RightAtrium* me);

// Execution function
void RightAtriumRun(RightAtrium* me);

#endif // RIGHTATRIUM_H_
