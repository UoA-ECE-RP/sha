#ifndef BUNDLEOFHIS2_H_
#define BUNDLEOFHIS2_H_

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

} BundleOfHis2;

// Initialization function
void BundleOfHis2Init(BundleOfHis2* me);

// Execution function
void BundleOfHis2Run(BundleOfHis2* me);

#endif // BUNDLEOFHIS2_H_
