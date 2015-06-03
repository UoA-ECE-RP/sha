#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<time.h>

#define OFILE "NPCx.csv"
#define IFILE1 "file7.csv"
#define IFILE2 "file8.csv"
#define IFILE3 "result.csv"

#define True 1
#define False 0

double x1, x2, x; //inputs continuous


/* The tick counter */
/* It is static to hide it inside this file */
static size_t tick = 0;

/* The output file pointer */
FILE *fo = NULL;

/* The input file pointer */
FILE *fi1 = NULL;
FILE *fi2 = NULL;
FILE *fi3 = NULL;


 unsigned int retTime;
 void waitFor (unsigned int secs) {
    retTime = time(0) + secs;     // Get finishing time.
    while (time(0) < retTime);    // Loop until it arrives.
}

/* Read input x1, x2, x from files */
void readInput() {
  static unsigned char count = 0;
  /* The check here is very expensive! */
  // Initialisation
  if(0 == count) {
    fi1 = fopen(IFILE1, "r");
    if (fi1 == NULL){
      perror(IFILE1);
      exit(1);
    }
    fi2 = fopen(IFILE2, "r");
    if (fi2 == NULL){
      perror(IFILE2);
      exit(1);
    }
    fi3 = fopen(IFILE3, "r");
    if (fi3 == NULL){
      perror(IFILE3);
    }
    ++count;
  }
  
  /* Reading x1, x2, x */
  

  char in1[256], in2[256], in3[256];

    while (fgets(in1,255,fi1) == NULL ){
      perror("No input 1");
      waitFor(2);
    }
    while (fgets(in2,255,fi2) == NULL ){
      perror("No input 2");
      waitFor(2);
    }
    while (fgets(in3,255,fi3) == NULL ){
      perror("No input 3");
      waitFor(2);
    }
  
    char *ret1 = NULL, *v1 = NULL;
    ret1 = strtok(in1, ",");
    if(ret1 == NULL){
      /* This means nothing found! */
      /* Set all events to false */
      exit(1);
    }
    while(ret1 != NULL) {
      v1 = strtok(NULL, ",");
      if (v1 != NULL) {
        if (strcmp(ret1, "x1") == 0){
          x1 = atof(v1);
    }
      }
      else {
        perror("NULL while scanning input 1");
        exit(1);
      }

      /* Read the next one! */
      ret1 = strtok(NULL, ",");
    }
  
    // input 2
    char *ret2 = NULL, *v2 = NULL;
    ret2 = strtok(in2, ",");
    if(ret2 == NULL){
      /* This means nothing found! */
      exit(1);
    }
    while(ret2 != NULL) {
      v2 = strtok(NULL, ",");
      if (v2 != NULL) {
        if (strcmp(ret2, "x2") == 0){
          x2 = atof(v2);
        }
      }
      else {
        perror("NULL while scanning input 2");
        exit(1);
      }

      /* Read the next one! */
      ret2 = strtok(NULL, ",");
    }

    // input 3
    char *ret3 = NULL, *v3 = NULL;
    ret3 = strtok(in3, ",");
    if(ret3 == NULL){
      /* This means nothing found! */
      exit(1);
    }
    while(ret3 != NULL) {
      v3 = strtok(NULL, ",");
      if (v3 != NULL) {
        if (strcmp(ret3, "x") == 0){
          x = atof(v3);
        }
      }
      else {
        perror("NULL while scanning input 3");
        exit(1);
      }

      /* Read the next one! */
      ret3 = strtok(NULL, ",");
    }
  
  
  
  
  fprintf(stdout, "%s:%f %s:%f %s:%f tick:%ld\n", "x1", x1,
    "x2", x2, "x", x, tick);
  fflush(stdout);
}

/* Write output  to file */
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
  fprintf(fo, "%s,%f,%s,%f,%s,%f\n", "x1_pre", x1, "x2_pre", x2, "x_pre", x);
  fflush(fo);
  fclose(fo);
    tick++;
 
}

int main(){
  while(True) {
    readInput();
    
    writeOutput();
  }
  return 0;

}

