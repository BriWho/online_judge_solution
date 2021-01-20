#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char dict[2048][64];
int result[64];
int records[64];
int skip[2048];

void checker(int n , int m ,int idx , int len , int dIdx ,char input[]){

	int j;
	if(len >= m){
		printf("%s =" ,input);
		for(j = 0 ; j < idx ; j++)
			printf(" %s" , dict[result[j]]);
		puts("");
		return;
	}

	for(; dIdx < n ; dIdx++){
		if(skip[dIdx]) continue;
		int isvalid = 1;
		int l = strlen(dict[dIdx]);

		for(j = 0 ; j < l ; j++){
			records[dict[dIdx][j] - 'A']--;
			if(records[dict[dIdx][j] - 'A'] < 0)
				isvalid = 0;
		}
		if(isvalid){
			result[idx] = dIdx;
			checker(n , m , idx + 1 , len + l , dIdx +1, input);
		}
		for(j = 0 ; j < l ; j++)
			records[dict[dIdx][j] - 'A']++;
	}

	return;
}

int main(){
	char input[64];
	char temp[64];
	int n = 0 , m = 0;
	int i , j;

	while(gets(input)){
		if(strcmp("#" , input) == 0) break;
		strcpy(dict[n] , input);
		n++;
	}

	while(gets(input)){
		if(strcmp("#" , input) == 0) break;
		memset(records , 0 , sizeof(records));
		memset(skip , 0 , sizeof(skip));

		m = 0;
		strcpy(temp , input);
		char* tok = strtok(temp , " ");
		while(tok != NULL){
			int len = strlen(tok);
			for(i =0 ; i < len ; i++)
				records[tok[i] - 'A']++;
			m += len;

			for(i = 0 ; i < n ; i++)
				if(strcmp(dict[i] , tok) == 0)
					skip[i] = 1;
			tok = strtok(NULL , " ");
		}

		checker(n , m , 0 , 0 , 0 , input);
	}

	return 0;
}
