#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void push(int stack[] , int* cnt ,int e){
	stack[(*cnt)++] = e;
}
int pop(int stack[] , int* cnt ){
	return stack[--(*cnt)];
}

int main()
{
	int n , i , j;
	char cmd[2][8];
	int a ,b;

	scanf("%d" , &n);
	int stack[n+1][n];
	int cnt[n+1];
	int pos[n];

	for(i = 0 ; i < n;i++ ){
		stack[i][0] = pos[i] = i;
		cnt[i] = 1;
	}
	cnt[n] = 0;

	while(scanf("%s" , cmd[0]) != EOF){
		if(strcmp(cmd[0] ,  "quit") == 0){
			for(i = 0 ; i < n ; i++){
				printf("%d:", i);
				for(j = 0 ; j < cnt[i] ; j++)
					printf(" %d" , stack[i][j]);
				printf("\n");
			}
			break;
		}
		scanf("%d%s%d" , &a , cmd[1] ,&b );
		if(pos[a] == pos[b]) continue;
		int move = strcmp(cmd[0] , "move") == 0? 1: 0;
		int pile = strcmp(cmd[0] , "pile") == 0? 1: 0;
		int onto = strcmp(cmd[1] , "onto") == 0? 1: 0;
		int over = strcmp(cmd[1] , "over") == 0? 1: 0;

		if(onto && (move || pile)){
			while(cnt[pos[b]] > 0){
				int t = pop(stack[pos[b]] , &cnt[pos[b]]);
				if(t == b){
					push(stack[pos[b]] , &cnt[pos[b]] , b);
					break;
				}
				push(stack[t] ,&cnt[t] , t );
				pos[t] = t;
			}
		}

		if(move && (over || onto)){
			while(cnt[pos[a]] > 0){
				int t = pop(stack[pos[a]] , &cnt[pos[a]]);
				if(t == a){
					push(stack[pos[b]] , &cnt[pos[b]] , a);
					break;
				}
				push(stack[t] ,&cnt[t] , t );
				pos[t] = t;
			}
			pos[a] = pos[b];
		}
		if(pile  && (over || onto)){
			while(cnt[pos[a]] > 0){
				int t = pop(stack[pos[a]] , &cnt[pos[a]]);
				push(stack[n] , &cnt[n] , t);
				pos[t] = pos[b];
				if(t == a)
					break;
			}
			while(cnt[n] > 0){
				push(stack[pos[b]] ,&cnt[pos[b]] , pop(stack[n] , &cnt[n]));
			}
		}
	}
	return 0;

}