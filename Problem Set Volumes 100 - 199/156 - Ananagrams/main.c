#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Word{
	char ord[32];
	char ori[32];
};

int wcmp1(const void* a , const void* b){
	return strcmp((((struct Word*)a) -> ord),(((struct Word*)b) -> ord));
}

int wcmp2(const void* a , const void* b){
	return strcmp((((struct Word*)a) -> ori),(((struct Word*)b) -> ori));
}

int ccmp(const void* a , const void* b){
	char* A = (char*)a, *B = (char*)b;
	if(*A > *B) return 1;
	return -1;
}

int main(){

	char input[32];
	struct Word dict[1024];
	int i;
	int n = 0 , m = 0;

	while(scanf("%s" , input) != EOF){
		if(strcmp(input , "#" ) == 0)
			break;
		strcpy(dict[n].ori ,input );
		int len = strlen(input);
		for(i = 0 ; i < len ; i++)
			input[i] = tolower(input[i]);
		qsort(input , len , sizeof(char) , ccmp);
		strcpy(dict[n].ord , input);
		n++;
	}

	qsort(dict , n , sizeof(struct Word) , wcmp1);

	for(i = 0 ; i < n ;){
		int repeat = 0 , j = i;
		for(j = i+1 ; j < n ;j++){
			if(strcmp(dict[i].ord , dict[j].ord) == 0){
				repeat = 1;
			}else break;
		}
		if(!repeat)
			dict[m++] = dict[i];
		i = j;
	}
	qsort(dict, m , sizeof(struct Word) , wcmp2);
	for(i = 0 ; i < m ; i++)
		printf("%s\n" , dict[i].ori);

	return 0;
}
