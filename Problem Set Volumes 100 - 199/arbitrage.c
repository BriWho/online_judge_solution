#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	int n ;
	int i , j , k;
	double table[32][32],a[32][32];
	int records[32][32];
	int ans[32];
	while(	scanf("%d" , &n)  !=EOF){
		for(i = 0 ; i< n ; i++){
			for(j = 0 ; j < n ;j++){
				if(i == j){
					table[i][j] = 1;
					continue;
				}
				scanf("%lf" ,&table[i][j]);
			}
		}
		int r= 0 , isexist = 0;
		int min_len = 32;
		for(i = 0 ; i < n ; i++){
			memset(a[0] , 0 ,sizeof(a[0]));
			a[0][i] = 1;
			for(r = 1 ; r <= n ; r++ ){
				for(j = 0 ; j < n ; j++){
					double max = 0;
					for(k = 0 ; k < n ;k++){
 						if(j == k) continue;
 						if(max < a[r-1][k] * table[k][j]){
 							max = a[r-1][k] * table[k][j];
 							records[r][j] = k;
 						}
					}
					a[r][j] = max;
				}
				if(a[r][i] >= 1.01 && min_len > r){
					int t = i;
					for(j = r ; j >= 0 ; j--){
						ans[j] = t + 1;
						t = records[j][t];
					}
					isexist= 1 , min_len = r;
					break;	
				}
			}
		}
		if(isexist){
			for(i = 0 ; i<= min_len ; i++)
				printf("%d%c" ,ans[i], " \n"[i==min_len]);
		}else{
			printf("no arbitrage sequence exists\n");
		}
	}

	return 0;
}