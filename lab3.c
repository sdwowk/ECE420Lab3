#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "timer.h"
#include "Lab3IO.h"

int n;

double** U;

void gaussian_elimination();
void jordan_elimination();

int main(int argc, char* argv[]){
  if(argc != 2){
    fprintf(stderr,"Wrong number of arguments. Need 2 got %d \n", argc);
    exit(1);
  }

  //U = CreateMat(n, n+1);

  double time_start, time_end;

  Lab3LoadInput(&U, &n);
  
  //PrintMat(U,n,n+1);

  GET_TIME(time_start);
  gaussian_elimination();
  jordan_elimination();
  int i;
  double *result = CreateVec(n);
  for(i = 0; i < n; i++){
  	result[i] = U[i][n]; 
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


	for(k=0 ; k < n; k++){
		tempMax = U[k][k];
		for(l = k; l < n; l++){

			if(U[k][l] > tempMax){
				tempMax = U[k][l];
				switchIndex = l;
			}
		}

		tempRow = U[k];
		U[k] = U[switchIndex];
		U[switchIndex] = tempRow;
		

		for(i = k+1; i < n; i++){
			alpha = U[i][k]/U[k][k];
			for( j = k; j < n; j++){
				U[i][j] = U[i][j] - alpha*U[k][j];
			}
		}
	}
	//free(tempRow);
}

void jordan_elimination() {
	int k, i;
	for (k = n-1; k > 1; k--){

		for(i = 0; i < k-1; i++){
			U[i][n] = U[i][n] - U[i][k]/(U[k][k] * U[k][n]);
			U[i][k] = 0;
		}
	}

}