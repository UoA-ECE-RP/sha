#ifndef HIS1_HIS2_H_
#define HIS1_HIS2_H_

#include <stdlib.h>
#include <stdio.h>
#include "../../Generic/step.h"
#include "../States.h"


// Cell Data Struct
typedef struct {


	// Outputs
	char ACTcell;

	// Inputs
	char ACTpath;

	// Internal Variables
	 int t;
 	enum pathStates state; // State
} His1_His2;

// Initialization function
void His1_His2Init(His1_His2* me);

// Execution function
void His1_His2Run(His1_His2* me);

#endif // HIS1_HIS2_H_
