#ifndef RIGHTVENTRICLE1_H_
#define RIGHTVENTRICLE1_H_

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

} RightVentricle1;

// Initialization function
void RightVentricle1Init(RightVentricle1* me);

// Execution function
void RightVentricle1Run(RightVentricle1* me);

#endif // RIGHTVENTRICLE1_H_
