#include<stdint.h>

#include<stdlib.h>

#include<stdio.h>

#define True 1

#define False 0

// Global variables from outside this HA

// Global variables in this HA

double signal_u;

//Events

extern unsigned char ACTnext, ACTnode;

extern void readInput();

extern void writeOutput();

//Continous variables

double x;

//Continous variable update

double x_u;

//Continous variable init

double x_init;

//The constant variable

double C1x;

//Step-size constant d

extern double d;

//Nstep constant k

double k;

//States

enum states {Rest , Cond , ERP , RRP};

//Previous state variable

#include "Rest.h"
#include <math.h>
double Rest_ode_1(double C1x, double d, double k) {
   double Rest_ode_1_result;
   Rest_ode_1_result = C1x + d*k;
   return Rest_ode_1_result;
}
double Rest_init_1(double x_u) {
   double Rest_init_1_result;
   Rest_init_1_result = x_u;
   return Rest_init_1_result;
}


#include "Cond.h"
#include <math.h>
double Cond_ode_1(double C1x, double d, double k) {
   double Cond_ode_1_result;
   Cond_ode_1_result = C1x + d*k;
   return Cond_ode_1_result;
}
double Cond_init_1(double x_u) {
   double Cond_init_1_result;
   Cond_init_1_result = x_u;
   return Cond_init_1_result;
}


#include "ERP.h"
#include <math.h>
double ERP_ode_1(double C1x, double d, double k) {
   double ERP_ode_1_result;
   ERP_ode_1_result = C1x + d*k;
   return ERP_ode_1_result;
}
double ERP_init_1(double x_u) {
   double ERP_init_1_result;
   ERP_init_1_result = x_u;
   return ERP_init_1_result;
}


#include "RRP.h"
#include <math.h>
double RRP_ode_1(double C1x, double d, double k) {
   double RRP_ode_1_result;
   RRP_ode_1_result = C1x + d*k;
   return RRP_ode_1_result;
}
double RRP_init_1(double x_u) {
   double RRP_init_1_result;
   RRP_init_1_result = x_u;
   return RRP_init_1_result;
}


enum states cell_TA(enum states cstate, enum states pstate) {
  static double fk;
  static unsigned char force_init_update;
  switch (cstate) {
  case (Rest):
    if(x <= 300 && !ACTnext && !ACTnode){
      if ((pstate != cstate) || force_init_update){
        C1x = Rest_init_1(x);
        x_init = x;
      }
      x_u = Rest_ode_1(C1x, d, k);
      if(x_u > 300 && x_init <= 300)
        x_u = 300;
      ++k;
      cstate = Rest;
      force_init_update = False;
    }
    else if(True && x >= 300) {
      k=1;
      cstate=Cond;
      x_u =0;
    }
    else if(ACTnode && True) {
      k=1;
      cstate=Cond;
      x_u =0;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (Cond):
    if(x <= 10 && !ACTnext && !ACTnode){
      if ((pstate != cstate) || force_init_update){
        C1x = Cond_init_1(x);
        x_init = x;
      }
      x_u = Cond_ode_1(C1x, d, k);
      if(x_u > 10 && x_init <= 10)
        x_u = 10;
      ++k;
      cstate = Cond;
      force_init_update = False;
    }
    else if(ACTnext && x >= 10) {
      k=1;
      cstate=ERP;
      x_u =0;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (ERP):
    if(x <= 200 && !ACTnext && !ACTnode){
      if ((pstate != cstate) || force_init_update){
        C1x = ERP_init_1(x);
        x_init = x;
      }
      x_u = ERP_ode_1(C1x, d, k);
      if(x_u > 200 && x_init <= 200)
        x_u = 200;
      ++k;
      cstate = ERP;
      force_init_update = False;
    }
    else if(True && x >= 200) {
      k=1;
      cstate=RRP;
      x_u =0;
    }
    else {
      fprintf(stderr,"Unreachable state!");
      exit(1);
    }
    break;
  case (RRP):
    if(x <= 100 && !ACTnext && !ACTnode){
      if ((pstate != cstate) || force_init_update){
        C1x = RRP_init_1(x);
        x_init = x;
      }
      x_u = RRP_ode_1(C1x, d, k);
      if(x_u > 100 && x_init <= 100)
        x_u = 100;
      ++k;
      cstate = RRP;
      force_init_update = False;
    }
    else if(ACTnode && True) {
      k=1;
      cstate=Cond;
      x_u =0;
    }
    else if(True && x >= 100) {
      k=1;
      cstate=Rest;
      x_u =0;
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
  x = 0;
  enum states pstate = -1;
  enum states cstate = Rest;
  while(True) {
    readInput();
    enum states rstate = cell_TA(cstate, pstate);
    pstate = cstate;
    cstate = rstate;
    x = x_u;
    writeOutput();
  }
  return 0;
}