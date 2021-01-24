#include<stdio.h>
#include<string.h>

int main(){
	int isTurnOff[128];

	int i , j , k;
	int N , m ;

	while(scanf("%d" , &N) !=EOF){
		if(N == 0) break;
		m = 1;
		while(1){
			memset(isTurnOff , 0 , sizeof(isTurnOff));

			j = 0 ;
			isTurnOff[0] = 1;
			for(i = 1 ; i < N ; i++){
				k = 0;
				while(k < m){
					j = (j + 1)%N;
					if(!isTurnOff[j])
						k++;
				}
				isTurnOff[j] = 1;
			}

			if(j == 12){
				printf("%d\n" ,m );
				break;
			}
			m++;
		}
	}
	return 0;
}
