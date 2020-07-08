#include<math.h>
#include<stdio.h>

int main(){
	double last , house;
	int n = 0;

	for(last = 2 ; n < 10 ; last++){
		house = sqrt((last + 1) * last /2);
		if(house == floor(house)){
			printf("%10.0lf%10.0lf\n" , house , last);
			n++;
		}
	}
	return 0;
}