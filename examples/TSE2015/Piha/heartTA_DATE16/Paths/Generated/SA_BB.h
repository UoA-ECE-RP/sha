#ifndef SA_BB_H_
#define SA_BB_H_

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
} SA_BB;

// Initialization function
void SA_BBInit(SA_BB* me);

// Execution function
void SA_BBRun(SA_BB* me);

#endif // SA_BB_H_
