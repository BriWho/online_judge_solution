#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

#define MAXN 16
#define MAXK 32
int isfit(int n, int* D , int* E){
	int i;
	for(i = 0 ; i< n ; i++){
		if(D[i] >= E[i])
			return 0;
	}
	return 1;
}

int cmp1(const void* a , const void* b){
	int* A = (int*)a , *B = (int*)b;
	if(*A > *B) return 1;
	else if(*A < *B) return -1;
	else return 0;
}
int cmp2(const void* a , const void* b){
	int* A = *(int**)a , *B = *(int**)b;
	if(A[0] > B[0]) return 1;
	else if(A[0] < B[0]) return -1;
	else return 0;
}

int main(){
	int k , n;
	int i , j;
	int boxes[MAXK][MAXN];
	int* bp[MAXK];
	int max_nest[MAXK];
	int nxt[MAXK];

	while(scanf("%d%d" , &k , &n) !=EOF){
		for(i = 0 ; i < k ; i++){
			for(j = 0 ; j < n ; j++)
				scanf("%d" ,&boxes[i][j]);
			bp[i] = boxes[i];
		}

		for(i = 0 ; i < k ; i++)
			qsort(boxes[i] , n , sizeof(int) , cmp1);
		qsort(bp , k , sizeof(int*) , cmp2 );

		memset( nxt , -1 , sizeof(int) * n);

		for(i = k-1; i >= 0 ; i--){
			int max = 0;
			for(j = i + 1; j < k ; j++){
				if(isfit(n , bp[i]  , bp[j])){
					if(max_nest[j] > max){
						max = max_nest[j];
						nxt[i] = j;
					}
				}
			}
			max_nest[i] = max + 1;
		}
		int max = 0;
		int root = 0;
		for(i = 0 ; i < k ; i++ ){
			if(max < max_nest[i]){
				max = max_nest[i];
				root = i;
			}
		}
		printf("%d\n", max );
		for(i = 0 ; i < max; i++){
			printf("%d%c" , (bp[root] - boxes[0])/MAXN + 1, " \n"[i == max-1]);
			root = nxt[root];
		}
	}
	return 0;
}
