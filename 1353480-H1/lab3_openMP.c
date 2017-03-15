#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "timer.h"
#include "Lab3IO.h"

int n;
int thread_count;

double** U;

void gaussian_elimination();
void jordan_elimination();

int main(int argc, char* argv[]){
  if(argc != 2){
    fprintf(stderr,"Wrong number of arguments. Need 2 got %d \n", argc);
    exit(1);
  }

  thread_count = strtol(argv[1], NULL, 10);

  double time_start, time_end;

  Lab3LoadInput(&U, &n);

  GET_TIME(time_start);

// #pragma omp parallel num_threads(thread_count)
//   {
  gaussian_elimination();
  jordan_elimination();
//  }

  int i;
  double *result = CreateVec(n);
  #pragma omp parallel for num_threads(thread_count) \
  private(i)
  for(i = 0; i < n; i++){
  	result[i] = U[i][n]/U[i][i]; 
  }

  GET_TIME(time_end);
  Lab3SaveOutput(result, n, (time_end - time_start));

  //PrintVec(result, n);

  DestroyMat(U, n);
  DestroyVec(result);

  return 0;
}


void gaussian_elimination(){
	int i, k, j, l, switchIndex;
	double  tempMax, alpha;
	double* tempRow;

	for(k=0 ; k < n-1; k++){
		tempMax = U[k][k] * U[k][k];
	#pragma omp parallel for reduction(max:tempMax)
		for(l = k; l < n; l++){

			if((U[k][l] * U[k][l]) > tempMax){
				tempMax = U[k][l] * U[k][l];
				switchIndex = l;
			}
		}

	// Swap row pointers instead of rows in memory
		if(k != switchIndex){		
			tempRow = U[k];
			U[k] = U[switchIndex];
			U[switchIndex] = tempRow;
		}

#pragma omp parallel for num_threads(thread_count) \
		private(alpha, i , j) \
		shared(k, U)
		for(i = k+1; i < n; i++){
			alpha = U[i][k]/U[k][k];
//#pragma omp for
			for( j = k; j < n+1; j++){
				U[i][j] = U[i][j] - alpha*U[k][j];
			}
		}
	}
}

void jordan_elimination() {
	int k, i;
	double temp;

	for (k = n-1; k > 0; k--){
#pragma omp parallel for num_threads(thread_count) \
		private(temp, i) \
		shared(U, k)
	
		for(i = k-1; i >= 0; i--){
			temp = U[i][k]/U[k][k];
			U[i][k] = U[i][k] - temp * U[k][k];  
			U[i][n] = U[i][n] - temp * U[k][n];

		}
		
	}
}