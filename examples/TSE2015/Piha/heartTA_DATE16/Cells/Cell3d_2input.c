#include "Cell3d_2input.h"

#define True 1
#define False 0

#include <math.h>
static double f(double theta) {
    if(theta >= v_n_R_max)
        return 4.03947;

    return 0.29*exp(62.89*theta) + 0.70*exp(-10.99*theta);
}

static double t1_ode_1(Cell3d_2input* me) {
    double t1_ode_1_change = alpha1_x * me->v_x;
    return me->v_x + STEP_SIZE * t1_ode_1_change;
}
static double t1_ode_2(Cell3d_2input* me) {
    double t1_ode_2_change = alpha1_y * me->v_y;
    return me->v_y + STEP_SIZE * t1_ode_2_change;
}
static double t1_ode_3(Cell3d_2input* me) {
    double t1_ode_3_change = alpha1_z * me->v_z;
    return me->v_z + STEP_SIZE * t1_ode_3_change;
}


static double t2_ode_1(Cell3d_2input* me) {
    double t2_ode_1_change = alpha2_x * me->v_x + beta_x * me->g;
    return me->v_x + STEP_SIZE * t2_ode_1_change;
}
static double t2_ode_2(Cell3d_2input* me) {
    double t2_ode_2_change = alpha2_y * me->v_y + beta_y * me->g;
    return me->v_y + STEP_SIZE * t2_ode_2_change;
}
static double t2_ode_3(Cell3d_2input* me) {
    double t2_ode_3_change = alpha2_z * me->v_z + beta_z * me->g;
    return me->v_z + STEP_SIZE * t2_ode_3_change;
}


static double t3_ode_1(Cell3d_2input* me) {
    double t3_ode_1_change = alpha3_x * me->v_x;
    return me->v_x + STEP_SIZE * t3_ode_1_change;
}
static double t3_ode_2(Cell3d_2input* me) {
    double t3_ode_2_change = alpha3_y * me->v_y;
    return me->v_y + STEP_SIZE * t3_ode_2_change;
}
static double t3_ode_3(Cell3d_2input* me) {
    double t3_ode_3_change = alpha3_z * me->v_z;
    return me->v_z + STEP_SIZE * t3_ode_3_change;
}


static double t4_ode_1(Cell3d_2input* me) {
    double t4_ode_1_change = alpha4_x * me->v_x * me->f_theta;
    return me->v_x + STEP_SIZE * t4_ode_1_change;
}
static double t4_ode_2(Cell3d_2input* me) {
    double t4_ode_2_change = alpha4_y * me->v_y * me->f_theta;
    return me->v_y + STEP_SIZE * t4_ode_2_change;
}
static double t4_ode_3(Cell3d_2input* me) {
    double t4_ode_3_change = alpha4_z * me->v_z;
    return me->v_z + STEP_SIZE * t4_ode_3_change;
}

// Initialization function
void Cell3d_2inputInit(Cell3d_2input* me) {
    me->state = t1;

    me->v_x = 0;
    me->v_y = 0;
    me->v_z = 0;
    me->v = 0;
    me->theta = 0;
    me->v_O = 0;

    me->g = 0;
}


// Execution function
void Cell3d_2inputRun(Cell3d_2input* me) {
	enum cellStates state_u = me->state;
	
	double v_x_u = me->v_x;
	double v_y_u = me->v_y;
	double v_z_u = me->v_z;
	double v_u = me->v;
	double theta_u = me->theta;	
	double v_O_u = me->v_O;
	double f_theta_u = me->f_theta;

    me->g = 0;
    me->g += (gamma_0 * sigma_0 * (me->v_i_0 - me->v)) / (A_m * C_m * distance_0);
    me->g += (gamma_1 * sigma_1 * (me->v_i_1 - me->v)) / (A_m * C_m * distance_1);
	
    switch (me->state) {
        case (t1):
        if(me->v <= v_T && me->g <= v_T) {
            v_x_u = t1_ode_1(me);
            v_y_u = t1_ode_2(me);
            v_z_u = t1_ode_3(me);
            v_u = v_x_u - v_y_u + v_z_u;

            state_u = t1;
        }
        else if(me->g > v_T) {
            v_x_u = 0.3*me->v;
            v_y_u = 0;
            v_z_u = 0.7*me->v;
            v_u = v_x_u - v_y_u + v_z_u;
            theta_u = v_u / v_R;
            v_O_u = (v_O_max - 80.1*sqrt(theta_u));
			f_theta_u = f(theta_u);

            state_u = t2;
        }
        else {
            fprintf(stderr,"Unreachable state!");
            exit(1);
        }
        break;
        case (t2):
        if(me->v < v_T && me->g > 0) {
            v_x_u = t2_ode_1(me);
            v_y_u = t2_ode_2(me);
            v_z_u = t2_ode_3(me);
            v_u = v_x_u - v_y_u + v_z_u;

            if(v_u > v_T) {
                double frac = (v_T - me->v) / (v_u - me->v);
                v_x_u = me->v_x + frac * (v_x_u - me->v_x);
                v_y_u = me->v_y + frac * (v_y_u - me->v_y);
                v_z_u = v_T - v_x_u + v_y_u;
                v_u = v_T;
            }

            state_u = t2;
        }
        else if(me->g <= 0 && me->v < v_T) {
            v_x_u = me->v_x;
            v_y_u = me->v_y;
            v_z_u = me->v_z;
            v_u = v_x_u - v_y_u + v_z_u;

            state_u = t1;
        }
        else if(me->v >= v_T) {
            v_x_u = me->v_x;
            v_y_u = me->v_y;
            v_z_u = me->v_z;
            v_u = v_x_u - v_y_u + v_z_u;

            state_u = t3;
        }
        else {
            fprintf(stderr,"Unreachable state!");
            exit(1);
        }
        break;
        case (t3):
        if(me->v < me->v_O) {
            v_x_u = t3_ode_1(me);
            v_y_u = t3_ode_2(me);
            v_z_u = t3_ode_3(me);
            v_u = v_x_u - v_y_u + v_z_u;

            if(v_u > me->v_O) {
                double frac = (me->v_O - me->v) / (v_u - me->v);
                v_x_u = me->v_x + frac * (v_x_u - me->v_x);
                v_y_u = me->v_y + frac * (v_y_u - me->v_y);
                v_z_u = me->v_O - v_x_u + v_y_u;
                v_u = me->v_O;
            }

            state_u = t3;
        }
        else if(me->v >= me->v_O) {
            v_x_u = me->v_x;
            v_y_u = me->v_y;
            v_z_u = me->v_z;
            v_u = v_x_u - v_y_u + v_z_u;

            state_u = t4;
        }
        else {
            fprintf(stderr,"Unreachable state!");
            exit(1);
        }
        break;
        case (t4):
        if(me->v > v_R) {
            v_x_u = t4_ode_1(me);
            v_y_u = t4_ode_2(me);
            v_z_u = t4_ode_3(me);
            v_u = v_x_u - v_y_u + v_z_u;

            if(v_u < v_R) {
                double frac = (v_R - me->v) / (v_u - me->v);
                v_x_u = me->v_x + frac * (v_x_u - me->v_x);
                v_y_u = me->v_y + frac * (v_y_u - me->v_y);
                v_z_u = v_R - v_x_u + v_y_u;
                v_u = v_R;
            }

            state_u = t4;
        }
        else if(me->v <= v_R) {
            v_x_u = me->v_x;
            v_y_u = me->v_y;
            v_z_u = me->v_z;
            v_u = v_x_u - v_y_u + v_z_u;

            state_u = t1;
        }
        else {
            fprintf(stderr,"Unreachable state!");
            exit(1);
        }
        break;
        default: exit(1);
    }
	
	me->state = state_u;
	
	me->v_x = v_x_u;
	me->v_y = v_y_u;
	me->v_z = v_z_u;
	me->v = v_u;
	me->theta = theta_u;
	me->v_O = v_O_u;
	me->f_theta = f_theta_u;
}
