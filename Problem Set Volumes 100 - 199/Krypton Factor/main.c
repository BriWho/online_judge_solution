#include <stdio.h>
#include <string.h>
int N;

int isEasy(char stack[] , int m){
	int i;
	for(i = 1 ; i <= m/2 ; i++){
		char* t = stack + m - i;
		if(memcmp(t , t - i , i) == 0)
			return 1;
	}
	return 0;
}

int DFS(char stack[] , int idx , int n , int L ){
	int i;
	if(n == N){
		for(i = 0 ; i < idx ; i++){
			printf("%c" , stack[i]);
			if(i == idx - 1 || i % 64 == 63){
				puts(""); 
				continue;
			}
			if(i % 4 == 3) 
				printf(" ");
		}

		printf("%d\n" , idx);
		return 1;
	}

	for(i = 0 ; i < L ; i++){
		stack[idx] = 'A' + i;
		if(isEasy(stack , idx + 1))
			continue;

		N++;
		if(DFS(stack , idx + 1 , n , L))
			return 1;
	}

	return 0;
}

int main(){
	int n , L;
	char stack[128];

	while(scanf("%d%d" , &n , &L) != EOF){
		if(n == 0 && L == 0) break;
		N = 0;
		DFS(stack , 0 , n , L);
	}
	return 0;
}