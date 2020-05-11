#include<stdio.h>
#include<stdlib.h>

int main(){
	int a, b;
	int i;

	while(	scanf("%d%d" ,&a , &b ) != EOF){
		int ta = a < b?a : b; 
		int tb = a > b?a : b;

		int max = -1;
		for(i = ta ; i <= tb ; i++){
			int cyc_len = 1;
			int j = i;
			while(j != 1){
				if(j % 2 == 1){
					j = j * 3 + 1;
				}else{
					j = j /2;
				}
				cyc_len++;
			}
			if(max < cyc_len)
				max = cyc_len;
		}
		printf("%d %d %d\n" , a , b , max);
	}
	
	return 0;
}
