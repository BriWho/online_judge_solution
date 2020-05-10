#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int height[100000];

int main(){
	int i;
	int L , H , R;
	int most_right = 0;
	memset( height , 0 , sizeof(int) * 100000);
	while(scanf("%d%d%d" , &L , &H , &R) != EOF){
		if(most_right < R)
			most_right = R;
		for(i = L ; i < R ; i++)
			height[i] = H > height[i]? H : height[i];
	}

	height[0] = 0;
	for( i = 1 ; i <= most_right; i++){
		if(height[i - 1] != height[i]){
			printf("%d %d%c" , i , height[i] , " \n"[i == most_right] );
		}
	}
	return 0;
}
