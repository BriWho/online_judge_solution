#include<stdio.h>
#include<string.h>
#include<limits.h>

const char* C = "roygb";
const char* M = "PGASN";

int main(){
	char input[128];
	char colors[128][5];
	int n = 0 , i , j, k;

	while(gets(input)){
		if(input[0] == '#') break;
		if(input[0] == 'e'){
			int min = INT_MAX , idx = -1;
			for(i = 0 ; i < n ; i++){
				int change = 0;
				for(j = 0 ; j < n ;j++)
					for(k = 0 ; k < 5 ;k++)
						if(colors[i][k] != colors[j][k])
							change++;
				if(change< min)
					min = change , idx = i;
			}

			printf("%d\n" , idx + 1);

			n = 0;
		}else{
			char* tok = strtok(input , ",");

			while(tok !=NULL){
				for(i = 0 ; i < 5 ; i++)
					if(tok[2] == M[i])
						colors[n][i] = tok[0];

				tok = strtok(NULL, ",");
			}

			n++;
		}

	}


	return 0;
}