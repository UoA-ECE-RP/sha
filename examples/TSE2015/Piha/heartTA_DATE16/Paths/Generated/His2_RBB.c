#include "His2_RBB.h"

#define True 1
#define False 0


int His2_RBB_ode0(His2_RBB* me) {
   // tp_dot=0, no change in t
    return me->t;
}
int His2_RBB_ode1(His2_RBB* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void His2_RBBInit(His2_RBB* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void His2_RBBRun(His2_RBB* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // His2_RBB FSM
  if(me->state == IDLE) {
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = His2_RBB_ode0(me);
        }
	} else if(me->state == ACT) {
        if(me->t > 20){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = His2_RBB_ode1(me);
        }
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
