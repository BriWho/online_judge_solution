#include<stdio.h>
#include<string.h>

const int currency[11] = {5,10,20,50,100,200,500,1000,2000,5000,10000};

int main(){
	int i , j;
	int c , d;
	unsigned long long int dp[6001];

	memset(dp , 0 , sizeof(dp));
	for(i = 0 ; i < 11 ; i++){
		int b = currency[i]/5;
		dp[b]++;
		for(j = b+1; j <= 6001 ; j++)
			dp[j] = dp[j-b] + dp[j];
	}

	while(scanf("%d.%d" , &d , &c) != EOF){
		if(d == 0 && c == 0) break;
		printf("%3d.%02d%17llu\n" , d , c , dp[(d * 100 + c)/5]);
	}
	return 0;
}
