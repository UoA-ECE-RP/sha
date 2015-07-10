// This file is generated by FBC.

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include<stdint.h>

#include<stdlib.h>

#include<stdio.h>

#define True 1

#define False 0

// Global variables from outside this HA

  double fk;
  unsigned char force_init_update;


//Continous variables

double x2, x1;

//Continous variable update

double x2_u, x1_u;

//Continous variable init

double x2_init, x1_init;

//The constant variable

double C1x1, C1x2;

//Step-size constant d

static double d=0.01;

//Nstep constant k

double k;

//States

enum states {t1 , t2};


static enum states pstate = -1;
static enum states cstate = t1;



#endif//GLOBAL_H_
