#include<stdio.h>
#include<stdbool.h>

int main(void){
	int i,j,count=0;
	for(i=0;i<(1<<16);i++){
		bool A[16];
		for(j=0;j<16;j++)
		{
			A[j]=i&(1<<j);
		}
	bool thisbool=
		A[5]&&A[4]&&!A[3]&&A[2]&&A[8]&&A[7]&&!A[13]&&!A[14]&&A[15]&&A[6]&&A[12]&&(A[0]||A[1])&&A[11]
		&&!(A[10]&&A[9]);
	if(thisbool)
		count++;
	}
	printf("%d",count);
}
