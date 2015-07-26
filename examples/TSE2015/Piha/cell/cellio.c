#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<assert.h>

/* The files are in csv format */
#define OFILE "cellout.csv"
#define IFILE "cellin.csv"

#define TRUE 1
#define FALSE 0

extern double x;
double sumX=0;

/* The step size */
double d = 0.01;
#define RUNS 10000000

/* The events to read from file */
unsigned char VS, VSP;


/* The tick counter */
/* It is static to hide it inside this file */
static size_t tick = 0;

/* The output file pointer */
FILE *fo = NULL;

/* The input file pointer */
FILE *fi = NULL;

static inline unsigned char getValue(unsigned char t, char* e){
  assert(t == TRUE || t == FALSE);
  return t;
}

/* Read input x from file */
void readInput() {
  static unsigned int count = 0;
  /* The check here is very expensive! */
  VS = FALSE;
  VSP = FALSE;
  
  if(count == 6){
	VS = TRUE;
	VSP = FALSE;
  }
  count++;

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
  //fprintf(fo, "%ld,%f\n", ++tick, x);
  tick++;
  sumX+=x;
  
  if (tick==RUNS){
    double r = RUNS;
	fprintf(fo, "%ld,%f\n", ++tick, sumX/r);
	exit(1);
  }
}

