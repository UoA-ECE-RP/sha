#include "RVA_RVS.h"

#define True 1
#define False 0


int RVA_RVS_ode0(RVA_RVS* me) {
   // tp_dot=0, no change in t
    return me->t;
}
int RVA_RVS_ode1(RVA_RVS* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void RVA_RVSInit(RVA_RVS* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void RVA_RVSRun(RVA_RVS* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // RVA_RVS FSM
  if(me->state == IDLE) {
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = RVA_RVS_ode0(me);
        }
	} else if(me->state == ACT) {
        if(me->t > 15){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = RVA_RVS_ode1(me);
        }
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
