#include<stdio.h>

int min(int a , int b){
	return a < b? a : b;
}

int main(){
	int dp[1500];
	int i;

	int mul[3] = { 1 ,1 ,1};
	int p[3] = { 0, 0 ,0};
	const int n = 1500;

	for(i = 0 ; i < n ; i++){
		int min_mul = min(mul[0] , min(mul[1] , mul[2]));
		dp[i] = min_mul;

		if(mul[0] == min_mul)
			mul[0] = 2 * dp[p[0]++];
		if(mul[1] == min_mul)
			mul[1] = 3 * dp[p[1]++];
		if(mul[2] == min_mul)
			mul[2] = 5 * dp[p[2]++];
	}

	printf("The 1500'th ugly number is %d.\n" , dp[n-1] );

	return 0;
}
