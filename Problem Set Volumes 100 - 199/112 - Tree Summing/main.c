#include<stdio.h>
#include<stdlib.h>

int tree(int sum , int stack){
	int num = 0 , ret = 0;
	char c;

	while(scanf("%c" , &c) == 1){
		if(c == '(') break;
	}
	if(scanf("%d" , &num) == 1){
		int L = tree(sum , stack + num);
		int R = tree(sum , stack + num);
		if(L == 2 && R == 2)
			ret = (sum == stack + num)? 1 : 0;
		if(L == 1 || R == 1)
			ret = 1;
	}else
		ret = 2;
	while(scanf("%c" , &c) == 1){
		if(c == ')') break;
	}
	return ret;
}

int main(){
	int num = 0;
	while(scanf("%d" , &num) != EOF){
		if(tree(num , 0) == 1) puts("yes");
		else puts("no");
	}
	return 0;
}
