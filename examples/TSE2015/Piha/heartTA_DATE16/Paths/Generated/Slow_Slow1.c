#include "Slow_Slow1.h"

#define True 1
#define False 0


int Slow_Slow1_ode0(Slow_Slow1* me) {
   // tp_dot=0, no change in t
    return me->t;
}
int Slow_Slow1_ode1(Slow_Slow1* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void Slow_Slow1Init(Slow_Slow1* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void Slow_Slow1Run(Slow_Slow1* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // Slow_Slow1 FSM
  if(me->state == IDLE) {
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = Slow_Slow1_ode0(me);
        }
	} else if(me->state == ACT) {
        if(me->t > 30){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = Slow_Slow1_ode1(me);
        }
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
