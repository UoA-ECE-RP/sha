#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include "wait.h"

/* The files are in csv format */
#define OFILE "file2.csv"
#define IFILE "file1.csv"

#define TRUE 1
#define FALSE 0

extern double x;

/* The step size */
double d = 0.2;

/* The events to read from file */
unsigned char VS, VSP;
double g;

/* The tick counter */
/* It is static to hide it inside this file */
static size_t tick = 0;

/* The output file pointer */
FILE *fo = NULL;

/* The input file pointer */
FILE *fi = NULL;
 unsigned int retTime;

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
  while (fgets(in,255,fi) == NULL){
	perror("No input");
	waitFor();
	//exit(1);
  }
  //else{
    char *ret = NULL, *v = NULL;
    ret = strtok(in, ",");
    if(ret == NULL){
      /* This means nothing found! */
      /* Set all events to false */
      perror("NULL strtok error");
      exit(1);
    }
    while(ret != NULL) {
      v = strtok(NULL, ",");
      if (v != NULL) {
		if (strcmp(ret, "VS") == 0)
		  VS = getValue((unsigned char)atoi(v), ret);
		else if(strcmp(ret, "VSP") == 0)
		  VSP = getValue((unsigned char)atoi(v), ret);
		else if(strcmp(ret, "g") == 0)
			g = atof(v);
		}
      else {
	perror("NULL while scanning input");
	exit(1);
      }
      /* Read the next one! */
      ret = strtok(NULL, ",");
    }
  //}
  fprintf(stdout, "%s:%d %s:%d %s:%f tick:%ld\n", "VS", VS,
	  "VSP", VSP, "g", g, tick);
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
    fprintf(fo, "x_apc,%f\n", x);
    fflush(fo);
    fclose(fo);
	
  tick++;
}

