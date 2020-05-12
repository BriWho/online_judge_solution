#include<stdio.h>
#include<stdlib.h>
#define MAXN 128

int main(){
	int i , j , k , m;
	int N;
	int rectangle[MAXN][MAXN];
	int t_arr[MAXN];

	while(scanf("%d" , &N) != EOF){
		for(i = 0 ; i < N ; i++)
			for(j = 0 ; j < N ; j++)
				scanf("%d" , &rectangle[i][j]);
	
		int max_sum = -127 * MAXN * MAXN;

		for(i = 0 ; i < N ; i++ ){
			for(j = i ; j < N ; j++){

				for(k = 0 ; k < N ; k++){
					t_arr[k] = 0;
					for(m = i ; m <= j ; m++)
						t_arr[k] += rectangle[m][k];
				}

				int t = t_arr[0];
				
				max_sum = t > max_sum? t : max_sum;
				for(k = 1; k < N; k++ ){
					t = (t_arr[k] + t > t_arr[k])? t_arr[k] + t: t_arr[k];
					max_sum = t > max_sum ?t : max_sum;
				}
			}
		}
		printf("%d\n" , max_sum);
	}
	return 0;
}