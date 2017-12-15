#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
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
	clock_t start, end;
	if(argc > 1){
		int x ;
		for(int i = 1; i < argc; i++){
			start = clock();
			sscanf(argv[i], "%d", &x);
			int primes = findUnderPrimes(x);
//			for (std::vector<int>::iterator it = underPrimes.begin(); it != underPrimes.end(); ++it)
//				std::cout << ' ' << *it;
//			std::cout << '\n';
			end = clock();
			std::cout << "x : " << x <<
			", time : " << ( (double) ( end - start ) / CLOCKS_PER_SEC ) << " seconds " <<
			", size : " << primes << std::endl;
		}
	}
	return 0;
}

