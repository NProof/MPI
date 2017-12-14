#include <iostream>
#include <vector>
#include <set>
#include<ctime>
#include <cstdio>

std::vector<int> findUnderPrimes(int n){
	std::vector<int> result ;
	std::set<int> marks;
	
	int k = 2;
	while( k * k <= n ){
		result.push_back(k);
		for(int i =  k * k ; i <= n; i += k){
			marks.insert(i);
		}
		do{
			k++;
		}
		while(marks.count(k));
	}
	while(k <= n){
		if(!marks.count(k))
			result.push_back(k);
		k++;
	}
	return result;
}

int main(int argc, char **argv){
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
			std::cout << "time : " << ( end - start ) / CLOCKS_PER_SEC << " seconds " << "size : " << underPrimes.size() << std::endl;
		}
	}
	return 0;
}

