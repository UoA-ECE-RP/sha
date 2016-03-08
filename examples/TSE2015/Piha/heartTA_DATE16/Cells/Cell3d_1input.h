#ifndef CELL3D_1INPUT_H_
#define CELL3D_1INPUT_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../Generic/step.h"
#include "../States.h"

// Cell Data Struct
typedef struct {

	// Outputs
	char ACTpath;

	// Inputs
	char ACTcell;

	// Internal Variables
	int t;
  enum cellStates state;

} Cell3d_1input;

// Initialization function
void Cell3d_1inputInit(Cell3d_1input* me);

// Execution function
void Cell3d_1inputRun(Cell3d_1input* me);

#endif // CELL3D_1INPUT_H_
