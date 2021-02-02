#include<stdio.h>
#include<string.h>

#define max(a,b) (a > b? a : b)
#define min(a,b) (a < b? a : b)

void space(int a){
	int i;
	for(i = 0 ; i < a ; i++)
		printf(" ");
}

void innerPart(int line , int b[2][2] , int c[2][2] , char v[2][32] , int l[2]){
	int i = 0;
	while(i < line){
		space(b[0][0]);
		printf("%c" , v[0][l[0]++]);
		space(c[0][0] + 3 + b[1][0]);
		printf("%c\n" , v[1][l[1]++]);
		i++;
	}
}

void outerPart(int line , int flag , int a[2][2] , int b[2][2] , char v[2][32] , int l[2]){
	int i = 0;
	while(i < line){
		if(flag){
			space(a[0][0] + 3 + b[1][0]);
			printf("%c\n" , v[1][l[1]++]);
		}else{
			space(b[0][0]);
			printf("%c\n" , v[0][l[0]++]);
		}
		i++;
	}
}

int main(){
	char h[2][32] , v[2][32];
	int i , j, k;
	int first = 1;
	int isIntersect[2];
	int a[2][2] , b[2][2] , c[2][2];

	while(scanf("%s" , h[0]) !=EOF){
		if(h[0][0] == '#') break;
		scanf("%s%s%s" , v[0] , h[1] , v[1]);
		if(!first) puts("");
		else first = 0;

		memset(isIntersect , 0 , sizeof(isIntersect));
		a[0][0] = strlen(h[0]) , a[0][1] = strlen(v[0]);
		a[1][0] = strlen(h[1]) , a[1][1] = strlen(v[1]);
		memset(b , 0 , sizeof(b));
		memset(c , 0 , sizeof(c));

		for(i = 0 ; i < 2 ; i++){
			for(j = 0 ; j < a[i][0] && !isIntersect[i]; j++)
				for(k = 0 ; k < a[i][1] && !isIntersect[i]; k++)
					if(h[i][j] == v[i][k]){
						b[i][0] = j , c[i][0] = a[i][0] - j - 1;
						b[i][1] = k , c[i][1] = a[i][1] - k - 1;
						isIntersect[i] = 1;
					}
		}

		if(isIntersect[0] && isIntersect[1]){
			int l[2] = {0, 0};

			outerPart(max(b[0][1], b[1][1]) - min(b[0][1], b[1][1]) , b[0][1] < b[1][1] , a , b , v , l);
			innerPart(min(b[0][1], b[1][1]) , b , c , v , l);
			printf("%s   %s\n" , h[0] , h[1]);
			l[0]++ , l[1]++;
			innerPart(min(c[0][1], c[1][1]) , b , c , v , l);
			outerPart(max(c[0][1], c[1][1]) - min(c[0][1], c[1][1]) , c[0][1] < c[1][1] , a , b , v , l);
		}else
			printf("Unable to make two crosses\n");

	}
	return 0;
}