#ifndef CRISTATERMINALIS1_H_
#define CRISTATERMINALIS1_H_

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

} CristaTerminalis1;

// Initialization function
void CristaTerminalis1Init(CristaTerminalis1* me);

// Execution function
void CristaTerminalis1Run(CristaTerminalis1* me);

#endif // CRISTATERMINALIS1_H_
