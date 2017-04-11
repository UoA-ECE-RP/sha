#ifndef LA_LA1_H_
#define LA_LA1_H_

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
} LA_LA1;

// Initialization function
void LA_LA1Init(LA_LA1* me);

// Execution function
void LA_LA1Run(LA_LA1* me);

#endif // LA_LA1_H_
