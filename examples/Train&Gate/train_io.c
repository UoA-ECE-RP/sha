#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<assert.h>

/* The files are in csv format */
#define OFILE "train.csv"

#define TRUE 1
#define FALSE 0

extern double y;
extern int signal_u;
int signal_pre=0;

/* The step size */
double d = 0.2;

/* The events to print */
int DOWN=0, UP=0;


/* The tick counter */
/* It is static to hide it inside this file */
static size_t tick = 0;

/* The output file pointer */
FILE *fo = NULL;

void setEvent(int signal_u){

  if (signal_u != signal_pre){
    if (signal_u==0){
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

  setEvent(signal_u);
  fprintf(fo, "%ld,%f,%s,%d,%s,%d\n", ++tick, y, "DOWN", DOWN, "UP", UP);

  if (tick==5000) {
    printf("Finished");
    exit(1);}
}


