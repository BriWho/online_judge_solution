#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	int M[64][64];
	int n = 0, m , c = 0;
	int a , b;
	int i , j , k;

	while(scanf("%d" , &m)!=EOF){
		printf("matrix for city %d\n" , c);

		memset(M , 0 , sizeof(M));
		for(i = 0 ; i < m ; i++){
			scanf("%d%d" , &a , &b);
			n = a + 1 > n? a + 1 : n;
			n = b + 1 > n? b + 1 : n;

			M[a][b]++;
			for(j = 0 ; j < n ; j++){
				M[j][b] += M[j][a];
				M[a][j] += M[b][j];
				for(k = 0 ; k < n ; k++)
					M[j][k] += M[j][a] * M[b][k];
			}
		}
			

		for(i = 0 ; i < n ; i++){
			if(M[i][i] != 0){
				for(j = 0 ; j < n ; j++){
					for(k = 0 ; k < n ; k++){
						if(M[j][i] != 0 && M[i][k] != 0)
							M[j][k] = -1;
					}
				}
			}
		}
		for(i = 0 ; i < n ; i++)
			for(j = 0 ; j < n ; j++)
				printf("%d%c" ,M[i][j] ," \n"[j==n-1]);

		n = 0;
		c++;
	}

	return 0;
}
