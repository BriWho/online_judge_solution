#include<stdio.h>
#include<string.h>

int gcd(int a, int b){
	if(b) while((a%=b) && (b %= a));
	return a +b;
}

int permN(int n , int numN[] ){
	int frac[32];
	int i , j , k;
	int sum = 0 , ret = 1;
	for(i = 0 ; i < n ; i++)
		sum += numN[i];
	for(i = 0 ; i <= sum ; i++)
		frac[i] = i;
	for(i = 0 ; i < n ; i++){
		for(j = 2 ; j <= numN[i] ; j++){
			int t = j;
			for(k = 2 ; k <= sum ; k++){
				int g = gcd(t , frac[k]);
				t /= g , frac[k] /= g;
			}
		}
	}
	for(i = 1 ; i <= sum ; i++)
		ret *= frac[i];
	return ret;
}

int main(){
	int i , j;
	char A[32];
	int letterN[32];
	while(scanf("%s" , A) !=EOF){
		if(strcmp("#" , A) == 0)
			break;
		int pos = 0;
		int len = strlen(A);
		memset(letterN , 0 , sizeof(letterN));

		for(i = 0 ; i< len ; i++)
			letterN[A[i]-'a']++;

		for(i = 0 ; i< len ; i++){
			int a = A[i] - 'a';
			for(j = 0 ; j < a ; j++){
				if(letterN[j] > 0){
					letterN[j]--;
					pos += permN(26 , letterN);
					letterN[j]++;
				}
			}
			letterN[a]--;
		}

		printf("%10d\n" , pos +1);
	}

	return 0;
}
