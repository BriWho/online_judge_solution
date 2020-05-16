#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	int n , i , j;
	int c_rank[32];
	int c_order[32];
	int s_rank[32];
	int s_order[32];

	int dp[32];

	scanf("%d" ,&n );
	for( i = 1 ; i <= n ; i++){
		scanf("%d" , &c_order[i]);
		c_rank[c_order[i]] = i;
	}
	while(scanf("%d" , &s_order[1]) != EOF){
		for( i = 2 ; i <= n ; i++)
			scanf("%d" , &s_order[i]);
		for(i = 1 ; i <= n ; i++)
			s_rank[s_order[i]] = i;

		memset( dp , 0, sizeof(dp));
		int max = 0;
		for(i = 1 ; i <= n ; i++){
			dp[i] ++;
			for(j = c_order[s_rank[i]] + 1 ; j <= n ; j++){
				int soj = s_order[c_rank[j]];
				dp[soj] = dp[i] > dp[soj] ? dp[i] : dp[soj];
			}
			if(max < dp[i])
				max = dp[i];
		}

		printf("%d\n" , max);
	}
	return 0;
}
