#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAXR 16 
#define MAXC 128

int lexico(const void* a , const void* b){
	return *(int*)a > *(int*)b? 1:-1;
}

int main(){
	int weight[MAXR][MAXC];
	int dp[MAXR][MAXC];
	int path[MAXR][MAXC];
	int n , m;
	int i , j , k;

	while(scanf("%d%d" , &n , &m) != EOF){
		for(i = 0 ; i < n ; i++){
			for(j = 0 ; j < m ; j++){
				scanf("%d" , &weight[i][j]);
				dp[i][j] = j == m-1?weight[i][j]:INT_MAX;
			}
		}

		for(i = m-2 ; i >= 0; i--){
			for(j = 0 ; j < n ; j++){
				int dir[3] = {
					(j + n - 1) % n ,
					(j + 1) % n , 
					j 
				};

				qsort(dir , 3 , sizeof(int) , lexico);

				for(k = 0 ; k < 3 ; k++){
					if(weight[j][i] + dp[dir[k]][i+1] < dp[j][i]){
						dp[j][i] = weight[j][i] + dp[dir[k]][i+1];
						path[j][i] = dir[k];
					}
				}
			}
		}

		int min = INT_MAX , start = 0;
		for(i = 0 ; i < n ; i++){
			if(min > dp[i][0]){
				min = dp[i][0];
				start = i;
			}
		}

		int current = start;
		for(i = 0 ; i < m ; i++){
			printf("%d%c" , current + 1, " \n"[m - 1== i]);
			current = path[current][i];
		}
		printf("%d\n" , min );
	}

	return 0;
}