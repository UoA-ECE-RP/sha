#include<stdint.h>

#include<stdlib.h>

#include<stdio.h>

#define True 1

#define False 0

//Events

extern unsigned char remove2, remove1, add1, add2;

extern void readInput();

extern void writeOutput();

//Continous variables

double x;

//Continous variable update

double x_u;

//The constant variable

double C1;

//Step-size constant d

extern double d;

//Nstep constant k

double k;

//States

enum states {t0 , t1 , t2};

//Previous state variable

#include "t0.h"
#include <math.h>
double t0_ode_1(double C1, double d, double k) {
   double t0_ode_1_result;
   t0_ode_1_result = C1*exp(0.1*d*k) + 500.0;
   return t0_ode_1_result;
}
double t0_init_1(double x_u) {
   double t0_init_1_result;
   t0_init_1_result = x_u - 500.0;
   return t0_init_1_result;
}


#include "t1.h"
#include <math.h>
double t1_ode_1(double C1, double d, double k) {
   double t1_ode_1_result;
   t1_ode_1_result = C1*exp(0.1*d*k) + 560.0;
   return t1_ode_1_result;
}
double t1_init_1(double x_u) {
   double t1_init_1_result;
   t1_init_1_result = x_u - 560.0;
   return t1_init_1_result;
}


#include "t2.h"
#include <math.h>
double t2_ode_1(double C1, double d, double k) {
   double t2_ode_1_result;
   t2_ode_1_result = C1*exp(0.1*d*k) + 600.0;
   return t2_ode_1_result;
}
double t2_init_1(double x_u) {
   double t2_init_1_result;
   t2_init_1_result = x_u - 600.0;
   return t2_init_1_result;
}


enum states reactor(enum states cstate, enum states pstate) {
  switch (cstate) {
  case (t0):
    if(x <= 550 && !remove2 && !remove1 && !add1 && !add2){
      if (pstate != cstate)
        C1 = t0_init_1(x);
      x_u = t0_ode_1(C1, d, k);
      if(x_u > 550)
        x_u = 550;
      ++k;
      cstate = t0;
    }
    else if(add1 && !remove2 && !remove1 && !add2 && x >= 550) {
      k=0;
      cstate=t1;
      x_u = x;
    }
    else if(add2 && !remove2 && !remove1 && !add1 && x >= 550) {
      k=0;
      cstate=t2;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (t1):
    if(x >= 510 && !remove2 && !remove1 && !add1 && !add2){
      if (pstate != cstate)
        C1 = t1_init_1(x);
      x_u = t1_ode_1(C1, d, k);
      if(x_u < 510)
        x_u = 510;
      ++k;
      cstate = t1;
    }
    else if(remove1 && !remove2 && !add1 && !add2 && x <= 510) {
      k=0;
      cstate=t0;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (t2):
    if(x >= 510 && !remove2 && !remove1 && !add1 && !add2){
      if (pstate != cstate)
        C1 = t2_init_1(x);
      x_u = t2_ode_1(C1, d, k);
      if(x_u < 510)
        x_u = 510;
      ++k;
      cstate = t2;
    }
    else if(remove2 && !remove1 && !add1 && !add2 && x <= 510) {
      k=0;
      cstate=t0;
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
  x = 510;
  enum states pstate = -1;
  enum states cstate = t0;
  while(True) {
    readInput();
    enum states rstate = reactor(cstate, pstate);
    pstate = cstate;
    cstate = rstate;
    x = x_u;
    writeOutput();
  }
  return 0;
}