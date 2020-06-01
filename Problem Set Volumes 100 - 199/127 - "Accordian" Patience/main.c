#include<stdio.h>
#include<string.h>

struct card{ char r , s; };

int match(const struct card a , const struct card b){
	return a.r == b.r || a.s == b.s;
}

int main(){
	char input[3];
	int cnt = 0;
	int i , j , k;
	struct card stack[52][52];
	int head[52];

	while(scanf("%s" , input) != EOF){
		if(strcmp(input , "#") == 0)
			break;
		stack[cnt][0].r = input[0];
		stack[cnt][0].s = input[1];
		head[cnt] = 1;
		cnt++;
		if(cnt == 52){
			int pile = 52;
			int ismoved = 1;
			while(ismoved){
				ismoved = 0;
				for(i = 1 ; i < pile && !ismoved; i++){
					if(i >= 3 && match(stack[i-3][head[i-3] - 1] , stack[i][head[i]-1])){
						stack[i-3][head[i-3]++] = stack[i][--head[i]];
						ismoved = 1;
					}else if(match(stack[i-1][head[i-1] - 1], stack[i][head[i]-1])){
						stack[i-1][head[i-1]++] = stack[i][--head[i]];
						ismoved = 1;
					}

					if(head[i] == 0){
						for(j = i ; j < pile - 1 ; j++){
							if(head[j+1] > 0){
								for(k = 0 ; k < head[j+1] ; k++)
									stack[j][k] = stack[j+1][k];
								head[j] = head[j + 1];
							}
						}
						pile--;
					}
				}
			}

			printf("%d pile%s remaining: " , pile , pile == 1?"":"s");
			for(j = 0 ; j < pile ; j++)
				printf("%d%c" , head[j] ," \n"[j == pile-1]);

			cnt = 0;
		}
	}

	return 0;
}
