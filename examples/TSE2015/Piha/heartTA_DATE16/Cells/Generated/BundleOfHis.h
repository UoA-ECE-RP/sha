#ifndef BUNDLEOFHIS_H_
#define BUNDLEOFHIS_H_

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

} BundleOfHis;

// Initialization function
void BundleOfHisInit(BundleOfHis* me);

// Execution function
void BundleOfHisRun(BundleOfHis* me);

#endif // BUNDLEOFHIS_H_
