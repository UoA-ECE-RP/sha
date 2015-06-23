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

/* The step size */
double d = 0.01;

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
  fprintf(fo, "%ld,%f,%f\n", ++tick, x1, x2);

  if (tick==5000) {
    printf("Finished");
    exit(1);}
}

