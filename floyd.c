#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
	clock_t start;
	
//	double  **distances = (double  **) malloc(5 * sizeof(double  *));
//	for(int i=0; i<5; i++) distances[i] = (unsigned int *) malloc(5 * sizeof(unsigned int));
	double  distances[6][6] = 
	{{0,2,5,NAN,NAN,NAN},
	{NAN,0,7,1,NAN,8},
	{NAN,NAN,0,4,NAN,NAN},
	{NAN,NAN,NAN,0,3,NAN},
	{NAN,NAN,2,NAN,0,3},
	{NAN,5,NAN,2,4,0}};
	
	printf("time : %lf seconds\n", (double) ( clock() - start ) / CLOCKS_PER_SEC);
	return 0;
}
