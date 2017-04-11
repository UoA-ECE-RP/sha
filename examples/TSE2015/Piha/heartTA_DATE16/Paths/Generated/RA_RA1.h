#ifndef RA_RA1_H_
#define RA_RA1_H_

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
} RA_RA1;

// Initialization function
void RA_RA1Init(RA_RA1* me);

// Execution function
void RA_RA1Run(RA_RA1* me);

#endif // RA_RA1_H_
