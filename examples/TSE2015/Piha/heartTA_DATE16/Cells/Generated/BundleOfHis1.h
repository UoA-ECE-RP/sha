#ifndef BUNDLEOFHIS1_H_
#define BUNDLEOFHIS1_H_

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

} BundleOfHis1;

// Initialization function
void BundleOfHis1Init(BundleOfHis1* me);

// Execution function
void BundleOfHis1Run(BundleOfHis1* me);

#endif // BUNDLEOFHIS1_H_
