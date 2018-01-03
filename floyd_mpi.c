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
	float * distance = &distances[id/6][id%6];
	// printf("* %d ] %3.lf\n", id, *distance);
	
	int  *store = (int  *) malloc(6 * 6 * sizeof(int));
	int **runed = (int **) malloc(6 * sizeof(int *)); 
	for(int i=0; i<6; i++)
		runed[i] = &store[i*6];
	
	for(int k=0; k<6; k++) {
		for(int i=0; i<6; i++)
			for(int j=0; j<6; j++)
				runed[i][j] = 0;
		
		distances[id/6][id%6] = *distance;
		
		if(id%6 == k){
			for(int j=0; j<6; j++) {
				if(j != k){
					// printf("%2d send to %2d when k is %d and *row*\n", id,(id/6)*6+j, k);
					MPI_Send (&distances[id/6][id%6], 1, MPI_FLOAT, (id/6)*6+j, 2*k+1, MPI_COMM_WORLD );
				}
			}
		}
		else{
			if(id/6 != k){
				printf("%2d re from %2d when k is %d and *row*\n", id, (id/6)*6+k, k);
				// MPI_Recv(&distances[id/6][k], 1, MPI_FLOAT, (id/6)*6+k, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				// MPI_Recv(&distances[k][id%6], 1, MPI_FLOAT, k*6+(id%6), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}
		/*
		if(id/6 == k){
			for(int i=0; i<6; i++) {
				if(i != k){
					printf("%2d send to %2d when k is %d and *col*\n", id, i*6+(id%6), k);
					MPI_Send (distance, 1, MPI_FLOAT, i*6+(id%6), 2*k, MPI_COMM_WORLD );
				}
			}
		}
		// for(int s=0; s<36; s++){
			if(id%6 != k && id/6 != k){
				// printf("(%2d) %2d , %2d when k is %d\n", id, id/6, id%6, k);
				MPI_Status status;
				// printf("%2d BEFORE %d when k is %d\n", id, (id/6)*6+k, k);
				// MPI_Recv(&distances[k][id%6], 1, MPI_FLOAT, k*6+(id%6), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				// MPI_Recv(&distances[id/6][k], 1, MPI_FLOAT, (id/6)*6+k, 0, MPI_COMM_WORLD, &status);
				printf("%2d AFTER \n", id);
			}
		// }
		
		// printf("%d (%d,%d) %d ] = %d\n", id, k, id/6, id%6, runed[(id/6)][(id%6)]);
		runed[id/6][id%6] = 1;
		// MPI_Bcast(&runed[id/6][id%6], 1, MPI_INT, 0, MPI_COMM_WORLD); worng!
		for(int s=0; s<36;s++)
			if(s!=id)
				MPI_Send (&runed[id/6][id%6], 1, MPI_INT, s, 36, MPI_COMM_WORLD );
		MPI_Status status;
		for(int s=0; s<36;s++)
			if(s!=id)
				MPI_Recv(&runed[s/6][s%6], 1, MPI_INT, s, 36, MPI_COMM_WORLD, &status );
		
		printf("id :%d\n", id);
		for(int i=0; i<5; i++){
			for(int j=0; j<5; j++)
				printf("%d ,", runed[i][j]);
			putchar('\n');
		}
		*/
		// printf("%d distance : %f \n", id, *distance);
		
	}
	
	MPI_Finalize();
	return 0;
}
