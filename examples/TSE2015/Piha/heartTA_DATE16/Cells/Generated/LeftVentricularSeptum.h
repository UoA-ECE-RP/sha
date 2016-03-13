#ifndef LEFTVENTRICULARSEPTUM_H_
#define LEFTVENTRICULARSEPTUM_H_

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

} LeftVentricularSeptum;

// Initialization function
void LeftVentricularSeptumInit(LeftVentricularSeptum* me);

// Execution function
void LeftVentricularSeptumRun(LeftVentricularSeptum* me);

#endif // LEFTVENTRICULARSEPTUM_H_
