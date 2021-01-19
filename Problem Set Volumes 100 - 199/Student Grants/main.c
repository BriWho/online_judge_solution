#include<stdio.h>
#include<string.h>

int main(){
	int student[50];
	int N , k;

	while(scanf("%d%d" , &N , &k) == 2){
		if(N == 0 && k == 0) break;

		memset(student , 0 , sizeof(student));
		int i , n;
		int outputStore = 0;
		int count = 0;


		for(i = 1 , n = 0; count < N; n=(n+1)%N){
			if(i > k) i = 1;
			while(student[n] >= 40)
				n = (n + 1)%N;

			if(outputStore == 0){
				outputStore += i;
				i++;
			}
			student[n] += outputStore;
			outputStore = 0;
			if(student[n] >= 40){
				outputStore += student[n] - 40;
				count ++;
				printf("%3d" , n+1);
			}

		}
		printf("\n");
	}
	return 0;
}