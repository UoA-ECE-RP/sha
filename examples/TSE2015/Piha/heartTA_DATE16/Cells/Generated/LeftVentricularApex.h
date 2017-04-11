#ifndef LEFTVENTRICULARAPEX_H_
#define LEFTVENTRICULARAPEX_H_

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

} LeftVentricularApex;

// Initialization function
void LeftVentricularApexInit(LeftVentricularApex* me);

// Execution function
void LeftVentricularApexRun(LeftVentricularApex* me);

#endif // LEFTVENTRICULARAPEX_H_
