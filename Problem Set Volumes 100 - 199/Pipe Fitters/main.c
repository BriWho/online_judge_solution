#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int grid(double w , double h){
	return (int)w * (int)h;
}

int skew(double w , double h){
	int nh = (2*h-2)/sqrt(3) + 1;
	int nw = (int)w;
	return  nw * nh - (w - (int)w < 0.5) * (int)(nh/2);
}

int max(int a , int b){
	return a > b? a : b;
}

int main(){
	double w , h;
	while(scanf("%lf%lf" , &w , &h) != EOF){
		int grid_n = grid(w , h);
		int skew_n = max(skew(w , h) , skew(h , w));

		if(grid_n >= skew_n) printf("%d grid\n" , grid_n);
		else printf("%d skew\n" , skew_n);
	}
	return 0;
}