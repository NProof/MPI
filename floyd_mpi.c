#include <stdio.h>
#include <math.h>
#include <string.h>
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
	// printf("* %d [ %d , %d ]\n", id, id/6, id%6);
	
	#define ROWS
	#define COLS
	
	for(int k=0; k<6; k++) {
		#ifdef ROWS
		if(id%6 == k){
			for(int j=0; j<6; j++) {
				if(j != k && j != id/6){
					// printf("%2d send to %2d when k is %d and *row*\n", id, (id/6)*6+j, k);
					MPI_Request request;
					MPI_Isend (&distances[id/6][id%6], 1, MPI_FLOAT, (id/6)*6+j, 2*k+1, MPI_COMM_WORLD, &request);
				}
			}
		}
		else{
			if(id/6 != k){
				MPI_Request request;
				MPI_Irecv(&distances[id/6][k], 1, MPI_FLOAT, (id/6)*6+k, 0, MPI_COMM_WORLD, &request);
			}
		}
		#endif
		// MPI_Barrier(MPI_COMM_WORLD);
		#ifdef COLS
		if(id/6 == k){
			for(int i=0; i<6; i++) {
				if(i != k && i != id%6){
					MPI_Request request;
					MPI_Isend (&distances[id/6][id%6], 1, MPI_FLOAT, i*6+(id%6), 2*k, MPI_COMM_WORLD, &request);
					// printf("%2d send to %2d when k is %d and *col*\n", id, i*6+(id%6), k);
				}
			}
		}
		else{
			if(id%6 != k){
				MPI_Request request;
				MPI_Irecv(&distances[k][id%6], 1, MPI_FLOAT, k*6+(id%6), 0, MPI_COMM_WORLD, &request);
				// printf("%2d re from %2d when k is %d and *col*\n", id, k*6+(id%6), k);
			}
		}
		#endif
		// MPI_Barrier(MPI_COMM_WORLD);
		if(!isnan(distances[id/6][k]) && !isnan(distances[k][id%6]))
			if(isnan(distances[id/6][id%6]) || distances[id/6][id%6] > distances[id/6][k]+distances[k][id%6]){
				distances[id/6][id%6] = distances[id/6][k]+distances[k][id%6];
				printf("id %d : %f when k %d\n", id, distances[id/6][id%6], k);
			}
		MPI_Barrier(MPI_COMM_WORLD);
		// for(int i=0; i<6; i++) {
			// for(int j=0; j<6; j++) {
				// if(isnan(distances[i][j]))
					// printf(" NaN");
				// else
					// printf(" %3.lf", distances[i][j]);
			// }
			// putchar('\n');
		// }
	}
	
	// printf("distance is %5.0f in %d\n", distances[id/6][id%6], id);
	
	MPI_Finalize();
	return 0;
}
