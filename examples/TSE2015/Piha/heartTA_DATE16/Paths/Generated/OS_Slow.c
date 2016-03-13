#include "OS_Slow.h"

#define True 1
#define False 0


int OS_Slow_ode0(OS_Slow* me) {
   // tp_dot=0, no change in t
    return me->t;
}
int OS_Slow_ode1(OS_Slow* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void OS_SlowInit(OS_Slow* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void OS_SlowRun(OS_Slow* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // OS_Slow FSM
  if(me->state == IDLE) {
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = OS_Slow_ode0(me);
        }
	} else if(me->state == ACT) {
        if(me->t > 30){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = OS_Slow_ode1(me);
        }
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
