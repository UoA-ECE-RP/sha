#ifndef LEFTVENTRICULARSEPTUM1_H_
#define LEFTVENTRICULARSEPTUM1_H_

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

} LeftVentricularSeptum1;

// Initialization function
void LeftVentricularSeptum1Init(LeftVentricularSeptum1* me);

// Execution function
void LeftVentricularSeptum1Run(LeftVentricularSeptum1* me);

#endif // LEFTVENTRICULARSEPTUM1_H_
