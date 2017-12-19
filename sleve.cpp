#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdio>

#define MAXSIZE 1000000050

bool marks[ MAXSIZE ];
	
int findUnderPrimes(int n){
	memset(marks, 0, n-1);
	int primes = 0, k = 2;
	while( k * k <= n ){
		primes++;
		for(int i =  k * k ; i <= n; i += k){
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
	while(k <= n);
	return primes;
}

int main(int argc, char **argv){
	#ifdef FILEOUT
		freopen("sleve.out", "w", stdout);
	#endif
	clock_t start;
	if(argc > 1){
		int x ;
		for(int i = 1; i < argc; i++){
			start = clock();
			sscanf(argv[i], "%d", &x);
			int primes = findUnderPrimes(x);
			std::cout << "x : " << x <<
			", time : " << ( (double) ( clock() - start ) / CLOCKS_PER_SEC ) << " seconds " <<
			", size : " << primes << std::endl;
		}
	}
	return 0;
}

