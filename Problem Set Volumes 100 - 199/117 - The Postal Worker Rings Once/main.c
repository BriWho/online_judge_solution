#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define swap(type , a , b) { \
	type t = a; \
	a = b; \
	b = t; \
};

int dijkstra(int cost[32][32] , int node[2]){
	int pq[32] , d[32];
	int isused[32] = {};
	int head = 0 , tail = 0;
	int i , j;

	for(i = 0 ; i < 26 ; i++)
		d[i] = INT_MAX;
	d[node[0]] = 0;
	pq[head++] = node[0];

	while(tail < head){
		int n = pq[tail++];
		isused[n] = 1;

		for(i = 0; i < 26 ; i++){
			if(!isused[i] && cost[n][i] > -1){
				if(d[n] + cost[n][i] < d[i]){
					d[i] = d[n] + cost[n][i];
					
					pq[head++] = i;
					for(j = head - 1; j > tail ; j--){
						if(d[pq[j]] < d[pq[j-1]])
							swap(int , pq[j] , pq[j-1]);
					}
				}
			}
		}
	}
	return d[node[1]];
}

int main(){
	char s[128];
	int cost[32][32];
	int deg[32];
	int i , j;
	int cost_sum = 0;
	int n = 0;

	memset(cost , -1 , sizeof(cost));
	memset(deg , 0 , sizeof(deg));

	while(scanf("%s" , s) != EOF){
		if(strcmp(s , "deadend") == 0) {

			int node[2];
			for(i = j = 0 ; i < 26 ; i++)
				if(deg[i] % 2)
					node[j++] = i;
			if(j == 2) 
				cost_sum += dijkstra(cost , node);
			printf("%d\n" , cost_sum);

			cost_sum = n = 0;
			memset(cost , -1 , sizeof(cost));
			memset(deg , 0 , sizeof(deg));
			continue;
		}

		int len = strlen(s);
		cost[s[0]-'a'][s[len-1]-'a'] = len;
		cost[s[len-1]-'a'][s[0]-'a'] = len;
		deg[s[0]-'a']++;
		deg[s[len-1]-'a']++;
		cost_sum += len;
		n++;
	}
	return 0;
}
