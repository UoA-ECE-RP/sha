#ifndef CSLEFTVENTRICULAR_H_
#define CSLEFTVENTRICULAR_H_

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

} CSLeftVentricular;

// Initialization function
void CSLeftVentricularInit(CSLeftVentricular* me);

// Execution function
void CSLeftVentricularRun(CSLeftVentricular* me);

#endif // CSLEFTVENTRICULAR_H_
