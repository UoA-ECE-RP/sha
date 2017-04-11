#ifndef RIGHTVENTRICULARSEPTUM_H_
#define RIGHTVENTRICULARSEPTUM_H_

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

} RightVentricularSeptum;

// Initialization function
void RightVentricularSeptumInit(RightVentricularSeptum* me);

// Execution function
void RightVentricularSeptumRun(RightVentricularSeptum* me);

#endif // RIGHTVENTRICULARSEPTUM_H_
