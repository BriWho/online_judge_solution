#include<stdio.h>
#include<string.h>

#define G 34943

int main(){
	char c[1026];
	int i;

	while(gets(c) != NULL){
		if(c[0] == '#') break;
		if(c[0] == 0)
			printf("00 00\n");
		else{
			unsigned int a = 0;
			for(i = 0 ; i < 1* strlen(c) ; i++ )
				a = ((a << 8) | c[i]) % G;
			a = G - (a << 16)%G;
			printf("%02X %02X\n" , (a >> 8)&255 , a & 255);
		}
	}

	return 0;
}
