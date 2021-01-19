#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAXCHAR 26

int node[MAXCHAR];
int neighbours[MAXCHAR][MAXCHAR];
int minbandwidth;
int isused[MAXCHAR];
int result[MAXCHAR];

int max(int a, int b){
	return a > b? a : b;
}

void dfs(int n , int idx , int order[] ,int bandwidth){
	int i , j;
	if(bandwidth >= minbandwidth)
		return;
	if(idx == n){
		for(i = 0 ; i < n ; i++)
			result[i] = order[i] + 'A';
		minbandwidth = bandwidth;
		return;
	}

	for(i = 0 ; i < MAXCHAR ; i++){
		if(node[i]  && !isused[i]){
			isused[i] = 1,order[idx] = i;

			int isvalid = 1 , bw = 0;
			for(j = 0 ; j < idx ; j++){
				if(neighbours[i][order[j]]){
					if(idx - j >= minbandwidth)
						isvalid = 0;
					bw = max(idx - j , bw);
				}
			}
			if(isvalid) dfs(n , idx +1 , order , max(bw , bandwidth));
			isused[i] = 0;
		}
	}

}

int main(){
	char input[128];
	int order[MAXCHAR];
	int i , j;

	while(scanf("%s" , input)!=EOF){
		if(input[0] == '#') break;
		memset(node , 0 , sizeof(node));
		memset(neighbours , 0 , sizeof(neighbours));
		memset(isused , 0 , sizeof(isused));

		int n = 0;
		minbandwidth = 9;
		char* token = strtok(input , ";");
		while(token != NULL){
			char n = token[0];
			char* neighbour = token + 2;
			node[n-'A'] = 1;

			for(i = 0 ; i < 1*strlen(neighbour) ; i++){
				node[neighbour[i] - 'A'] = 1;
				neighbours[n - 'A'][neighbour[i] - 'A'] = 1;
				neighbours[neighbour[i]-'A'][n - 'A'] = 1;
			}
			token = strtok(NULL , ";");
		}

		for(i = 0 ; i < MAXCHAR ; i++)
			n += node[i];
		dfs(n , 0 , order , 0);

		for(i = 0 ; i < n ; i++)
			printf("%c " , result[i]);
		printf("-> %d\n" , minbandwidth);

	}
	return 0;
}
