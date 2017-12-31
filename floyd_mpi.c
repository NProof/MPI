#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	
	float  distances[6][6] = 
	{{0,2,5,NAN,NAN,NAN},
	{NAN,0,7,1,NAN,8},
	{NAN,NAN,0,4,NAN,NAN},
	{NAN,NAN,NAN,0,3,NAN},
	{NAN,NAN,2,NAN,0,3},
	{NAN,5,NAN,2,4,0}};
	
	int id;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	float * distance = &distances[id/6][id%6];
	// printf("* %d ] %3.lf\n", id, *distance);
	for(int k=0; k<6; k++) {
		if(id%6 == k){
			for(int j=0; j<6; j++) {
				if(j != k){
					printf("%2d send to %2d when k is %d\n", id,(id/6)*6+j, k);
					MPI_Send (distance, 1, MPI_FLOAT, (id/6)*6+j, 2*k+1, MPI_COMM_WORLD );
				}
			}
		}
		if(id/6 == k){
			for(int i=0; i<6; i++) {
				if(i != k){
					// printf("%2d send to %2d when k is %d\n", id, i*6+(id%6), k);
					MPI_Send (distance, 1, MPI_FLOAT, i*6+(id%6), 2*k, MPI_COMM_WORLD );
				}
			}
		}
	}
	
	MPI_Finalize();
	return 0;
}
