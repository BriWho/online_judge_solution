#include<stdio.h>
#include<string.h>

int dfs(int x , int y , int k , int m , int n){
	if(k < 1) return 0;
	return bfs(x - k, y - k, k/2, m, n)+
		bfs(x + k, y - k, k/2, m, n) +
		bfs(x + k, y + k, k/2, m, n) +
		bfs(x - k, y + k, k/2, m, n) +
		(x - k <= m && x + k >= m && y - k <= n && y + k >= n);
}

int main(){
	int i;
	int m, n , k;

	while(scanf("%d%d%d" , &k , &m , &n) == 3){
		if(k == 0 && m == 0 && n == 0) break;
		printf("%3d\n" , dfs(1024 , 1024 , k , m, n));
	}

	return 0;
}
