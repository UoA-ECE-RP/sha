#include "Fast1_AV.h"

#define True 1
#define False 0


int Fast1_AV_ode0(Fast1_AV* me) {
   // tp_dot=0, no change in t
    return me->t;
}
int Fast1_AV_ode1(Fast1_AV* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void Fast1_AVInit(Fast1_AV* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void Fast1_AVRun(Fast1_AV* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // Fast1_AV FSM
  if(me->state == IDLE) {
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = Fast1_AV_ode0(me);
        }
	} else if(me->state == ACT) {
        if(me->t > 10){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = Fast1_AV_ode1(me);
        }
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
