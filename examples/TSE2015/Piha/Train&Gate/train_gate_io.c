#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<assert.h>

/* The files are in csv format */
#define OFILE "train_gate.csv"

#define TRUE 1
#define FALSE 0

extern double x,y;
double sumX=0, sumY=0;
extern double signal_u;
double signal_pre=0;



/* The step size */
double d = 0.01;
#define RUNS 10000000

/* The events to print */
int DOWN=0, UP=0;

/* The tick counter */
/* It is static to hide it inside this file */
static size_t tick = 0;

/* The output file pointer */
FILE *fo = NULL;

void readInput() {
  if (signal_u != signal_pre){
    if (signal_u==1){
      DOWN=1;
      UP=0;
    }
    else{
      DOWN=0;
      UP=1;
    }
    signal_pre=signal_u;
  }
  else {
    DOWN=0;
    UP=0;}
}


/* Write output x to file */
void writeOutput(){
  static unsigned char count = 0;
  if (0 == count){
    fo = fopen(OFILE, "w");
    if (fo == NULL){
      perror(OFILE);
      exit(1);
    }
    ++count;
  }

  sumX+=x;
  sumY+=y;
  tick++;

  if (tick==RUNS) {
    double r = RUNS;
    fprintf(fo, "%ld,%f,%f\n", tick, sumX/r, sumY/r);
    exit(1);}
}


