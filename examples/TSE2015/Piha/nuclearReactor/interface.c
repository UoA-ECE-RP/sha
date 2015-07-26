#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<assert.h>

/* The files are in csv format */
#define OFILE "reactor.csv"

#define TRUE 1
#define FALSE 0
#define RUNS 10000000

extern double x;
double sumX=0;
extern double signal_u;
double signal_pre=0;

/* The step size */
double d = 0.01;

/* The events to emit */
int add1=0, add2=0, remove1=0, remove2=0;

/* The tick counter */
/* It is static to hide it inside this file */
static size_t tick = 0;

/* The output file pointer */
FILE *fo = NULL;


/* Read input x from file */
void readInput() {
  if (signal_u != signal_pre){
    if (signal_u==1){
      add1=1;
    }
    else if (signal_u==2){
      add2=1;
    }
    else if (signal_u==0.1){
      remove1=1;
    }
    else if (signal_u==0.2){
      remove2=1;
    }
    signal_pre=signal_u;
  }
  else {
    add1=0;
    add2=0;
    remove1=0;
    remove2=0;}
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
  tick++;
  sumX+=x;
  //fprintf(fo, "%ld,%s,%f,%s,%d,%s,%d,%s,%f\n", ++tick, "x", x, "add1", add1, "remove1", remove1, "add2", add2, "remove2", remove2, "signal", signal_u);

  if (tick==RUNS) {
	  double r =RUNS;
	  
    printf("Finished");
    fprintf(fo, "%ld,%f\n", tick, sumX/r);
    exit(1);}  
}

