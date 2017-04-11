#ifndef RIGHTVENTRICULARAPEX_H_
#define RIGHTVENTRICULARAPEX_H_

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

} RightVentricularApex;

// Initialization function
void RightVentricularApexInit(RightVentricularApex* me);

// Execution function
void RightVentricularApexRun(RightVentricularApex* me);

#endif // RIGHTVENTRICULARAPEX_H_
