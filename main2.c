#include<stdio.h>
#include<stdlib.h>

int gcd(int a , int b){
	int t;
	while(b > 0){
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

int main(){
	int a  , b , i;
	int N;
	int* isused;
	
	while(scanf("%d" , &N)!=EOF){
		int prime_cnt = 0;
		int triple_cnt = 0;
		isused = calloc( N + 1, sizeof(int));
		
		for(b = 1 ; b * b < N ; b++ ){
			for(a = b+1 ; a * a + b * b <= N ; a += 2){
				if(gcd(a , b) > 1) continue;
				int x = a * a - b * b;
				int y = 2 * a * b;
				int z = a * a + b * b;
				if(y >= N) continue;
				triple_cnt++;
				
				for(i = 1 ; i * x <= N && i * y <= N && i * z<=N ; i++ )
					isused[x * i] = isused[y * i] = isused[z * i] = 1;
			}
		}
		for(i = 1 ; i <= N ; i++)
			if(!isused[i])
				prime_cnt++;
		printf("%d %d\n" , triple_cnt , prime_cnt);
		free(isused);
	}

	return 0;
}
