#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdio>

#define MAXSIZE 1000000050

bool marks[ MAXSIZE ];

int main(int argc, char **argv){
	#ifdef FILEOUT
		freopen("sleve.out", "w", stdout);
	#endif
	clock_t start;
	if(argc > 1){
		int x, primes, k;
		for(int i = 1; i < argc; i++){
			start = clock();
			sscanf(argv[i], "%d", &x);
			primes = 0;
			k = 2;
			memset(marks, 0, x-1);
			while( k * k <= x ){
				primes++;
				for(int i =  k * k ; i <= x; i += k){
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
			
			std::cout << "x : " << x <<
			", time : " << ( (double) ( clock() - start ) / CLOCKS_PER_SEC ) << " seconds " <<
			", size : " << primes << std::endl;
		}
	}
	return 0;
}
