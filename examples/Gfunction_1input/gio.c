#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<assert.h>
#include <time.h>

/* The files are in csv format */
#define OFILE "gout.csv"
#define IFILE1 "gin1.csv"

#define TRUE 1
#define FALSE 0

double x1; //inputs continuous

//Continuous variables and Outputs

extern double v_aggregate; //output continuous g
unsigned char VSP, VS;

/* The tick counter */
/* It is static to hide it inside this file */
static size_t tick = 0;

/* The output file pointer */
FILE *fo = NULL;

/* The input file pointer */
FILE *fi1 = NULL;

 unsigned int retTime;
 void waitFor (unsigned int secs) {
    retTime = time(0) + secs;     // Get finishing time.
    while (time(0) < retTime);    // Loop until it arrives.
}

static inline unsigned char getValue(unsigned char t, char* e){
  assert(t == TRUE || t == FALSE);
  return t;
}

/* Read input x from file */
void readInput() {
  static unsigned char count = 0;
  /* The check here is very expensive! */
  if(0 == count) {
    fi1 = fopen(IFILE1, "r");
    if (fi1 == NULL){
      perror(IFILE1);
      exit(1);
    }

    ++count;
  }
  
  /* The format of input is 1 line/tick */
  /* for the events above the format is: */
  /*
    ON, ON_Value, C, C_Value, B, B_Value, OFF, OFF_Value
  */
  char in1[256];
  while (fgets(in1,255,fi1) == NULL ){
	perror("No input");
	waitFor(2);
	//exit(1);
  }
  //else{
	  // input 1
    char *ret = NULL, *v = NULL;
    ret = strtok(in1, ",");
    if(ret == NULL){
      /* This means nothing found! */
      /* Set all events to false */
	  perror("NULL strtok error");
      exit(1);
    }
    while(ret != NULL) {
      v = strtok(NULL, ",");
      if (v != NULL) {
		if (strcmp(ret, "x1") == 0){
			//x1 = getValue((unsigned char)atoi(v), ret);
			x1 = atof(v);
		}
      }
      else {
		perror("NULL while scanning input");
		exit(1);
      }

      /* Read the next one! */
      ret = strtok(NULL, ",");
    }
	
	
 // }
  
  
  
  fprintf(stdout, "%s:%f  tick:%ld\n", "x1", x1, tick);
  fflush(stdout);
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
	fclose(fo);
    ++count;
  }
    // each write...
    fo = fopen(OFILE, "a");
    if (fo == NULL){
      perror(OFILE);
      exit(1);
    }
	fprintf(fo, "VS,0,VSP,0,g,%f\n", v_aggregate);
	fflush(fo);
	fclose(fo);
	
	tick++;
}

