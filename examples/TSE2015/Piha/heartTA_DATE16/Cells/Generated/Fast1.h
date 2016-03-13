#ifndef FAST1_H_
#define FAST1_H_

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

} Fast1;

// Initialization function
void Fast1Init(Fast1* me);

// Execution function
void Fast1Run(Fast1* me);

#endif // FAST1_H_
