#ifndef CELL3D_2INPUT_H_
#define CELL3D_2INPUT_H_

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
	char ACTcell1;
	char ACTcell2;

	// Internal Variables
	int t;
  enum cellStates state;

} Cell3d_2input;

// Initialization function
void Cell3d_2inputInit(Cell3d_2input* me);

// Execution function
void Cell3d_2inputRun(Cell3d_2input* me);

#endif // CELL3D_2INPUT_H_
