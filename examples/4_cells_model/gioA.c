#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/* The files are in csv format */
#define OFILE "file5.csv"
#define IFILE1 "file2.csv"
#define PFILE "NPCx.csv"

#define TRUE 1
#define FALSE 0

double x_apc, x_pre; //inputs continuous

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
FILE *fp = NULL;

 unsigned int retTime;
 void waitFor (unsigned int secs) {
    retTime = time(0) + secs;     // Get finishing time.
    for (int i_timer=0 ; i_timer<10000 ; i_timer ++){
      for (int j_timer=0 ; j_timer<10000 ; j_timer ++) {}}   // Loop until it arrives.
 }

static inline unsigned char getValue(unsigned char t, char* e){
  assert(t == TRUE || t == FALSE);
  return t;
}

/* Read input x from file */
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
    if (strcmp(ret, "x_apc") == 0){
      x_apc = atof(v);
    }
      }
      else {
    perror("NULL while scanning input");
    exit(1);
      }

      /* Read the next one! */
      ret = strtok(NULL, ",");
    }

  fprintf(stdout, "%s:%f tick:%ld\n", "x_apc", x_apc, tick);
  fflush(stdout);

}
  
  
 /* Read previous state */
void readPreviousState() {
  static unsigned char count = 0;
  /* The check here is very expensive! */
  if(0 == count) {
    fp = fopen(PFILE, "r");
    if (fp == NULL){
      perror(PFILE);
      exit(1);
    }
    ++count;
  }
  
  /* The format of input is 1 line/tick */
  /* for the events above the format is: */
  /*
    ON, ON_Value, C, C_Value, B, B_Value, OFF, OFF_Value
  */
  char pre[256];
  while (fgets(pre,255,fp) == NULL ){
  perror("No input");
  waitFor(2);
  }

  char *retp = NULL, *vp = NULL;
  retp = strtok(pre, ",");
  if(retp == NULL){
    /* This means nothing found! */
    perror("NULL strtok error");
    exit(1);
  }
  while(retp != NULL) {
    vp = strtok(NULL, ",");
    if (vp != NULL) {
      if (strcmp(retp, "x1") == 0){
      x_pre = atof(vp);
      }
    }
    else {
      perror("NULL while scanning input");
      exit(1);
      }
      /* Read the next one! */
      retp = strtok(NULL, ",");
    }
  
  fprintf(stdout, "%s:%f tick:%ld\n","x_pre", x_pre, tick);
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
	fprintf(fo, "VS,0,VSP,0,g,%f\n",v_aggregate);
	fflush(fo);
	fclose(fo);
	
	tick++;
}

