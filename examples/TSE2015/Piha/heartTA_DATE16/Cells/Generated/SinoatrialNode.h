#ifndef SINOATRIALNODE_H_
#define SINOATRIALNODE_H_

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

} SinoatrialNode;

// Initialization function
void SinoatrialNodeInit(SinoatrialNode* me);

// Execution function
void SinoatrialNodeRun(SinoatrialNode* me);

#endif // SINOATRIALNODE_H_
