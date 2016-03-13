#ifndef LEFTATRIUM1_H_
#define LEFTATRIUM1_H_

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

} LeftAtrium1;

// Initialization function
void LeftAtrium1Init(LeftAtrium1* me);

// Execution function
void LeftAtrium1Run(LeftAtrium1* me);

#endif // LEFTATRIUM1_H_
