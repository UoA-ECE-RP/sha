#include "SA_BB.h"

#define True 1
#define False 0


int SA_BB_ode0(SA_BB* me) {
   // tp_dot=0, no change in t
    return me->t;
}
int SA_BB_ode1(SA_BB* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void SA_BBInit(SA_BB* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void SA_BBRun(SA_BB* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // SA_BB FSM
  if(me->state == IDLE) {
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = SA_BB_ode0(me);
        }
	} else if(me->state == ACT) {
        if(me->t > 20){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = SA_BB_ode1(me);
        }
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
