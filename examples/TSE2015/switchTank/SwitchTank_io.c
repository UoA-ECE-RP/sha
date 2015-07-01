#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<assert.h>

/* The files are in csv format */
#define OFILE "switchtank.csv"

#define TRUE 1
#define FALSE 0

extern double x1,x2;
double sum1=0,sum2=0;

/* The step size */
double d = 0.01;

/* The events to read from file */

#define RUNS 10000000

/* The tick counter */
/* It is static to hide it inside this file */
static size_t tick = 0;

/* The output file pointer */
FILE *fo = NULL;


void readInput() {
  
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

  sum1+=x1;
  sum2+=x2;
  tick++;

  if (tick==RUNS) {
    double r = RUNS;
    fprintf(fo, "%ld,%f,%f\n", tick, sum1/r, sum2/r);
    exit(1);}
}

