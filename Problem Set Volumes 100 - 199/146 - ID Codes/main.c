#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define swap(type , a , b) {type t = a; a = b ; b = t; }

int cmp(const void* a , const void*  b){
	int A = *(char*)a, B = *(char*)b;
	return A > B? 1 : -1;
}

int main(){
	char code[64];
	int i , j;

	while(scanf("%s" , code) !=EOF){
		if(strcmp("#" , code) == 0)
			break;
		int exist = 0;
		int n = strlen(code);
		for(i = 0 ; i < n -1 ; i++){
			if(code[i] < code[i+1])
				exist = 1;
		}

		if(!exist){
			printf("No Successor\n");
			continue;
		}
		for(i = n-1 ; i >= 0;i--){
			int min = 256 , idx = -1;
			for(j = i + 1 ; j < n ; j++){
				if(min > code[j] &&  code[j] > code[i])
					min = code[j] , idx = j;
			}
			if(idx >= 0){
				swap(char , code[i] , code[idx]);
				i++;
				qsort(code + i , n - i , sizeof(char) , cmp);
				break;
			}
		}


		printf("%s\n" , code);

	}

	return 0;
}
