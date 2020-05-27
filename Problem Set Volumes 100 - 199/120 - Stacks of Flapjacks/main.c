#include<stdio.h>
#include<stdlib.h>

struct stack{
	int e[100] , n;
};

void init(struct stack* s){
	s -> n = 0;
}
int isempty(struct stack* s){
	return s -> n == 0;
}

int pop(struct stack* s){
	if(isempty(s)) return -1;
	return s ->  e[--s -> n];
}

int push(struct stack* s , int e){
	return s -> e[s -> n++] = e;
}

int max_idx(struct stack* s , int pos){
	int i , max = -1 , idx = -1;
	for(i = pos ; i < s -> n ; i++)
		if(s -> e[i] > max)
			max = s -> e[i], idx = i;
	return idx;
}

void flip(struct stack* s ,int pos ){
	int i , m = s -> n - pos;
	int queue[100];
	int tail = 0 , head = 0;
	for(i = 0 ; i < m ; i++)
		queue[head++] = pop(s);
	for(i = 0 ; i < m ; i++)
		push(s , queue[tail++]);
}

void printstack(struct stack s){
	int i;
	for(i = 0 ; i < s.n ; i++)
		printf("%d%c" , s.e[i] , " \n"[i == s.n-1]);
}

struct stack sort(struct stack s){
	struct stack res;
	init(&res);
	int i;
	for(i = 0 ; i < s.n ; i++){
		int idx = max_idx(&s , i);
		if(i == idx) continue;
		if(idx != s.n -1){
			flip(&s , idx);
			push(&res , idx + 1);
		}
		flip(&s , i);
		push(&res , i + 1);
	}
	return res;
}

int main(){
	struct stack s , r;
	int e , c;
	init(&s);

	while(scanf("%d%c" , &e , &c) != EOF){
		push(&s , e);
		if(c == '\n'){
			printstack(s);
			flip(&s , 0);
			r = sort(s);
			push(&r , 0);
			printstack(r);
			init(&s);
		}
	}

	return 0;
}
