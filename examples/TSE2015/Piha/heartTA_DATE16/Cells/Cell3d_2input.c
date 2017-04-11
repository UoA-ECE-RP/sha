#include "Cell3d_2input.h"

#define True 1
#define False 0

int Cell3d_2input_ode1(Cell3d_2input* me) {
   // t_dot=1
    return me->t + STEP_SIZE * 1;
}


// Initialization function
void Cell3d_2inputInit(Cell3d_2input* me) {
    me->state = REST;

    me->ACTpath= 0;
    me->ACTcell1 = 0;
    me->ACTcell2 = 0;

    me->t = 0;
}


// Execution function
void Cell3d_2inputRun(Cell3d_2input* me) {
	enum cellStates state_u = me->state;

	char  ACTpath_u = 0;
	int   t_u = me->t;

	char ACTin = me->ACTcell1 || me->ACTcell2;

    // Cell FSM
    if(me->state == REST) {
          if(me->t > TREST ||  ACTin==1){
              t_u = 0;
              state_u = COND;
          }
          else {
              t_u = Cell3d_2input_ode1(me);
          }
    } else if(me->state == COND) {
          if(me->t > TCOND){
              t_u = 0;
              ACTpath_u=1;
              state_u = ERP;
          }
          else {
              t_u = Cell3d_2input_ode1(me);
          }
	} else if(me->state == ERP) {
          if(me->t > TERP){
              t_u = 0;
              state_u = RRP;
          }
          else {
              t_u = Cell3d_2input_ode1(me);
          }
    } else if(me->state == RRP) {
          if(me->t > TRRP){
              t_u = 0;
              state_u = REST;
          }
          else if(ACTin==1){
              t_u = 0;
              state_u = COND;
          }
          else {
              t_u = Cell3d_2input_ode1(me);
          }
    }

	me->state = state_u;
	me->t = t_u;
	me->ACTpath = ACTpath_u;
}
