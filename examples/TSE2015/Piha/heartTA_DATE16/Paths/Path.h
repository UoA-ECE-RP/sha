#ifndef PATH_H_
#define PATH_H_

#include <stdint.h>
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
} Path;

// Initialization function
void PathInit(Path* me);

// Execution function
void PathRun(Path* me);

#endif // PATH_H_
