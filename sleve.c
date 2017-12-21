
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 1000000050

bool marks[ MAXSIZE ];

int main(int argc, char **argv){
	clock_t start;
	
	if(argc > 1){
		int x, primes, k;
		int i;
		for(i = 1; i < argc; i++){
			start = clock();
			sscanf(argv[i], "%d", &x);
			primes = 0;
			k = 2;
			memset(marks, 0, x-1);
			while( k * k <= x ){
				primes++;
				int i;
				for(i =  k * k ; i <= x; i += k){
					marks[i-2] = true;
				}
				do{
					k++;
				}
				while(marks[k-2]);
			}
			do{
				k++;
				if(!marks[k-2])
					primes++;
			}
			while(k <= x);
			
			printf("x : %d, time : %lf seconds, size : %d\n", x, (double) ( clock() - start ) / CLOCKS_PER_SEC , primes);
		}
	}
	return 0;
}

