#ifndef CRISTATERMINALIS_H_
#define CRISTATERMINALIS_H_

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

} CristaTerminalis;

// Initialization function
void CristaTerminalisInit(CristaTerminalis* me);

// Execution function
void CristaTerminalisRun(CristaTerminalis* me);

#endif // CRISTATERMINALIS_H_
