#include <iostream>
#include <vector>
#include <bitset>
#include <ctime>
#include <cstdio>

std::bitset<500000005> marks;
std::vector<int> result ;
	
std::vector<int> findUnderPrimes(int n){
	result.clear();
	marks.reset();
	int k = 2;
	while( k * k <= n ){
		result.push_back(k);
		for(int i =  k * k ; i <= n; i += k){
			marks.set(i);
		}
		do{
			k++;
		}
		while(marks.test(k));
	}
	while(k <= n){
		if(!marks.test(k))
			result.push_back(k);
		k++;
	}
	return result;
}

int main(int argc, char **argv){
	#ifdef FILEOUT
		freopen("sleve2.out", "w", stdout);
	#endif
	clock_t start, end;
	if(argc > 1){
		int x ;
		for(int i = 1; i < argc; i++){
			start = clock();
			sscanf(argv[i], "%d", &x);
			std::vector<int> underPrimes = findUnderPrimes(x);
//			for (std::vector<int>::iterator it = underPrimes.begin(); it != underPrimes.end(); ++it)
//				std::cout << ' ' << *it;
//			std::cout << '\n';
			end = clock();
			std::cout << "x : " << x <<
			", time : " << ( (double) ( end - start ) / CLOCKS_PER_SEC ) << " seconds " <<
			", size : " << underPrimes.size() << std::endl;
		}
	}
	return 0;
}

