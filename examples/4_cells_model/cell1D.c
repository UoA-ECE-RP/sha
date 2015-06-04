#include<stdint.h>

#include<stdlib.h>

#include<stdio.h>

#define True 1

#define False 0

//Events

extern unsigned char VSP, VS;
extern double g;

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

enum states {t1 , t2 , t3 , t4};

//Previous state variable

#include "t1.h"
#include <math.h>
double t1_ode_1(double C1, double d, double k) {
   double t1_ode_1_result;
   t1_ode_1_result = C1*exp(-0.1*d*k)+g*d*k;
   return t1_ode_1_result;
}
double t1_init_1(double x_u) {
   double t1_init_1_result;
   t1_init_1_result = x_u;
   return t1_init_1_result;
}


#include "t2.h"
#include <math.h>
double t2_ode_1(double C1, double d, double k) {
   double t2_ode_1_result;
   t2_ode_1_result = C1 + 800*d*k+g*d*k;
   return t2_ode_1_result;
}
double t2_init_1(double x_u) {
   double t2_init_1_result;
   t2_init_1_result = x_u;
   return t2_init_1_result;
}


#include "t3.h"
#include <math.h>
double t3_ode_1(double C1, double d, double k) {
   double t3_ode_1_result;
   t3_ode_1_result = C1*exp(200.0*d*k);
   return t3_ode_1_result;
}
double t3_init_1(double x_u) {
   double t3_init_1_result;
   t3_init_1_result = x_u;
   return t3_init_1_result;
}


#include "t4.h"
#include <math.h>
double t4_ode_1(double C1, double d, double k) {
   double t4_ode_1_result;
   t4_ode_1_result = C1*exp(-0.002*d*k);
   return t4_ode_1_result;
}
double t4_init_1(double x_u) {
   double t4_init_1_result;
   t4_init_1_result = x_u;
   return t4_init_1_result;
}


enum states cell1D(enum states cstate, enum states pstate) {
  switch (cstate) {
  case (t1):
    if(x <= 20 && !VSP && !VS){
      if (pstate != cstate)
        C1 = t1_init_1(x);
      x_u = t1_ode_1(C1, d, k);
      if(x_u < 20 && C1 > 20)
        x_u = 20;
      ++k;
      cstate = t1;
    }
    else if(VS && !VSP && x < 20) {
      k=0;
      cstate=t2;
      x_u = x;
    }
    else if(!VSP && !VS && x >= 20) {
      k=0;
      cstate=t3;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (t2):
    if(x < 20 && !VSP && !VS){
      if (pstate != cstate)
        C1 = t2_init_1(x);
      x_u = t2_ode_1(C1, d, k);
      if(x_u > 20 && C1 < 20)
        x_u = 20;
      ++k;
      cstate = t2;
    }
    else if(VSP && !VS && x < 20) {
      k=0;
      cstate=t1;
      x_u = x;
    }
    else if(!VSP && !VS && x <= 20 && x >= 20) {
      k=0;
      cstate=t3;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (t3):
    if(x >= 20 && x < 138 && !VSP && !VS){
      if (pstate != cstate)
        C1 = t3_init_1(x);
      x_u = t3_ode_1(C1, d, k);
      if(x_u > 138 && C1 < 138)
        x_u = 138;
      ++k;
      cstate = t3;
    }
    else if(!VSP && !VS && x <= 138 && x >= 138) {
      k=0;
      cstate=t4;
      x_u = x;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (t4):
    if(x > 20 && x <= 138 && !VSP && !VS){
      if (pstate != cstate)
        C1 = t4_init_1(x);
      x_u = t4_ode_1(C1, d, k);
      if(x_u < 20 && C1 > 20)
        x_u = 20;
      ++k;
      cstate = t4;
    }
    else if(!VSP && !VS && x <= 20 && x >= 20) {
      k=0;
      cstate=t1;
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
  x = 0.0001;
  enum states pstate = -1;
  enum states cstate = t1;
  while(True) {
    readInput();
    enum states rstate = cell1D(cstate, pstate);
    pstate = cstate;
    cstate = rstate;
    x = x_u;
    writeOutput();
  }
  return 0;
}