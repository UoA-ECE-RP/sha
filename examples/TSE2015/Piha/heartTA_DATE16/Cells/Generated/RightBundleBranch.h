#ifndef RIGHTBUNDLEBRANCH_H_
#define RIGHTBUNDLEBRANCH_H_

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

} RightBundleBranch;

// Initialization function
void RightBundleBranchInit(RightBundleBranch* me);

// Execution function
void RightBundleBranchRun(RightBundleBranch* me);

#endif // RIGHTBUNDLEBRANCH_H_
