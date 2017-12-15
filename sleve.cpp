#include <iostream>
#include <vector>
#include <bitset>
#include <ctime>
#include <cstdio>

#define MAXSIZE 500000005

std::bitset< MAXSIZE > marks;
	
void findUnderPrimes(int n){
	marks.reset();
	int k = 2;
	while( k * k <= n ){
		for(int i =  k * k ; i <= n; i += k){
			marks.set(i);
		}
		do{
			k++;
		}
		while(marks.test(k));
	}
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
			findUnderPrimes(x);
//			for (std::vector<int>::iterator it = underPrimes.begin(); it != underPrimes.end(); ++it)
//				std::cout << ' ' << *it;
//			std::cout << '\n';
			end = clock();
			std::cout << "x : " << x <<
			", time : " << ( (double) ( end - start ) / CLOCKS_PER_SEC ) << " seconds " <<
			", size : " << x - marks.count() - 1 << std::endl;
		}
	}
	return 0;
}

