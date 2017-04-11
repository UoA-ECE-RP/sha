#ifndef RA1_CS_H_
#define RA1_CS_H_

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
} RA1_CS;

// Initialization function
void RA1_CSInit(RA1_CS* me);

// Execution function
void RA1_CSRun(RA1_CS* me);

#endif // RA1_CS_H_
