#ifndef LEFTBUNDLEBRANCH_H_
#define LEFTBUNDLEBRANCH_H_

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

} LeftBundleBranch;

// Initialization function
void LeftBundleBranchInit(LeftBundleBranch* me);

// Execution function
void LeftBundleBranchRun(LeftBundleBranch* me);

#endif // LEFTBUNDLEBRANCH_H_
