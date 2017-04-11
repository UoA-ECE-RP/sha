#ifndef LEFTATRIUM_H_
#define LEFTATRIUM_H_

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

} LeftAtrium;

// Initialization function
void LeftAtriumInit(LeftAtrium* me);

// Execution function
void LeftAtriumRun(LeftAtrium* me);

#endif // LEFTATRIUM_H_
