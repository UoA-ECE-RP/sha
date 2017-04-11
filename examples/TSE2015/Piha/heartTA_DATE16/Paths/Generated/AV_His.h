#ifndef AV_HIS_H_
#define AV_HIS_H_

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
} AV_His;

// Initialization function
void AV_HisInit(AV_His* me);

// Execution function
void AV_HisRun(AV_His* me);

#endif // AV_HIS_H_
