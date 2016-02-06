#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<assert.h>

/* The files are in csv format */
#define OFILE "cellout.csv"
//#define IFILE "cellin.csv"

#define TRUE 1
#define FALSE 0

extern double x;
double sumX=0;
extern double signal_u;

/* The step size */
double d = 1;
#define RUNS 10000000


/* The events to emit */
int ACTnext=0;

/* The events to read */
int ACTnode=0;


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
  ACTnode = FALSE;

  if(count == 6){
	   ACTnode = TRUE;
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
  fprintf(fo, "%ld,%f\n", ++tick, x, "signal", signal_u);
  tick++;
  sumX+=x;

  if (tick==RUNS){
    double r = RUNS;
	fprintf(fo, "%ld,%f\n", ++tick, sumX/r);
	exit(1);
  }
}
