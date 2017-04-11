#ifndef ATRIOVENTRICULARNODE_H_
#define ATRIOVENTRICULARNODE_H_

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

} AtrioventricularNode;

// Initialization function
void AtrioventricularNodeInit(AtrioventricularNode* me);

// Execution function
void AtrioventricularNodeRun(AtrioventricularNode* me);

#endif // ATRIOVENTRICULARNODE_H_
