#ifndef LEFTVENTRICLE1_H_
#define LEFTVENTRICLE1_H_

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

} LeftVentricle1;

// Initialization function
void LeftVentricle1Init(LeftVentricle1* me);

// Execution function
void LeftVentricle1Run(LeftVentricle1* me);

#endif // LEFTVENTRICLE1_H_
