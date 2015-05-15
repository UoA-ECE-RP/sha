#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<assert.h>

/* The files are in csv format */
#define OFILE "wout.csv"
#define IFILE "win.csv"

#define TRUE 1
#define FALSE 0

/* The step size */
double d = 0.00005;

/* The output variable that needs to be written to file */
/* It is extern, because the real thing is defined in the
   compiled code */
extern double x;

/* The events to read from file */
unsigned char ON, C, B, OFF;

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
  static unsigned char count = 0;
  /* The check here is very expensive! */
  if(0 == count) {
    fi = fopen(IFILE, "r");
    if (fi == NULL){
      perror(IFILE);
      exit(1);
    }
    ++count;
  }
  
  /* The format of input is 1 line/tick */
  /* for the events above the format is: */
  /*
    ON, ON_Value, C, C_Value, B, B_Value, OFF, OFF_Value
  */
  char in[256];
  if (fgets(in,255,fi) == NULL){
    perror("Could not scan inputs\n");
    exit(1);
  }
  else{
    char *ret = NULL, *v = NULL;
    ret = strtok(in, ",");
    if(ret == NULL){
      /* This means nothing found! */
      /* Set all events to false */
      ON = FALSE;
      C = FALSE;
      B = FALSE;
      OFF = FALSE;
    }
    while(ret != NULL) {
      v = strtok(NULL, ",");
      if (v != NULL) {
	if (strcmp(ret, "ON") == 0)
	  ON = getValue((unsigned char)atoi(v), ret);
	else if(strcmp(ret, "OFF") == 0)
	  OFF = getValue((unsigned char)atoi(v), ret);
	else if(strcmp(ret, "C") == 0)
	  C = getValue((unsigned char)atoi(v), ret);
	else if (strcmp(ret, "B") ==  0)
	  B = getValue((unsigned char)atoi(v), ret);
      }
      else {
	perror("NULL while scanning input");
	exit(1);
      }
      /* Read the next one! */
      ret = strtok(NULL, ",");
    }
  }
}

/* Write output x to file */
void writeOutput(){
  static unsigned char count = 0;
  if (0 == count){
    fo = fopen(OFILE, "r");
    if (fo == NULL){
      perror(OFILE);
      exit(1);
    }
    ++count;
  }
  fprintf(fo, "%ld,%e\n", ++tick, x);
}

