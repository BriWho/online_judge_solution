#include<stdio.h>
#include<string.h>


int main(){
	int N;
	int i , j;
	int factor[128];

	while(scanf("%d" , &N) !=EOF){
		if(N == 0) break;
		for(i = 0 ; i <= N ; i++)
			factor[i] = i;
		printf("%3d! =" , N);
		int primeNum = 0;
		for(i = 2 ; i <= N ; i++){
			if(factor[i] == 1) continue;
			if(primeNum == 15){
				printf("\n      ");
				primeNum = 0;
			}
			int cnt = 0;
			for(j = i ; j <= N ; j++){
				while(factor[j] % i == 0)
					cnt++ , factor[j] /= i;
			}
			printf("%3d" , cnt);
			primeNum++;
		}
		puts("");
	}
	return 0;
}