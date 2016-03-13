#ifndef RIGHTVENTRICULARSEPTUM1_H_
#define RIGHTVENTRICULARSEPTUM1_H_

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

} RightVentricularSeptum1;

// Initialization function
void RightVentricularSeptum1Init(RightVentricularSeptum1* me);

// Execution function
void RightVentricularSeptum1Run(RightVentricularSeptum1* me);

#endif // RIGHTVENTRICULARSEPTUM1_H_
