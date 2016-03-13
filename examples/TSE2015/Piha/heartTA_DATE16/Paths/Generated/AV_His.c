#include "AV_His.h"

#define True 1
#define False 0


int AV_His_ode0(AV_His* me) {
   // tp_dot=0, no change in t
    return me->t;
}
int AV_His_ode1(AV_His* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void AV_HisInit(AV_His* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void AV_HisRun(AV_His* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // AV_His FSM
  if(me->state == IDLE) {
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = AV_His_ode0(me);
        }
	} else if(me->state == ACT) {
        if(me->t > 30){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = AV_His_ode1(me);
        }
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
