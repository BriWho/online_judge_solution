#include<stdio.h>
#include<string.h>

const char DIR[4] = "ENWS";

int main(){
	int n , m;
	int x , y ;
	char ins[128] , c[2];
	int lost[64][64];
	int i;

	memset(lost , 0 , sizeof(lost));

	scanf("%d%d" , &n , &m);
	while(scanf("%d%d%s" , &x, &y , c) != EOF){
		scanf("%s" , ins);
		int d = c[0];

		for(i = 0 ; i < 4 ; i++){
			if(DIR[i] == d){
				d = i;
				break;
			}
		}

		int len = strlen(ins);
		int isvalid = 1;
		for(i = 0 ; i < len ; i++){
			int tx = x , ty = y;
			switch(ins[i]){
			case 'F': 
				switch(d){
				case 0: tx++; break; 
				case 1: ty++; break;
				case 2: tx--; break;
				case 3: ty--; break;
				}
				break;
			case 'L': d = (d + 1)%4; break;
			case 'R': d = (d + 3)%4; break;
			}
			if(tx < 0 || ty < 0 || tx > n || ty > m){
				if(!lost[x][y]){
					isvalid = 0;
					lost[x][y] = 1;
					break;
				}
			}else{
				x = tx , y = ty;
			}
		}

		printf("%d %d %c" , x , y , DIR[d]);
		if(!isvalid)
			printf(" LOST");
		puts("");
	}

	return 0;
}