#include "RVA_RV.h"

#define True 1
#define False 0


int RVA_RV_ode0(RVA_RV* me) {
   // tp_dot=0, no change in t
    return me->t;
}
int RVA_RV_ode1(RVA_RV* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void RVA_RVInit(RVA_RV* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void RVA_RVRun(RVA_RV* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // RVA_RV FSM
  if(me->state == IDLE) {
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = RVA_RV_ode0(me);
        }
	} else if(me->state == ACT) {
        if(me->t > 10){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = RVA_RV_ode1(me);
        }
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
