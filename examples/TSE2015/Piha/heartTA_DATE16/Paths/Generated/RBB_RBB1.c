#include "RBB_RBB1.h"

#define True 1
#define False 0


int RBB_RBB1_ode0(RBB_RBB1* me) {
   // tp_dot=0, no change in t
    return me->t;
}
int RBB_RBB1_ode1(RBB_RBB1* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void RBB_RBB1Init(RBB_RBB1* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void RBB_RBB1Run(RBB_RBB1* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // RBB_RBB1 FSM
  if(me->state == IDLE) {
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = RBB_RBB1_ode0(me);
        }
	} else if(me->state == ACT) {
        if(me->t > 5){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = RBB_RBB1_ode1(me);
        }
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
