#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct word_data{
	char* str;
	int idx;
};

char titles[256][256];
int length[256];
struct word_data data[2048];

int cmp(const void* a , const void* b){
	struct word_data* A = (struct word_data*)a;
	struct word_data* B = (struct word_data*)b;
	int r = strcmp(A -> str , B -> str);

	if(r != 0) return r;
	else if(A -> idx > B -> idx) return 1;
	else if(A -> idx < B -> idx) return -1;
	else if(A -> str > B -> str) return 1;
	else return -1;
}

int isIgnore(int n , char ignores[][16] , char* word){
	int i;
	for( i = 0 ; i < n ; i++)
		if(strcmp(ignores[i] , word) == 0)
			return 1;
	return 0;
}

int main(){
	int i , j;
	char ignores[64][16];
	int n = 0, m = 0 ,k = 0;

	while(scanf("%s" , ignores[n]) != EOF){
		if(strcmp(ignores[n] , "::") == 0) 
			break;
		n++;
	}

	while(fgets(titles[m] ,256 , stdin) != NULL){
		int len = strlen(titles[m]) - 1;
		titles[m][len] = 0;

		for(i = 0 ; i< len ; i++){
			titles[m][i] = tolower(titles[m][i]);
			if(titles[m][i] == ' ')
				titles[m][i] = 0;
		}

		for(i = 0 ; i < len ; i++){
			while(titles[m][i] == 0)
				i++;
			int l = strlen(titles[m] + i);
			if(!isIgnore( n , ignores , titles[m] + i)){
				data[k].str = titles[m] + i;
				data[k].idx = m;
				k++;
			}
			i += l;
		}
		length[m] = len;
		m++;
	}
	qsort(data, k , sizeof(struct word_data), cmp);

	for(i = 0 ; i < k ;i++){
		int idx = data[i].idx;

		for(j = 0 ; j < length[idx] ; j++){
			if(titles[idx][j] == 0)
				printf(" ");
			else if(data[i].str == titles[idx] + j){
				while(titles[idx][j] != 0){
					printf("%c", toupper(titles[idx][j]));
					j++;
				}
				j--;
			}else
				printf("%c" , titles[idx][j]);
		}
		puts("");
	}

	return 0;
}
