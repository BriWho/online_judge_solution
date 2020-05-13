#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

void printalpha(const char* alpha){
	int i, n = strlen(alpha);
	for(i = 0 ; i < n - 1; i++)
		printf("%c,", alpha[i]);
	printf("%c" , alpha[n-1]);
}

void printreadln(const char* alpha){
	printf("readln(");
	printalpha(alpha);
	printf(")");
}

void printwriteln(const char* alpha){
	printf("writeln(");
	printalpha(alpha);
	printf(")");
}

void printtab(int n){
	while(n--) printf("  ");
}

void print(int n ,int level ,char A[]){
	if(n <= level){
		printtab(level);
		printwriteln(A);
		printf("\n");
		return;
	}

	int i;
	printtab(level);
	for(i = level ; i > 0; i--){
		char a[16] = {};
		memcpy(a , A , sizeof(char) * n);
		printf("if %c < %c then\n",A[i-1] , A[i]);
		print(n , level + 1 , a);
		
		char t = A[i];
		A[i] = A[i-1];
		A[i-1] = t;
		printtab(level);
		printf("else%c" , " \n"[i==1]);
	}
	char a[16] = {};
	memcpy(a , A , sizeof(char) * n);
	print(n , level + 1 , a);
}

int main(){
	int i , j;
	int M , n;
	char A[16];
	scanf("%d" , &M);
	for(i = 0 ; i < M ; i++){
		scanf("%d" , &n);
		for(j = 0 ; j < n ; j++)
			A[j] = "abcdefgh"[j];
		A[n] = 0;
		printf("program sort(input,output);\nvar\n");
		printalpha(A);
		printf(" : integer;\nbegin\n  ");
		printreadln(A);
		printf(";\n");
		print(n,1,A);
		printf("end.\n");
		if(i < M -1) printf("\n");
	}
	return 0;
}