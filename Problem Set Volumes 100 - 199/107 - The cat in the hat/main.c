#include<stdio.h>
#include<stdlib.h>

int main(){
	
	int H , work;
	int i;

	while(scanf("%d%d" , &H ,&work) != EOF){
		if(H == 0 && work == 0) break;

		for( i = 0 ; i < H ; i++ ){

			int notwork = 0 , totalheight = 0;
			int h = H ,  w = 1;
			while(i > 0 && h % (i + 1) == 0){
				notwork += w;
				totalheight += h * w;

				h /= i + 1;
				w *= i;
			}

			if(h == 1 && w == work ){
				printf("%d %d\n" , notwork , totalheight + w);
				break;
			}
		}
	}

	return 0;
}
