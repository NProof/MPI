#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define ROOTP 0

int main(int argc, char **argv){
	clock_t start = clock();
	
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
	
	for(int t=0; t<6; t++) {
		for(int k=0; k<6; k++) {
			if(!isnan(distances[id/6][k]) && !isnan(distances[k][id%6]))
				if(isnan(distances[id/6][id%6]) || distances[id/6][id%6] > distances[id/6][k]+distances[k][id%6]){
					distances[id/6][id%6] = distances[id/6][k]+distances[k][id%6];
				}
		}
		for(int j=0; j<6; j++) {
			if(j != id%6){
				MPI_Send (&distances[id/6][id%6], 1, MPI_FLOAT, (id/6)*6+j, (id/6)*6+j, MPI_COMM_WORLD);
				
				MPI_Recv(&distances[id/6][j], 1, MPI_FLOAT, (id/6)*6+j, id, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}
		for(int i=0; i<6; i++) {
			if(i != id/6){
				MPI_Send (&distances[id/6][id%6], 1, MPI_FLOAT, i*6+(id%6), i*6+(id%6), MPI_COMM_WORLD);
				
				MPI_Recv(&distances[i][id%6], 1, MPI_FLOAT, i*6+(id%6), MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}
	}
	
	if(id == ROOTP){
		float distance;
		MPI_Status status;
		for(int c=1; c<36; c++){
			if(c != ROOTP){
				MPI_Recv(&distance, 1, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				int idSend = status.MPI_SOURCE;
				distances[idSend/6][idSend%6] = distance;
			}
		}
		
		for(int i=0; i<6; i++) {
			for(int j=0; j<6; j++) {
					if(isnan(distances[i][j]))
						printf(" NaN");
					else
						printf(" %3.lf", distances[i][j]);
			}
			printf("\n");
		}
		printf("time : %f seconds\n", (float)( clock() - start ) / CLOCKS_PER_SEC);	
	}
	else{
		MPI_Send (&distances[id/6][id%6], 1, MPI_FLOAT, 0, id, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
	printf("time : %f seconds\n", (float)( clock() - start ) / CLOCKS_PER_SEC);	
	return 0;
}
