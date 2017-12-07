#include<stdio.h>
#include<stdbool.h>
#include<mpi.h>
#include<time.h>

int main(int argc, char **argv){
	
	int k, id, p, global_solutions, solution, check_circut(int, int);
	clock_t start, end;
	
	start = clock();
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	if(id == 0)
		printf(" a b c d e f g h i j k l m n o p\n");
	
	int i,j;
	for(i=id;i<(1<<16);i+=p){
		bool A[16];
		for(j=0;j<16;j++)
		{
			A[j]=i&(1<<j);
		}
		bool thisbool=
			A[5]&&A[4]&&!A[3]&&A[2]&&A[8]&&A[7]&&!A[13]&&!A[14]&&A[15]&&A[6]&&A[12]&&(A[0]||A[1])&&A[11]
			&&!(A[10]&&A[9]);
		if(thisbool){
			solution++;
			for(j=0;j<16;j++)
			{
				printf(" %d", ((i>>j)&1));
			}
			printf("\n");
		}
	}
	
	MPI_Reduce(&solution, &global_solutions, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(id == 0)
		printf("There are %d different soulutions\n", global_solutions);
	
	MPI_Finalize();
	
	end = clock();
	double diff = end - start;
	printf(" %f  sec\n", diff / CLOCKS_PER_SEC );
	
	return 0;
}
