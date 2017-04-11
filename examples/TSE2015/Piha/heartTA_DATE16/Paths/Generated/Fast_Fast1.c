#include "Fast_Fast1.h"

#define True 1
#define False 0


int Fast_Fast1_ode0(Fast_Fast1* me) {
   // tp_dot=0, no change in t
    return me->t;
}
int Fast_Fast1_ode1(Fast_Fast1* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void Fast_Fast1Init(Fast_Fast1* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void Fast_Fast1Run(Fast_Fast1* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // Fast_Fast1 FSM
  if(me->state == IDLE) {
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = Fast_Fast1_ode0(me);
        }
	} else if(me->state == ACT) {
        if(me->t > 20){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = Fast_Fast1_ode1(me);
        }
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
