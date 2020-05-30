#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmp(const void* a , const void* b){
	return *(int*)a > *(int*)b ? 1 : -1;
}

void dfs(int n , int v[] , int idx , int stack[] , int orders[32][32]){
	int i , j;
	if(idx == n){
		for(i = 0 ; i < n ; i++)
			printf("%c" , stack[i]+ 'a');
		printf("\n");
		return;
	}
	for(i = 0 ; i < n ; i++){
		int isvalid = 1;
		int vi = v[i];
		for(j = 0 ; j < idx ; j++){
			if(orders[vi][stack[j]]){
				isvalid = 0;
				break;
			}
		}
		if(isvalid){
			orders[vi][vi] = 1;
			stack[idx] = vi;
			dfs(n , v , idx + 1 , stack , orders);
			orders[vi][vi] = 0;
		}
	}

}

int main(){
	int value[32], pairs[128];
	int stack[32], orders[32][32];
	int n = 0 , m = 0;
	int start = 0 , first = 1;
	char a , c;
	int i;

	while(scanf("%c%c" , &a , &c) == 2){
		if(start) pairs[m++] = a - 'a';
		else value[n++] = a - 'a';
		if(c == '\n'){
			if(start){
				if(!first) 
					printf("\n");
				m /= 2;
				memset(orders , 0 , sizeof(orders));
				qsort(value , n , sizeof(int) , cmp);
				for(i = 0 ; i < m ; i++)
					orders[pairs[i*2]][pairs[1+i*2]] = 1;

				dfs(n , value , 0 , stack , orders);
				n = m = 0;
				start = first = 0;
			}else
				start = 1;
		}
	}

	return 0;
}
