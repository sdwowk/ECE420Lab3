#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "timer.h"


int main(int argc, char* argv[]){
  if(argc != 2){
    fprintf(stderr,"Wrong number of arguments. Need 2 got %d \n", argc);
    exit(1);
  }

  return 0;
}
