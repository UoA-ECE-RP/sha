#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<assert.h>

/* The files are in csv format */
#define OFILE "train_control.csv"

#define TRUE 1
#define FALSE 0

extern double v,z;
double sumZ=0, sumV=0;

/* The step size */
double d = 0.2;
#define RUNS 10000000

/* The events to read from file */


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
  //fprintf(fo, "%ld,%f,%f\n", ++tick, z, v);

   sumZ+=z;
   sumV+=v;
   tick++;

 //fprintf(fo, "%ld,%f\n", tick, x);
   if (tick==RUNS) {
     double r = RUNS;
     fprintf(fo, "%ld,%f,%f\n", tick, sumZ/r,sumV/r);
     exit(1);
   }
 }

