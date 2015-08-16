#include<stdint.h>

#include<stdlib.h>

#include<stdio.h>

#define True 1

#define False 0

// Global variables from outside this HA

// Global variables in this HA

double signal_u;

//Events

extern unsigned char OFF, TURN_ON, ON, TURN_OFF;

extern void readInput();

extern void writeOutput();

//Continous variables

double y, x;

//Continous variable update

double y_u, x_u;

//Continous variable init

double y_init, x_init;

//The constant variable

double C1y, C1x;

//Step-size constant d

extern double d;

//Nstep constant k

double k;

//States

enum states {_watertank_t1_burner_b1 , _watertank_t1_burner_b2 , _watertank_t1_burner_b3 , _watertank_t1_burner_b4 , _watertank_t2_burner_b1 , _watertank_t2_burner_b2 , _watertank_t2_burner_b3 , _watertank_t2_burner_b4 , _watertank_t3_burner_b1 , _watertank_t3_burner_b2 , _watertank_t3_burner_b3 , _watertank_t3_burner_b4 , _watertank_t4_burner_b1 , _watertank_t4_burner_b2 , _watertank_t4_burner_b3 , _watertank_t4_burner_b4};

//Previous state variable

#include "_watertank_t1_burner_b1.h"
#include <math.h>
double _watertank_t1_burner_b1_ode_1(double C1x, double d, double k) {
   double _watertank_t1_burner_b1_ode_1_result;
   _watertank_t1_burner_b1_ode_1_result = C1x*exp(-0.075*d*k) + 150.0;
   return _watertank_t1_burner_b1_ode_1_result;
}
double _watertank_t1_burner_b1_ode_2(double C1y) {
   double _watertank_t1_burner_b1_ode_2_result;
   _watertank_t1_burner_b1_ode_2_result = C1y;
   return _watertank_t1_burner_b1_ode_2_result;
}
double _watertank_t1_burner_b1_init_1(double x_u) {
   double _watertank_t1_burner_b1_init_1_result;
   _watertank_t1_burner_b1_init_1_result = x_u - 150.0;
   return _watertank_t1_burner_b1_init_1_result;
}
double _watertank_t1_burner_b1_init_2(double y_u) {
   double _watertank_t1_burner_b1_init_2_result;
   _watertank_t1_burner_b1_init_2_result = y_u;
   return _watertank_t1_burner_b1_init_2_result;
}


#include "_watertank_t1_burner_b2.h"
#include <math.h>
double _watertank_t1_burner_b2_ode_1(double C1x, double d, double k) {
   double _watertank_t1_burner_b2_ode_1_result;
   _watertank_t1_burner_b2_ode_1_result = C1x*exp(-0.075*d*k) + 150.0;
   return _watertank_t1_burner_b2_ode_1_result;
}
double _watertank_t1_burner_b2_ode_2(double C1y, double d, double k) {
   double _watertank_t1_burner_b2_ode_2_result;
   _watertank_t1_burner_b2_ode_2_result = C1y + d*k;
   return _watertank_t1_burner_b2_ode_2_result;
}
double _watertank_t1_burner_b2_init_1(double x_u) {
   double _watertank_t1_burner_b2_init_1_result;
   _watertank_t1_burner_b2_init_1_result = x_u - 150.0;
   return _watertank_t1_burner_b2_init_1_result;
}
double _watertank_t1_burner_b2_init_2(double y_u) {
   double _watertank_t1_burner_b2_init_2_result;
   _watertank_t1_burner_b2_init_2_result = y_u;
   return _watertank_t1_burner_b2_init_2_result;
}


#include "_watertank_t1_burner_b3.h"
#include <math.h>
double _watertank_t1_burner_b3_ode_1(double C1x, double d, double k) {
   double _watertank_t1_burner_b3_ode_1_result;
   _watertank_t1_burner_b3_ode_1_result = C1x*exp(-0.075*d*k) + 150.0;
   return _watertank_t1_burner_b3_ode_1_result;
}
double _watertank_t1_burner_b3_ode_2(double C1y) {
   double _watertank_t1_burner_b3_ode_2_result;
   _watertank_t1_burner_b3_ode_2_result = C1y;
   return _watertank_t1_burner_b3_ode_2_result;
}
double _watertank_t1_burner_b3_init_1(double x_u) {
   double _watertank_t1_burner_b3_init_1_result;
   _watertank_t1_burner_b3_init_1_result = x_u - 150.0;
   return _watertank_t1_burner_b3_init_1_result;
}
double _watertank_t1_burner_b3_init_2(double y_u) {
   double _watertank_t1_burner_b3_init_2_result;
   _watertank_t1_burner_b3_init_2_result = y_u;
   return _watertank_t1_burner_b3_init_2_result;
}


#include "_watertank_t1_burner_b4.h"
#include <math.h>
double _watertank_t1_burner_b4_ode_1(double C1x, double d, double k) {
   double _watertank_t1_burner_b4_ode_1_result;
   _watertank_t1_burner_b4_ode_1_result = C1x*exp(-0.075*d*k) + 150.0;
   return _watertank_t1_burner_b4_ode_1_result;
}
double _watertank_t1_burner_b4_ode_2(double C1y, double d, double k) {
   double _watertank_t1_burner_b4_ode_2_result;
   _watertank_t1_burner_b4_ode_2_result = C1y + d*k;
   return _watertank_t1_burner_b4_ode_2_result;
}
double _watertank_t1_burner_b4_init_1(double x_u) {
   double _watertank_t1_burner_b4_init_1_result;
   _watertank_t1_burner_b4_init_1_result = x_u - 150.0;
   return _watertank_t1_burner_b4_init_1_result;
}
double _watertank_t1_burner_b4_init_2(double y_u) {
   double _watertank_t1_burner_b4_init_2_result;
   _watertank_t1_burner_b4_init_2_result = y_u;
   return _watertank_t1_burner_b4_init_2_result;
}


#include "_watertank_t2_burner_b1.h"
#include <math.h>
double _watertank_t2_burner_b1_ode_1(double C1x) {
   double _watertank_t2_burner_b1_ode_1_result;
   _watertank_t2_burner_b1_ode_1_result = C1x;
   return _watertank_t2_burner_b1_ode_1_result;
}
double _watertank_t2_burner_b1_ode_2(double C1y) {
   double _watertank_t2_burner_b1_ode_2_result;
   _watertank_t2_burner_b1_ode_2_result = C1y;
   return _watertank_t2_burner_b1_ode_2_result;
}
double _watertank_t2_burner_b1_init_1(double x_u) {
   double _watertank_t2_burner_b1_init_1_result;
   _watertank_t2_burner_b1_init_1_result = x_u;
   return _watertank_t2_burner_b1_init_1_result;
}
double _watertank_t2_burner_b1_init_2(double y_u) {
   double _watertank_t2_burner_b1_init_2_result;
   _watertank_t2_burner_b1_init_2_result = y_u;
   return _watertank_t2_burner_b1_init_2_result;
}


#include "_watertank_t2_burner_b2.h"
#include <math.h>
double _watertank_t2_burner_b2_ode_1(double C1x) {
   double _watertank_t2_burner_b2_ode_1_result;
   _watertank_t2_burner_b2_ode_1_result = C1x;
   return _watertank_t2_burner_b2_ode_1_result;
}
double _watertank_t2_burner_b2_ode_2(double C1y, double d, double k) {
   double _watertank_t2_burner_b2_ode_2_result;
   _watertank_t2_burner_b2_ode_2_result = C1y + d*k;
   return _watertank_t2_burner_b2_ode_2_result;
}
double _watertank_t2_burner_b2_init_1(double x_u) {
   double _watertank_t2_burner_b2_init_1_result;
   _watertank_t2_burner_b2_init_1_result = x_u;
   return _watertank_t2_burner_b2_init_1_result;
}
double _watertank_t2_burner_b2_init_2(double y_u) {
   double _watertank_t2_burner_b2_init_2_result;
   _watertank_t2_burner_b2_init_2_result = y_u;
   return _watertank_t2_burner_b2_init_2_result;
}


#include "_watertank_t2_burner_b3.h"
#include <math.h>
double _watertank_t2_burner_b3_ode_1(double C1x) {
   double _watertank_t2_burner_b3_ode_1_result;
   _watertank_t2_burner_b3_ode_1_result = C1x;
   return _watertank_t2_burner_b3_ode_1_result;
}
double _watertank_t2_burner_b3_ode_2(double C1y) {
   double _watertank_t2_burner_b3_ode_2_result;
   _watertank_t2_burner_b3_ode_2_result = C1y;
   return _watertank_t2_burner_b3_ode_2_result;
}
double _watertank_t2_burner_b3_init_1(double x_u) {
   double _watertank_t2_burner_b3_init_1_result;
   _watertank_t2_burner_b3_init_1_result = x_u;
   return _watertank_t2_burner_b3_init_1_result;
}
double _watertank_t2_burner_b3_init_2(double y_u) {
   double _watertank_t2_burner_b3_init_2_result;
   _watertank_t2_burner_b3_init_2_result = y_u;
   return _watertank_t2_burner_b3_init_2_result;
}


#include "_watertank_t2_burner_b4.h"
#include <math.h>
double _watertank_t2_burner_b4_ode_1(double C1x) {
   double _watertank_t2_burner_b4_ode_1_result;
   _watertank_t2_burner_b4_ode_1_result = C1x;
   return _watertank_t2_burner_b4_ode_1_result;
}
double _watertank_t2_burner_b4_ode_2(double C1y, double d, double k) {
   double _watertank_t2_burner_b4_ode_2_result;
   _watertank_t2_burner_b4_ode_2_result = C1y + d*k;
   return _watertank_t2_burner_b4_ode_2_result;
}
double _watertank_t2_burner_b4_init_1(double x_u) {
   double _watertank_t2_burner_b4_init_1_result;
   _watertank_t2_burner_b4_init_1_result = x_u;
   return _watertank_t2_burner_b4_init_1_result;
}
double _watertank_t2_burner_b4_init_2(double y_u) {
   double _watertank_t2_burner_b4_init_2_result;
   _watertank_t2_burner_b4_init_2_result = y_u;
   return _watertank_t2_burner_b4_init_2_result;
}


#include "_watertank_t3_burner_b1.h"
#include <math.h>
double _watertank_t3_burner_b1_ode_1(double C1x, double d, double k) {
   double _watertank_t3_burner_b1_ode_1_result;
   _watertank_t3_burner_b1_ode_1_result = C1x*exp(-0.075*d*k);
   return _watertank_t3_burner_b1_ode_1_result;
}
double _watertank_t3_burner_b1_ode_2(double C1y) {
   double _watertank_t3_burner_b1_ode_2_result;
   _watertank_t3_burner_b1_ode_2_result = C1y;
   return _watertank_t3_burner_b1_ode_2_result;
}
double _watertank_t3_burner_b1_init_1(double x_u) {
   double _watertank_t3_burner_b1_init_1_result;
   _watertank_t3_burner_b1_init_1_result = x_u;
   return _watertank_t3_burner_b1_init_1_result;
}
double _watertank_t3_burner_b1_init_2(double y_u) {
   double _watertank_t3_burner_b1_init_2_result;
   _watertank_t3_burner_b1_init_2_result = y_u;
   return _watertank_t3_burner_b1_init_2_result;
}


#include "_watertank_t3_burner_b2.h"
#include <math.h>
double _watertank_t3_burner_b2_ode_1(double C1x, double d, double k) {
   double _watertank_t3_burner_b2_ode_1_result;
   _watertank_t3_burner_b2_ode_1_result = C1x*exp(-0.075*d*k);
   return _watertank_t3_burner_b2_ode_1_result;
}
double _watertank_t3_burner_b2_ode_2(double C1y, double d, double k) {
   double _watertank_t3_burner_b2_ode_2_result;
   _watertank_t3_burner_b2_ode_2_result = C1y + d*k;
   return _watertank_t3_burner_b2_ode_2_result;
}
double _watertank_t3_burner_b2_init_1(double x_u) {
   double _watertank_t3_burner_b2_init_1_result;
   _watertank_t3_burner_b2_init_1_result = x_u;
   return _watertank_t3_burner_b2_init_1_result;
}
double _watertank_t3_burner_b2_init_2(double y_u) {
   double _watertank_t3_burner_b2_init_2_result;
   _watertank_t3_burner_b2_init_2_result = y_u;
   return _watertank_t3_burner_b2_init_2_result;
}


#include "_watertank_t3_burner_b3.h"
#include <math.h>
double _watertank_t3_burner_b3_ode_1(double C1x, double d, double k) {
   double _watertank_t3_burner_b3_ode_1_result;
   _watertank_t3_burner_b3_ode_1_result = C1x*exp(-0.075*d*k);
   return _watertank_t3_burner_b3_ode_1_result;
}
double _watertank_t3_burner_b3_ode_2(double C1y) {
   double _watertank_t3_burner_b3_ode_2_result;
   _watertank_t3_burner_b3_ode_2_result = C1y;
   return _watertank_t3_burner_b3_ode_2_result;
}
double _watertank_t3_burner_b3_init_1(double x_u) {
   double _watertank_t3_burner_b3_init_1_result;
   _watertank_t3_burner_b3_init_1_result = x_u;
   return _watertank_t3_burner_b3_init_1_result;
}
double _watertank_t3_burner_b3_init_2(double y_u) {
   double _watertank_t3_burner_b3_init_2_result;
   _watertank_t3_burner_b3_init_2_result = y_u;
   return _watertank_t3_burner_b3_init_2_result;
}


#include "_watertank_t3_burner_b4.h"
#include <math.h>
double _watertank_t3_burner_b4_ode_1(double C1x, double d, double k) {
   double _watertank_t3_burner_b4_ode_1_result;
   _watertank_t3_burner_b4_ode_1_result = C1x*exp(-0.075*d*k);
   return _watertank_t3_burner_b4_ode_1_result;
}
double _watertank_t3_burner_b4_ode_2(double C1y, double d, double k) {
   double _watertank_t3_burner_b4_ode_2_result;
   _watertank_t3_burner_b4_ode_2_result = C1y + d*k;
   return _watertank_t3_burner_b4_ode_2_result;
}
double _watertank_t3_burner_b4_init_1(double x_u) {
   double _watertank_t3_burner_b4_init_1_result;
   _watertank_t3_burner_b4_init_1_result = x_u;
   return _watertank_t3_burner_b4_init_1_result;
}
double _watertank_t3_burner_b4_init_2(double y_u) {
   double _watertank_t3_burner_b4_init_2_result;
   _watertank_t3_burner_b4_init_2_result = y_u;
   return _watertank_t3_burner_b4_init_2_result;
}


#include "_watertank_t4_burner_b1.h"
#include <math.h>
double _watertank_t4_burner_b1_ode_1(double C1x) {
   double _watertank_t4_burner_b1_ode_1_result;
   _watertank_t4_burner_b1_ode_1_result = C1x;
   return _watertank_t4_burner_b1_ode_1_result;
}
double _watertank_t4_burner_b1_ode_2(double C1y) {
   double _watertank_t4_burner_b1_ode_2_result;
   _watertank_t4_burner_b1_ode_2_result = C1y;
   return _watertank_t4_burner_b1_ode_2_result;
}
double _watertank_t4_burner_b1_init_1(double x_u) {
   double _watertank_t4_burner_b1_init_1_result;
   _watertank_t4_burner_b1_init_1_result = x_u;
   return _watertank_t4_burner_b1_init_1_result;
}
double _watertank_t4_burner_b1_init_2(double y_u) {
   double _watertank_t4_burner_b1_init_2_result;
   _watertank_t4_burner_b1_init_2_result = y_u;
   return _watertank_t4_burner_b1_init_2_result;
}


#include "_watertank_t4_burner_b2.h"
#include <math.h>
double _watertank_t4_burner_b2_ode_1(double C1x) {
   double _watertank_t4_burner_b2_ode_1_result;
   _watertank_t4_burner_b2_ode_1_result = C1x;
   return _watertank_t4_burner_b2_ode_1_result;
}
double _watertank_t4_burner_b2_ode_2(double C1y, double d, double k) {
   double _watertank_t4_burner_b2_ode_2_result;
   _watertank_t4_burner_b2_ode_2_result = C1y + d*k;
   return _watertank_t4_burner_b2_ode_2_result;
}
double _watertank_t4_burner_b2_init_1(double x_u) {
   double _watertank_t4_burner_b2_init_1_result;
   _watertank_t4_burner_b2_init_1_result = x_u;
   return _watertank_t4_burner_b2_init_1_result;
}
double _watertank_t4_burner_b2_init_2(double y_u) {
   double _watertank_t4_burner_b2_init_2_result;
   _watertank_t4_burner_b2_init_2_result = y_u;
   return _watertank_t4_burner_b2_init_2_result;
}


#include "_watertank_t4_burner_b3.h"
#include <math.h>
double _watertank_t4_burner_b3_ode_1(double C1x) {
   double _watertank_t4_burner_b3_ode_1_result;
   _watertank_t4_burner_b3_ode_1_result = C1x;
   return _watertank_t4_burner_b3_ode_1_result;
}
double _watertank_t4_burner_b3_ode_2(double C1y) {
   double _watertank_t4_burner_b3_ode_2_result;
   _watertank_t4_burner_b3_ode_2_result = C1y;
   return _watertank_t4_burner_b3_ode_2_result;
}
double _watertank_t4_burner_b3_init_1(double x_u) {
   double _watertank_t4_burner_b3_init_1_result;
   _watertank_t4_burner_b3_init_1_result = x_u;
   return _watertank_t4_burner_b3_init_1_result;
}
double _watertank_t4_burner_b3_init_2(double y_u) {
   double _watertank_t4_burner_b3_init_2_result;
   _watertank_t4_burner_b3_init_2_result = y_u;
   return _watertank_t4_burner_b3_init_2_result;
}


#include "_watertank_t4_burner_b4.h"
#include <math.h>
double _watertank_t4_burner_b4_ode_1(double C1x) {
   double _watertank_t4_burner_b4_ode_1_result;
   _watertank_t4_burner_b4_ode_1_result = C1x;
   return _watertank_t4_burner_b4_ode_1_result;
}
double _watertank_t4_burner_b4_ode_2(double C1y, double d, double k) {
   double _watertank_t4_burner_b4_ode_2_result;
   _watertank_t4_burner_b4_ode_2_result = C1y + d*k;
   return _watertank_t4_burner_b4_ode_2_result;
}
double _watertank_t4_burner_b4_init_1(double x_u) {
   double _watertank_t4_burner_b4_init_1_result;
   _watertank_t4_burner_b4_init_1_result = x_u;
   return _watertank_t4_burner_b4_init_1_result;
}
double _watertank_t4_burner_b4_init_2(double y_u) {
   double _watertank_t4_burner_b4_init_2_result;
   _watertank_t4_burner_b4_init_2_result = y_u;
   return _watertank_t4_burner_b4_init_2_result;
}


enum states watertank_burner(enum states cstate, enum states pstate) {
  static double fk;
  static unsigned char force_init_update;
  switch (cstate) {
  case (_watertank_t1_burner_b1):
    if(y >= 0 && y <= 0 && x >= 20 && x < 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t1_burner_b1_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t1_burner_b1_ode_1(C1x, d, k);
      if(x_u > 100 && x_init <= 100)
        x_u = 100;
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t1_burner_b1_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t1_burner_b1_ode_2(C1y);
      ++k;
      cstate = _watertank_t1_burner_b1;
      force_init_update = False;
    }
    else if(TURN_ON && !OFF && !ON && !TURN_OFF && True && x >= 100 && x <= 100) {
      k=1;
      cstate=_watertank_t2_burner_b2;
      x_u = x;
      y_u =y;
    }
    else if(OFF && TURN_ON && !ON && !TURN_OFF && True && True) {
      k=1;
      cstate=_watertank_t3_burner_b2;
      x_u = x;
      y_u =y;
    }
    else if(TURN_ON && !OFF && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t1_burner_b2;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && x >= 100 && x <= 100) {
      k=1;
      cstate=_watertank_t2_burner_b1;
      x_u = x;
      x_u = x;
    }
    else if(TURN_ON && !OFF && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t1_burner_b2;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t3_burner_b1;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t1_burner_b2):
    if(y < 0.1 && x >= 20 && x < 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t1_burner_b2_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t1_burner_b2_ode_1(C1x, d, k);
      if(x_u > 100 && x_init <= 100)
        x_u = 100;
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t1_burner_b2_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t1_burner_b2_ode_2(C1y, d, k);
      if(y_u > 0.100000000000000 && y_init <= 0.100000000000000)
        y_u = 0.100000000000000;
      ++k;
      cstate = _watertank_t1_burner_b2;
      force_init_update = False;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1 && x >= 100 && x <= 100) {
      k=1;
      cstate=_watertank_t2_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1 && True) {
      k=1;
      cstate=_watertank_t3_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t1_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && x >= 100 && x <= 100) {
      k=1;
      cstate=_watertank_t2_burner_b2;
      x_u = x;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t1_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
      x_u = x;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t3_burner_b2;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t1_burner_b3):
    if(y >= 0 && y <= 0 && x >= 20 && x < 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t1_burner_b3_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t1_burner_b3_ode_1(C1x, d, k);
      if(x_u > 100 && x_init <= 100)
        x_u = 100;
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t1_burner_b3_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t1_burner_b3_ode_2(C1y);
      ++k;
      cstate = _watertank_t1_burner_b3;
      force_init_update = False;
    }
    else if(TURN_OFF && !OFF && !TURN_ON && !ON && True && x >= 100 && x <= 100) {
      k=1;
      cstate=_watertank_t2_burner_b4;
      x_u = x;
      y_u =y;
    }
    else if(OFF && TURN_OFF && !TURN_ON && !ON && True && True) {
      k=1;
      cstate=_watertank_t3_burner_b4;
      x_u = x;
      y_u =y;
    }
    else if(TURN_OFF && !OFF && !TURN_ON && !ON && True) {
      k=1;
      cstate=_watertank_t1_burner_b4;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && x >= 100 && x <= 100) {
      k=1;
      cstate=_watertank_t2_burner_b3;
      x_u = x;
      x_u = x;
    }
    else if(TURN_OFF && !OFF && !TURN_ON && !ON && True) {
      k=1;
      cstate=_watertank_t1_burner_b4;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t3_burner_b3;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t1_burner_b4):
    if(y < 0.1 && x >= 20 && x < 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t1_burner_b4_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t1_burner_b4_ode_1(C1x, d, k);
      if(x_u > 100 && x_init <= 100)
        x_u = 100;
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t1_burner_b4_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t1_burner_b4_ode_2(C1y, d, k);
      if(y_u > 0.100000000000000 && y_init <= 0.100000000000000)
        y_u = 0.100000000000000;
      ++k;
      cstate = _watertank_t1_burner_b4;
      force_init_update = False;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1 && x >= 100 && x <= 100) {
      k=1;
      cstate=_watertank_t2_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1 && True) {
      k=1;
      cstate=_watertank_t3_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t1_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && x >= 100 && x <= 100) {
      k=1;
      cstate=_watertank_t2_burner_b4;
      x_u = x;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t1_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
      x_u = x;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t3_burner_b4;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t2_burner_b1):
    if(y >= 0 && y <= 0 && x >= 100 && x <= 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t2_burner_b1_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t2_burner_b1_ode_1(C1x);
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t2_burner_b1_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t2_burner_b1_ode_2(C1y);
      ++k;
      cstate = _watertank_t2_burner_b1;
      force_init_update = False;
    }
    else if(OFF && TURN_ON && !ON && !TURN_OFF && True && True) {
      k=1;
      cstate=_watertank_t3_burner_b2;
      x_u = x;
      y_u =y;
    }
    else if(TURN_ON && !OFF && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t2_burner_b2;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t3_burner_b1;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t2_burner_b2):
    if(y < 0.1 && x >= 100 && x <= 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t2_burner_b2_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t2_burner_b2_ode_1(C1x);
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t2_burner_b2_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t2_burner_b2_ode_2(C1y, d, k);
      if(y_u > 0.100000000000000 && y_init <= 0.100000000000000)
        y_u = 0.100000000000000;
      ++k;
      cstate = _watertank_t2_burner_b2;
      force_init_update = False;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1 && True) {
      k=1;
      cstate=_watertank_t3_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t2_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
      x_u = x;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t3_burner_b2;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t2_burner_b3):
    if(y >= 0 && y <= 0 && x >= 100 && x <= 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t2_burner_b3_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t2_burner_b3_ode_1(C1x);
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t2_burner_b3_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t2_burner_b3_ode_2(C1y);
      ++k;
      cstate = _watertank_t2_burner_b3;
      force_init_update = False;
    }
    else if(OFF && TURN_OFF && !TURN_ON && !ON && True && True) {
      k=1;
      cstate=_watertank_t3_burner_b4;
      x_u = x;
      y_u =y;
    }
    else if(TURN_OFF && !OFF && !TURN_ON && !ON && True) {
      k=1;
      cstate=_watertank_t2_burner_b4;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t3_burner_b3;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t2_burner_b4):
    if(y < 0.1 && x >= 100 && x <= 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t2_burner_b4_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t2_burner_b4_ode_1(C1x);
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t2_burner_b4_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t2_burner_b4_ode_2(C1y, d, k);
      if(y_u > 0.100000000000000 && y_init <= 0.100000000000000)
        y_u = 0.100000000000000;
      ++k;
      cstate = _watertank_t2_burner_b4;
      force_init_update = False;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1 && True) {
      k=1;
      cstate=_watertank_t3_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t2_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
      x_u = x;
    }
    else if(OFF && !TURN_ON && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t3_burner_b4;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t3_burner_b1):
    if(y >= 0 && y <= 0 && x > 20 && x <= 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t3_burner_b1_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t3_burner_b1_ode_1(C1x, d, k);
      if(x_u < 20 && x_init >= 20)
        x_u = 20;
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t3_burner_b1_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t3_burner_b1_ode_2(C1y);
      ++k;
      cstate = _watertank_t3_burner_b1;
      force_init_update = False;
    }
    else if(ON && TURN_ON && !OFF && !TURN_OFF && True && True) {
      k=1;
      cstate=_watertank_t1_burner_b2;
      x_u = x;
      y_u =y;
    }
    else if(TURN_ON && !OFF && !ON && !TURN_OFF && True && x >= 20 && x <= 20) {
      k=1;
      cstate=_watertank_t4_burner_b2;
      x_u = x;
      y_u =y;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t1_burner_b1;
      x_u = x;
      x_u = x;
    }
    else if(TURN_ON && !OFF && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t3_burner_b2;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && x >= 20 && x <= 20) {
      k=1;
      cstate=_watertank_t4_burner_b1;
      x_u = x;
      x_u = x;
    }
    else if(TURN_ON && !OFF && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t3_burner_b2;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t3_burner_b2):
    if(y < 0.1 && x > 20 && x <= 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t3_burner_b2_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t3_burner_b2_ode_1(C1x, d, k);
      if(x_u < 20 && x_init >= 20)
        x_u = 20;
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t3_burner_b2_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t3_burner_b2_ode_2(C1y, d, k);
      if(y_u > 0.100000000000000 && y_init <= 0.100000000000000)
        y_u = 0.100000000000000;
      ++k;
      cstate = _watertank_t3_burner_b2;
      force_init_update = False;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && y >= 0.1 && True) {
      k=1;
      cstate=_watertank_t1_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1 && x >= 20 && x <= 20) {
      k=1;
      cstate=_watertank_t4_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t1_burner_b2;
      x_u = x;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t3_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && x >= 20 && x <= 20) {
      k=1;
      cstate=_watertank_t4_burner_b2;
      x_u = x;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t3_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t3_burner_b3):
    if(y >= 0 && y <= 0 && x > 20 && x <= 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t3_burner_b3_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t3_burner_b3_ode_1(C1x, d, k);
      if(x_u < 20 && x_init >= 20)
        x_u = 20;
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t3_burner_b3_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t3_burner_b3_ode_2(C1y);
      ++k;
      cstate = _watertank_t3_burner_b3;
      force_init_update = False;
    }
    else if(ON && TURN_OFF && !OFF && !TURN_ON && True && True) {
      k=1;
      cstate=_watertank_t1_burner_b4;
      x_u = x;
      y_u =y;
    }
    else if(TURN_OFF && !OFF && !TURN_ON && !ON && True && x >= 20 && x <= 20) {
      k=1;
      cstate=_watertank_t4_burner_b4;
      x_u = x;
      y_u =y;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t1_burner_b3;
      x_u = x;
      x_u = x;
    }
    else if(TURN_OFF && !OFF && !TURN_ON && !ON && True) {
      k=1;
      cstate=_watertank_t3_burner_b4;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && x >= 20 && x <= 20) {
      k=1;
      cstate=_watertank_t4_burner_b3;
      x_u = x;
      x_u = x;
    }
    else if(TURN_OFF && !OFF && !TURN_ON && !ON && True) {
      k=1;
      cstate=_watertank_t3_burner_b4;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t3_burner_b4):
    if(y < 0.1 && x > 20 && x <= 100 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t3_burner_b4_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t3_burner_b4_ode_1(C1x, d, k);
      if(x_u < 20 && x_init >= 20)
        x_u = 20;
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t3_burner_b4_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t3_burner_b4_ode_2(C1y, d, k);
      if(y_u > 0.100000000000000 && y_init <= 0.100000000000000)
        y_u = 0.100000000000000;
      ++k;
      cstate = _watertank_t3_burner_b4;
      force_init_update = False;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && y >= 0.1 && True) {
      k=1;
      cstate=_watertank_t1_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1 && x >= 20 && x <= 20) {
      k=1;
      cstate=_watertank_t4_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t1_burner_b4;
      x_u = x;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t3_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && x >= 20 && x <= 20) {
      k=1;
      cstate=_watertank_t4_burner_b4;
      x_u = x;
      x_u = x;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t3_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t4_burner_b1):
    if(y >= 0 && y <= 0 && x >= 20 && x <= 20 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t4_burner_b1_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t4_burner_b1_ode_1(C1x);
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t4_burner_b1_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t4_burner_b1_ode_2(C1y);
      ++k;
      cstate = _watertank_t4_burner_b1;
      force_init_update = False;
    }
    else if(ON && TURN_ON && !OFF && !TURN_OFF && True && True) {
      k=1;
      cstate=_watertank_t1_burner_b2;
      x_u = x;
      y_u =y;
    }
    else if(TURN_ON && !OFF && !ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t4_burner_b2;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t1_burner_b1;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t4_burner_b2):
    if(y < 0.1 && x >= 20 && x <= 20 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t4_burner_b2_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t4_burner_b2_ode_1(C1x);
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t4_burner_b2_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t4_burner_b2_ode_2(C1y, d, k);
      if(y_u > 0.100000000000000 && y_init <= 0.100000000000000)
        y_u = 0.100000000000000;
      ++k;
      cstate = _watertank_t4_burner_b2;
      force_init_update = False;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && y >= 0.1 && True) {
      k=1;
      cstate=_watertank_t1_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t4_burner_b3;
      x_u = x;
      y_u =0;
      signal_u =1;
      x_u = x;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t1_burner_b2;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t4_burner_b3):
    if(y >= 0 && y <= 0 && x >= 20 && x <= 20 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t4_burner_b3_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t4_burner_b3_ode_1(C1x);
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t4_burner_b3_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t4_burner_b3_ode_2(C1y);
      ++k;
      cstate = _watertank_t4_burner_b3;
      force_init_update = False;
    }
    else if(ON && TURN_OFF && !OFF && !TURN_ON && True && True) {
      k=1;
      cstate=_watertank_t1_burner_b4;
      x_u = x;
      y_u =y;
    }
    else if(TURN_OFF && !OFF && !TURN_ON && !ON && True) {
      k=1;
      cstate=_watertank_t4_burner_b4;
      x_u = x;
      y_u =y;
      x_u = x;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t1_burner_b3;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (_watertank_t4_burner_b4):
    if(y < 0.1 && x >= 20 && x <= 20 && !OFF && !TURN_ON && !ON && !TURN_OFF){
      if ((pstate != cstate) || force_init_update){
        C1x = _watertank_t4_burner_b4_init_1(x);
        x_init = x;
      }
      x_u = _watertank_t4_burner_b4_ode_1(C1x);
      if ((pstate != cstate) || force_init_update){
        C1y = _watertank_t4_burner_b4_init_2(y);
        y_init = y;
      }
      y_u = _watertank_t4_burner_b4_ode_2(C1y, d, k);
      if(y_u > 0.100000000000000 && y_init <= 0.100000000000000)
        y_u = 0.100000000000000;
      ++k;
      cstate = _watertank_t4_burner_b4;
      force_init_update = False;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && y >= 0.1 && True) {
      k=1;
      cstate=_watertank_t1_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
    }
    else if(!OFF && !TURN_ON && !ON && !TURN_OFF && y >= 0.1) {
      k=1;
      cstate=_watertank_t4_burner_b1;
      x_u = x;
      y_u =0;
      signal_u =0;
      x_u = x;
    }
    else if(ON && !OFF && !TURN_ON && !TURN_OFF && True) {
      k=1;
      cstate=_watertank_t1_burner_b4;
      x_u = x;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  default: exit(1);
  }
  return cstate;
}

int main(void) {
  x = 20;
  y = 0;
  enum states pstate = -1;
  enum states cstate = _watertank_t4_burner_b1;
  while(True) {
    readInput();
    enum states rstate = watertank_burner(cstate, pstate);
    pstate = cstate;
    cstate = rstate;
    y = y_u;
    x = x_u;
    writeOutput();
  }
  return 0;
}