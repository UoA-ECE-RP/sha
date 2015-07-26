#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<assert.h>

/* The files are in csv format */
#define OFILE "sysout.csv"
#define IFILE "sysin.csv"

#define TRUE 1
#define FALSE 0
#define RUNS 10000000

extern double x, y;
double xSum=0;
extern double signal_u;
double signal_pre=0;

/* The step size */
double d = 0.01;

/* The events to emit */
int ON=0, OFF=0;

/* The events to read */
int TURN_ON=0, TURN_OFF=0;

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

	printf("read input\n");
  if (signal_u != signal_pre){
    if (signal_u==1){
      ON=1;
    }
    else if (signal_u==0){
      OFF=1;
    }
   
    signal_pre=signal_u;
  }
  else {
    ON=0;
    OFF=0;
   }


  static unsigned char counter = 0;
  
  /* The check here is very expensive! */
  
	TURN_ON = FALSE;
    TURN_OFF = FALSE;
	
  if(0 == counter) {
  /*  fi = fopen(IFILE, "r");
    if (fi == NULL){
      perror(IFILE);
      exit(1);
    }*/
	
  }
  
  if(counter==10){
	TURN_ON = TRUE;
    TURN_OFF = FALSE;
  }
  
  
   ++counter;
  
  
  /* The format of input is 1 line/tick */
  /* for the events above the format is: */
  /*
    ON, ON_Value, C, C_Value, B, B_Value, OFF, OFF_Value
  */
  /*char in[256];
  if (fgets(in,255,fi) == NULL){
    TURN_ON = FALSE;
    TURN_OFF = FALSE;
  }
  else{
    char *ret = NULL, *v = NULL;
    ret = strtok(in, ",");
    if(ret == NULL){
      // This means nothing found! 
      // Set all events to false 
      TURN_ON = FALSE;
      TURN_OFF = FALSE;
    }
    while(ret != NULL) {
      v = strtok(NULL, ",");
      if (v != NULL) {
        if (strcmp(ret, "TURN_ON") == 0)
          TURN_ON = getValue((unsigned char)atoi(v), ret);
        else if(strcmp(ret, "TURN_OFF") == 0)
          TURN_OFF = getValue((unsigned char)atoi(v), ret);
      }
      else {
        perror("NULL while scanning input");
        exit(1);
      }
      // Read the next one! 
      ret = strtok(NULL, ",");
    }
  }*/

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
  //fprintf(fo, "%ld,%s,%f,%s,%f,%s,%d,%s,%d,%s,%f\n", ++tick, "x", x, "y", y, "ON", ON, "OFF", OFF, "signal", signal_u);
  xSum+=x;
  tick++;
  if (tick==RUNS) {
    //printf("Finished");
    double r = RUNS;
    fprintf(fo, "%ld,%f\n", tick, xSum/r);
    exit(1);}  
}

