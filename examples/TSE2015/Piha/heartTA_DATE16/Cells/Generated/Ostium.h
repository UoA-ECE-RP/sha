#ifndef OSTIUM_H_
#define OSTIUM_H_

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

} Ostium;

// Initialization function
void OstiumInit(Ostium* me);

// Execution function
void OstiumRun(Ostium* me);

#endif // OSTIUM_H_
