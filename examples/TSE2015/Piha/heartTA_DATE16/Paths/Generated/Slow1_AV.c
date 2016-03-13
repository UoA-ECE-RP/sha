#include "Slow1_AV.h"

#define True 1
#define False 0


int Slow1_AV_ode0(Slow1_AV* me) {
   // tp_dot=0, no change in t
    return me->t;
}
int Slow1_AV_ode1(Slow1_AV* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void Slow1_AVInit(Slow1_AV* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void Slow1_AVRun(Slow1_AV* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // Slow1_AV FSM
  if(me->state == IDLE) {
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = Slow1_AV_ode0(me);
        }
	} else if(me->state == ACT) {
        if(me->t > 15){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = Slow1_AV_ode1(me);
        }
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
