#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<assert.h>

/* The files are in csv format */
#define OFILEC "controlout.csv"
#define IFILEC "controlin.csv"

#define TRUE 1
#define FALSE 0

extern double x;

/* The step size */
double d = 0.2;

/* The events to read from file */
unsigned char add1_control, add2_control, remove1_control, remove2_control;

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
void readInputControler() {
  static unsigned char count = 0;
  /* The check here is very expensive! */
  if(0 == count) {
    fi = fopen(IFILEC, "r");
    if (fi == NULL){
      perror(IFILEC);
      exit(1);
    }
    ++count;
  }
  
  /* The format of input is 1 line/tick */
  /* for the events above the format is: */
  /*
    add1, add1_Value, add2, add2_value, remove1, remove1_value, remove2, remove2_value
    same for the controler
  */
  char in[256];
  if (fgets(in,255,fi) == NULL){
    add1_control = FALSE;
    add2_control = FALSE;
    remove1_control = FALSE;
    remove2_control = FALSE;
  }
  else{
    char *ret = NULL, *v = NULL;
    ret = strtok(in, ",");
    if(ret == NULL){
      /* This means nothing found! */
      /* Set all events to false */
      add1_control = FALSE;
      add2_control = FALSE;
      remove1_control = FALSE;
      remove2_control = FALSE;
    }
    while(ret != NULL) {
      v = strtok(NULL, ",");
      if (v != NULL) {
  if (strcmp(ret, "add1") == 0)
    add1_control = getValue((unsigned char)atoi(v), ret);
  else if(strcmp(ret, "add2") == 0)
    add2_control = getValue((unsigned char)atoi(v), ret);
  else if(strcmp(ret, "remove1") == 0)
    remove1_control = getValue((unsigned char)atoi(v), ret);
  else if (strcmp(ret, "remove2") ==  0)
    remove2_control = getValue((unsigned char)atoi(v), ret);
      }
      else {
  perror("NULL while scanning input");
  exit(1);
      }
      /* Read the next one! */
      ret = strtok(NULL, ",");
    }
  }
  fprintf(stdout, "%s:%d %s:%d %s:%d %s:%d tick:%ld\n", "add1_control", add1_control,
    "add2_control", add2_control, "remove1_control", remove1_control, "remove2_control", remove2_control, tick);
  fflush(stdout);
}

/* Write output x to file */
void writeOutputControl(){
  static unsigned char count = 0;
  if (0 == count){
    fo = fopen(OFILEC, "w");
    if (fo == NULL){
      perror(OFILEC);
      exit(1);
    }
    ++count;
  }
  fprintf(fo, "%ld,%f\n", ++tick, x);
}

