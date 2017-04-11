#include "RightVentricularSeptum.h"

#define True 1
#define False 0

int RightVentricularSeptum_ode1(RightVentricularSeptum* me) {
   // t_dot=1
    return me->t + STEP_SIZE * 1;
}


// Initialization function
void RightVentricularSeptumInit(RightVentricularSeptum* me) {
    me->state = REST;

    me->ACTpath= 0;
    me->ACTcell = 0;

    me->t = 0;
}


// Execution function
void RightVentricularSeptumRun(RightVentricularSeptum* me) {
	enum cellStates state_u = me->state;

	char  ACTpath_u = 0;
	int   t_u = me->t;



    // Cell FSM
    if(me->state == REST) {
          if(me->t > 400 ||  me->ACTcell==1){
              t_u = 0;
              state_u = COND;
          }
          else {
              t_u = RightVentricularSeptum_ode1(me);
          }
    } else if(me->state == COND) {
          if(me->t > 10){
              t_u = 0;
              ACTpath_u=1;
              state_u = ERP;
          }
          else {
              t_u = RightVentricularSeptum_ode1(me);
          }
	} else if(me->state == ERP) {
          if(me->t > 200){
              t_u = 0;
              state_u = RRP;
          }
          else {
              t_u = RightVentricularSeptum_ode1(me);
          }
    } else if(me->state == RRP) {
          if(me->t > 100){
              t_u = 0;
              state_u = REST;
          }
          else if(me->ACTcell==1){
              t_u = 0;
              state_u = COND;
          }
          else {
              t_u = RightVentricularSeptum_ode1(me);
          }
    }

	me->state = state_u;
	me->t = t_u;
	me->ACTpath = ACTpath_u;
}
