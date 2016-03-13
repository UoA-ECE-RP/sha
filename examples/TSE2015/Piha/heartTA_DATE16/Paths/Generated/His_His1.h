#ifndef HIS_HIS1_H_
#define HIS_HIS1_H_

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
} His_His1;

// Initialization function
void His_His1Init(His_His1* me);

// Execution function
void His_His1Run(His_His1* me);

#endif // HIS_HIS1_H_
