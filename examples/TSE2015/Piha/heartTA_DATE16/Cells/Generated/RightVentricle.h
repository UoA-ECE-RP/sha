#ifndef RIGHTVENTRICLE_H_
#define RIGHTVENTRICLE_H_

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

} RightVentricle;

// Initialization function
void RightVentricleInit(RightVentricle* me);

// Execution function
void RightVentricleRun(RightVentricle* me);

#endif // RIGHTVENTRICLE_H_
