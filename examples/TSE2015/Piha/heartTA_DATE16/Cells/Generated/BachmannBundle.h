#ifndef BACHMANNBUNDLE_H_
#define BACHMANNBUNDLE_H_

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

} BachmannBundle;

// Initialization function
void BachmannBundleInit(BachmannBundle* me);

// Execution function
void BachmannBundleRun(BachmannBundle* me);

#endif // BACHMANNBUNDLE_H_
