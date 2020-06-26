#include<stdio.h>
#include<string.h>

int main(){
	int N , k , m;
	int i , j;
	int isvisited[32];
	while(scanf("%d%d%d" , &N , &k , &m ) != EOF){
		if( N == 0 && k == 0 && m == 0) break;
		int p1 = N-1, p2 = 0;
		int n = 0;
		memset(isvisited , 0 , sizeof(isvisited));
		while(n < N){
			for(i = 0 ; i < k;){
				p1 = (p1 + 1)%N;
				if(!isvisited[p1])
					i++;
			}
			for(i = 0 ; i < m;){
				p2 = (p2 + N- 1)%N;
				if(!isvisited[p2])
					i++;
			}
			if(p1 == p2){
				printf("%3d" , p1 + 1);
				isvisited[p1] = 1;
				n++;
			}else{
				printf("%3d%3d" , p1 + 1 , p2 + 1);
				isvisited[p1] = isvisited[p2] = 1;
				n += 2;
			}
			printf("%c" , ",\n"[n ==N]);
		}
	}
	return 0;
}
