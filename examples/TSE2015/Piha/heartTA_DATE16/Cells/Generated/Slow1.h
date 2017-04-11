#ifndef SLOW1_H_
#define SLOW1_H_

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

} Slow1;

// Initialization function
void Slow1Init(Slow1* me);

// Execution function
void Slow1Run(Slow1* me);

#endif // SLOW1_H_
