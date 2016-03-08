#include "Path.h"

#define True 1
#define False 0


static int  TApath_ode0(Path* me) {
   // tp_dot=0, no change in t
    return me->t;
}
static int TApath_ode1(Path* me) {
   // tp_dot=1
    return me->t + STEP_SIZE * 1;
}

// Initialization function
void PathInit(Path* me) {
    me->state = IDLE;

    me->ACTcell = 0;
    me->ACTpath = 0;

    me->t = 0;

}


// Execution function
void PathRun(Path* me) {
	enum pathStates state_u = me->state;
	char ACTcell_u = 0;
	char t_u = me->t;


  // Path FSM
  switch (me->state) {
      case (IDLE):
        if(me->ACTpath==1){
              t_u = 0;
              state_u = ACT;
        }
        else{
            t_u = TApath_ode0(me);
        }
      break;
      case (ACT):
        if(me->t > DELAY){
              t_u = 0;
              state_u = IDLE;
              ACTcell_u=1;
        }
        else{
            t_u = TApath_ode1(me);
        }
      break;
      default: exit(1);
    }



    me->state = state_u;
    me->t = t_u;
    me->ACTcell=ACTcell_u;

}
