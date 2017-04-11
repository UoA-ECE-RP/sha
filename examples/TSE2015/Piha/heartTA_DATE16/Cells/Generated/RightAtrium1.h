#ifndef RIGHTATRIUM1_H_
#define RIGHTATRIUM1_H_

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

} RightAtrium1;

// Initialization function
void RightAtrium1Init(RightAtrium1* me);

// Execution function
void RightAtrium1Run(RightAtrium1* me);

#endif // RIGHTATRIUM1_H_
