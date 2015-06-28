#include<stdint.h>

#include<stdlib.h>

#include<stdio.h>

#define True 1

#define False 0

// Global variables from outside this HA

//Events

extern void readInput();

extern void writeOutput();

//Continous variables

double x2, x1;

//Continous variable update

double x2_u, x1_u;

//The constant variable

double C1x1, C1x2;

//Step-size constant d

extern double d;

//Nstep constant k

double k;

//States

enum states {t1 , t2};

//Previous state variable

#include "t1.h"
#include <math.h>
double t1_ode_1(double C1x1, double d, double k) {
   double t1_ode_1_result;
   t1_ode_1_result = C1x1 + 0.7*d*k;
   return t1_ode_1_result;
}
double t1_ode_2(double C1x2, double d, double k) {
   double t1_ode_2_result;
   t1_ode_2_result = C1x2 - 0.4*d*k;
   return t1_ode_2_result;
}
double t1_init_1(double x1_u) {
   double t1_init_1_result;
   t1_init_1_result = x1_u;
   return t1_init_1_result;
}
double t1_init_2(double x2_u) {
   double t1_init_2_result;
   t1_init_2_result = x2_u;
   return t1_init_2_result;
}


#include "t2.h"
#include <math.h>
double t2_ode_1(double C1x1, double d, double k) {
   double t2_ode_1_result;
   t2_ode_1_result = C1x1 - 0.3*d*k;
   return t2_ode_1_result;
}
double t2_ode_2(double C1x2, double d, double k) {
   double t2_ode_2_result;
   t2_ode_2_result = C1x2 + 0.6*d*k;
   return t2_ode_2_result;
}
double t2_init_1(double x1_u) {
   double t2_init_1_result;
   t2_init_1_result = x1_u;
   return t2_init_1_result;
}
double t2_init_2(double x2_u) {
   double t2_init_2_result;
   t2_init_2_result = x2_u;
   return t2_init_2_result;
}


enum states SwitchTank(enum states cstate, enum states pstate) {
  switch (cstate) {
  double fk;
  unsigned char force_init_update;
  case (t1):
    if(x1 <= 1 && x2 > 0.25){
      if ((pstate != cstate) || force_init_update){
        C1x1 = t1_init_1(x1);
      }
      x1_u = t1_ode_1(C1x1, d, k);
      if(x1_u > 1 && C1x1 < 1)
        x1_u = 1;
      if ((pstate != cstate) || force_init_update){
        C1x2 = t1_init_2(x2);
      }
      x2_u = t1_ode_2(C1x2, d, k);
      if(x2_u < 0.250000000000000 && C1x2 > 0.250000000000000)
        x2_u = 0.250000000000000;
      ++k;
      cstate = t1;
      force_init_update = False;
    }
    else if(True && x2 <= 0.25) {
      k=1;
      cstate=t2;
      x1_u = x1;
      x2_u = x2;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (t2):
    if(x1 > 0.25 && x2 <= 1){
      if ((pstate != cstate) || force_init_update){
        C1x1 = t2_init_1(x1);
      }
      x1_u = t2_ode_1(C1x1, d, k);
      if(x1_u < 0.250000000000000 && C1x1 > 0.250000000000000)
        x1_u = 0.250000000000000;
      if ((pstate != cstate) || force_init_update){
        C1x2 = t2_init_2(x2);
      }
      x2_u = t2_ode_2(C1x2, d, k);
      if(x2_u > 1 && C1x2 < 1)
        x2_u = 1;
      ++k;
      cstate = t2;
      force_init_update = False;
    }
    else if(True && x1 <= 0.25) {
      k=1;
      cstate=t1;
      x1_u = x1;
      x2_u = x2;
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
  x1 = 0.5;
  x2 = 0.5;
  enum states pstate = -1;
  enum states cstate = t1;
  while(True) {
    readInput();
    enum states rstate = SwitchTank(cstate, pstate);
    pstate = cstate;
    cstate = rstate;
    x2 = x2_u;
    x1 = x1_u;
    writeOutput();
  }
  return 0;
}