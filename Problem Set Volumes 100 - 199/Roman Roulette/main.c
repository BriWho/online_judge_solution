#include<stdio.h>

int main(){
	int arr[128]; 
	int i;
	int n , k;

	while(scanf("%d%d" , &n , &k ) != EOF){
		if(n == 0 && k == 0) break;
		k--;
		for(i = 0 ; i< n ; i++)
			arr[i] = i;
		int p = 0 ,t = n;
		while(t > 1){
			p = (p + k) % t;
			for(i = p ; i < t - 1 ;i++)
				arr[i] = arr[i+1];
			t--;
			p %= t;
			int b = (p + k) % t;
			int burrier = arr[b];
			if(p <= b){
				for(i = b ; i < t - 1 ; i++ )
					arr[i] = arr[i + 1];
				for(i = t - 1 ; i > p ; i--)
					arr[i] = arr[i - 1];
				arr[p] = burrier;
			}else{
				for(i = t ; i > p ; i--)
					arr[i] = arr[i - 1];
				arr[p] = burrier;
				for(i = b ; i < t ;i++)
					arr[i] = arr[i + 1];
				p--;
			}
			
			p = (p + 1) % t;
		}
		printf("%d\n" , (n - arr[0])%n + 1);
	}

	return 0;
}