#ifndef SA_CT_H_
#define SA_CT_H_

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
} SA_CT;

// Initialization function
void SA_CTInit(SA_CT* me);

// Execution function
void SA_CTRun(SA_CT* me);

#endif // SA_CT_H_
