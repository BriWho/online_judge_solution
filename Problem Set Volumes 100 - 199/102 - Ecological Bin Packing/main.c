#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

enum { B , G , C };

int main(){
	int move[3][3];
	int bin[3][3];
	int i , j , k;
	int order[3];

	while(scanf("%d%d%d%d%d%d%d%d%d" ,
		&bin[0][0] , &bin[0][2] , &bin[0][1],
		&bin[1][0] , &bin[1][2] , &bin[1][1],
		&bin[2][0] , &bin[2][2] , &bin[2][1] ) != EOF)
	{
		for(i = 0 ; i< 3 ;i++){
			for(j = 0 ; j < 3;j++)
				move[i][j] = bin[(i+1)%3][j] + bin[(i+2)%3][j];
		}
		int min = INT_MAX;
		for(i = 0 ; i < 3 ; i++){
			for(j = 0 ; j < 3 ; j++){
				for(k = 0 ; k < 3 ; k++){
					if(i != j && j != k && k != i){
						int t = move[0][i] + move[1][j] + move[2][k];
						if(t < min){
							min = t;
							order[0] = i , order[1] = j , order[2] = k;
						}
					}
				}
			}
		}
		printf("%c%c%c %d\n" ,"BCG"[order[0]] , "BCG"[order[1]] , "BCG"[order[2]] , min);

	}

	return 0;
}
