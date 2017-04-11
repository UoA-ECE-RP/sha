#ifndef BB_LA_H_
#define BB_LA_H_

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
} BB_LA;

// Initialization function
void BB_LAInit(BB_LA* me);

// Execution function
void BB_LARun(BB_LA* me);

#endif // BB_LA_H_
