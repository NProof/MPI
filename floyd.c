#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
	clock_t start = clock();
	
//	double  **distances = (double  **) malloc(5 * sizeof(double  *));
//	for(int i=0; i<5; i++) distances[i] = (unsigned int *) malloc(5 * sizeof(unsigned int));

	double  distances[6][6] = 
	{{0,2,5,NAN,NAN,NAN},
	{NAN,0,7,1,NAN,8},
	{NAN,NAN,0,4,NAN,NAN},
	{NAN,NAN,NAN,0,3,NAN},
	{NAN,NAN,2,NAN,0,3},
	{NAN,5,NAN,2,4,0}};

	for(int k=0; k<6; k++) {
		for(int i=0; i<6; i++) {
			for(int j=0; j<6; j++) {
				distances[i][j] = fmin(distances[i][j],distances[i][k]+distances[k][j]);
			}
		}
	}
	
	for(int i=0; i<6; i++) {
		for(int j=0; j<6; j++) {
			if(isnan(distances[i][j]))
				printf(" NaN");
			else
				printf(" %3.lf", distances[i][j]);
		}
		putchar('\n');
	}
	
	printf("time : %f seconds\n", (float)( clock() - start ) / CLOCKS_PER_SEC);
	return 0;
}
