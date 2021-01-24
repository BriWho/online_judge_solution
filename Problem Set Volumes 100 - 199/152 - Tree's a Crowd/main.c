#include<stdio.h>
#include<string.h>

#define MAX_TREE 5000
#define square(X) ((X)*(X))

int tree[MAX_TREE][3];
int closestDist[MAX_TREE];

const int D2[10] = {1,4,9,16,25,36,49,64,81,100};

int main(){
	int i , j;
	int x , y , z;
	int n = 0;
	int A[10];
	memset(closestDist , -1 , sizeof(closestDist));
	memset(A , 0 , sizeof(A));
	while(scanf("%d%d%d" , &x , &y , &z) == 3){
		if(x == 0 && y == 0 && z == 0) break;
		tree[n][0] = x, tree[n][1] = y, tree[n][2] = z;

		int minD2 = 100;
		for(i = 0 ; i < n ; i++){
			int d2 = square(x - tree[i][0]) + square(y - tree[i][1]) + square(z - tree[i][2]);
			if(d2 < minD2) minD2 = d2;
			if(d2 < closestDist[i]) closestDist[i] = d2;
		}
		closestDist[n] = minD2;
		n++;
	}

	for(i = 0 ; i < n ; i++){
		for(j = 0 ; j < 10 ; j++)
			if(closestDist[i] < D2[j]){
				A[j]++;
				break;
			}
	}
	
	for(i = 0 ; i < 10 ; i++)
		printf("%4d" , A[i]);
	printf("\n");
	return 0;
}
