#include<stdint.h>

#include<stdlib.h>

#include<stdio.h>

#define True 1

#define False 0

//Events

extern unsigned char valid, shot;

extern void readInput();

extern void writeOutput();

//Continous variables

double y, x;

//Continous variable update

double y_u, x_u;

//The constant variable

double C1;

//Step-size constant d

extern double d;

//Nstep constant k

double k;

//States

enum states {t0 , t1 , t2 , t3 , t4};

//Previous state variable

#include "t0.h"
#include <math.h>
double t0_ode_1(double C1) {
   double t0_ode_1_result;
   t0_ode_1_result = C1;
   return t0_ode_1_result;
}
double t0_ode_2(double C1) {
   double t0_ode_2_result;
   t0_ode_2_result = C1;
   return t0_ode_2_result;
}
double t0_init_1(double x_u) {
   double t0_init_1_result;
   t0_init_1_result = x_u;
   return t0_init_1_result;
}
double t0_init_2(double y_u) {
   double t0_init_2_result;
   t0_init_2_result = y_u;
   return t0_init_2_result;
}


#include "t1.h"
#include <math.h>
double t1_ode_1(double C1, double d, double k) {
   double t1_ode_1_result;
   t1_ode_1_result = C1*exp(0.866*d*k);
   return t1_ode_1_result;
}
double t1_ode_2(double C1, double d, double k) {
   double t1_ode_2_result;
   t1_ode_2_result = C1*exp(0.5*d*k);
   return t1_ode_2_result;
}
double t1_init_1(double x_u) {
   double t1_init_1_result;
   t1_init_1_result = x_u;
   return t1_init_1_result;
}
double t1_init_2(double y_u) {
   double t1_init_2_result;
   t1_init_2_result = y_u;
   return t1_init_2_result;
}


#include "t2.h"
#include <math.h>
double t2_ode_1(double C1, double d, double k) {
   double t2_ode_1_result;
   t2_ode_1_result = C1*exp(0.866*d*k);
   return t2_ode_1_result;
}
double t2_ode_2(double C1, double d, double k) {
   double t2_ode_2_result;
   t2_ode_2_result = C1*exp(-0.5*d*k);
   return t2_ode_2_result;
}
double t2_init_1(double x_u) {
   double t2_init_1_result;
   t2_init_1_result = x_u;
   return t2_init_1_result;
}
double t2_init_2(double y_u) {
   double t2_init_2_result;
   t2_init_2_result = y_u;
   return t2_init_2_result;
}


#include "t3.h"
#include <math.h>
double t3_ode_1(double C1, double d, double k) {
   double t3_ode_1_result;
   t3_ode_1_result = C1*exp(-0.866*d*k);
   return t3_ode_1_result;
}
double t3_ode_2(double C1, double d, double k) {
   double t3_ode_2_result;
   t3_ode_2_result = C1*exp(-0.5*d*k);
   return t3_ode_2_result;
}
double t3_init_1(double x_u) {
   double t3_init_1_result;
   t3_init_1_result = x_u;
   return t3_init_1_result;
}
double t3_init_2(double y_u) {
   double t3_init_2_result;
   t3_init_2_result = y_u;
   return t3_init_2_result;
}


#include "t4.h"
#include <math.h>
double t4_ode_1(double C1, double d, double k) {
   double t4_ode_1_result;
   t4_ode_1_result = C1*exp(-0.866*d*k);
   return t4_ode_1_result;
}
double t4_ode_2(double C1, double d, double k) {
   double t4_ode_2_result;
   t4_ode_2_result = C1*exp(0.5*d*k);
   return t4_ode_2_result;
}
double t4_init_1(double x_u) {
   double t4_init_1_result;
   t4_init_1_result = x_u;
   return t4_init_1_result;
}
double t4_init_2(double y_u) {
   double t4_init_2_result;
   t4_init_2_result = y_u;
   return t4_init_2_result;
}


enum states billardBall(enum states cstate, enum states pstate) {
  switch (cstate) {
  case (t0):
    if(y >= 0 && y <= 10 && x >= 0 && x <= 33 && !valid && !shot){
      if (pstate != cstate)
        C1 = t0_init_1(x);
      x_u = t0_ode_1(C1);
      if (pstate != cstate)
        C1 = t0_init_2(y);
      y_u = t0_ode_2(C1);
      ++k;
      cstate = t0;
    }
    else if(shot && !valid && True) {
      k=0;
      cstate=t1;
      y_u = y;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (t1):
    if(y <= 10 && x <= 33 && !valid && !shot){
      if (pstate != cstate)
        C1 = t1_init_1(x);
      x_u = t1_ode_1(C1);
      if (pstate != cstate)
        C1 = t1_init_2(y);
      y_u = t1_ode_2(C1);
      ++k;
      cstate = t1;
    }
    else if(valid && !shot && y >= 10) {
      k=0;
      cstate=t2;
      y_u = y;
    }
    else if(valid && !shot && x >= 33) {
      k=0;
      cstate=t4;
      y_u = y;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (t2):
    if(x < 33 && !valid && !shot){
      if (pstate != cstate)
        C1 = t2_init_1(x);
      x_u = t2_ode_1(C1);
      if (pstate != cstate)
        C1 = t2_init_2(y);
      y_u = t2_ode_2(C1);
      ++k;
      cstate = t2;
    }
    else if(valid && !shot && x >= 33) {
      k=0;
      cstate=t3;
      y_u = y;
    }
    else if(valid && !shot && y <= 0) {
      k=0;
      cstate=t1;
      y_u = y;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (t3):
    if(y > 0 && !valid && !shot){
      if (pstate != cstate)
        C1 = t3_init_1(x);
      x_u = t3_ode_1(C1);
      if (pstate != cstate)
        C1 = t3_init_2(y);
      y_u = t3_ode_2(C1);
      ++k;
      cstate = t3;
    }
    else if(valid && !shot && y <= 0) {
      k=0;
      cstate=t4;
      y_u = y;
    }
    else if(valid && !shot && x <= 0) {
      k=0;
      cstate=t2;
      y_u = y;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (t4):
    if(x > 0 && !valid && !shot){
      if (pstate != cstate)
        C1 = t4_init_1(x);
      x_u = t4_ode_1(C1);
      if (pstate != cstate)
        C1 = t4_init_2(y);
      y_u = t4_ode_2(C1);
      ++k;
      cstate = t4;
    }
    else if(valid && !shot && x <= 0) {
      k=0;
      cstate=t1;
      y_u = y;
    }
    else if(valid && !shot && y >= 10) {
      k=0;
      cstate=t3;
      y_u = y;
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
  x = 5;
  y = 5;
  enum states pstate = -1;
  enum states cstate = t0;
  while(True) {
    readInput();
    enum states rstate = billardBall(cstate, pstate);
    pstate = cstate;
    cstate = rstate;
    y = y_u;
    x = x_u;
    writeOutput();
  }
  return 0;
}