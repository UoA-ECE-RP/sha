#ifndef LEFTBUNDLEBRANCH1_H_
#define LEFTBUNDLEBRANCH1_H_

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

} LeftBundleBranch1;

// Initialization function
void LeftBundleBranch1Init(LeftBundleBranch1* me);

// Execution function
void LeftBundleBranch1Run(LeftBundleBranch1* me);

#endif // LEFTBUNDLEBRANCH1_H_
