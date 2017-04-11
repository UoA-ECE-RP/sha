#ifndef LEFTVENTRICLE_H_
#define LEFTVENTRICLE_H_

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

} LeftVentricle;

// Initialization function
void LeftVentricleInit(LeftVentricle* me);

// Execution function
void LeftVentricleRun(LeftVentricle* me);

#endif // LEFTVENTRICLE_H_
