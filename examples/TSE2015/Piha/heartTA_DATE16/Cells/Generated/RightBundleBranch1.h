#ifndef RIGHTBUNDLEBRANCH1_H_
#define RIGHTBUNDLEBRANCH1_H_

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

} RightBundleBranch1;

// Initialization function
void RightBundleBranch1Init(RightBundleBranch1* me);

// Execution function
void RightBundleBranch1Run(RightBundleBranch1* me);

#endif // RIGHTBUNDLEBRANCH1_H_
