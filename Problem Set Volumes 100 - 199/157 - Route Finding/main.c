#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int neigh[1024][32];
int neighN[1024];
int isTravel[1024];
char result[1024];
int minCost;

void dfs(int node , int end , char route[] , int cost){
	int i;
	route[cost + 1] = node%26 + 'a';
	if(node == end){
		if(minCost > cost){
			minCost = cost;
			route[cost + 2] = 0;
			strcpy(result , route);
		}
		return;
	}

	isTravel[node] = 1;
	for(i = 0 ; i < neighN[node] ; i++){
		int nxt = neigh[node][i];
		if(isTravel[nxt]) continue;
		if(node/26 == nxt/26){
			dfs(nxt , end , route , cost + 1);
		}else{
			route[cost + 2] = '=';
			route[cost + 3] = nxt/26 + 'A';
			dfs(nxt ,end , route , cost + 3);
		}
	}
	isTravel[node] = 0;
}

int main(){
	int i , j , k;
	int n;
	char path[128];
	char route[128];

	memset(neighN , 0 , sizeof(neighN));
	memset(isTravel , 0 , sizeof(isTravel));
	scanf("%d" , &n);

	for(i = 0 ; i < n ; i++){
		scanf("%s" , path );
		int len = strlen(path);
		int p = path[2];
		for(j = 3 ; j < len ; j++){
			int a = (p-'a') + 26 * (path[0] - 'A') , b;
			if(path[j] == '='){
				b = (path[j+2]-'a') + 26 * (path[j+1]-'A');
				for(k = 0 ; k < neighN[a] ; k++)
					if(a/26 != neigh[a][k]/26 && b/26!=neigh[a][k]/26)
						neigh[b][neighN[b]++] = neigh[a][k];
				for(k = 0 ; k < neighN[b] ; k++)
					if(a/26 != neigh[b][k]/26 && b/26!= neigh[b][k]/26)
						neigh[a][neighN[a]++] = neigh[b][k];
				j += 2;
			}else{
				b = (path[j]-'a') + 26 * (path[0]-'A');
				p = path[j];
			}
			neigh[a][neighN[a]++]=b;
			neigh[b][neighN[b]++]=a;
		}
	}

	while(scanf("%s" , path) == 1){
		if(path[0] == '#') break;
		minCost = INT_MAX;
		int a = (path[1]-'a') + 26 * (path[0]-'A');
		int b = (path[3]-'a') + 26 * (path[2]-'A');
		route[0] = a/26 + 'A';
		dfs(a, b , route , 0);
		printf("%3d: %s\n" , minCost , result);
	}

	return 0;
}
