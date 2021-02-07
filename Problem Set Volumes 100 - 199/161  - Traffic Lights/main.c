#include<stdio.h>
#include<string.h>
#include<limits.h>

int main(){
	int timer[128];
	int red[128];
	int i = 0 , j = 0;

	while(scanf("%d%d%d" , &red[0] , &red[1] , &red[2]) == 3){
		if(red[0] == 0 && red[1] == 0 && red[2] == 0)
			break;
		int n = 2;
		while(red[n] != 0)
			scanf("%d" , &red[++n]);

		memset(timer , 0 , sizeof(timer));
		int min = INT_MAX;
		for(i = 0 ; i < n ; i++)
			if(red[i] < min)
				min = red[i];
		for(i = 0 ; i < n ; i++)
			timer[i] += min;
		int fail = 1;
		for(i = min +1; i <= 5 * 60 * 60 ; i++){
			int ok = 1;
			for(j = 0 ; j < n ; j++){
				timer[j] = (timer[j] + 1)%(red[j] * 2);
				if(timer[j] >= red[j] - 5)
					ok = 0;
			}
			if(ok){
				printf("%02d:%02d:%02d\n" , i/3600 , (i%3600)/60 , i%60);
				fail = 0;
				break;
			}
		}


		if(fail)
			printf("Signals fail to synchronise in 5 hours\n");
	}

	return 0;
}
