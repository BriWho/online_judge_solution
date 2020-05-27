#include<stdio.h>
#include<string.h>
#define MAXN 16
#define MAXL 16

int lquery(char* name ,int n ,  char people[][MAXL]){
	int i;
	for(i = 0 ; i < n ; i++)
		if(strcmp(people[i] , name) == 0)
			return i;
	return -1;
}

int main(){
	int n , i , j , idx;
	char people[MAXN][MAXL];
	int net_worth[MAXN];
	char name[MAXL];
	int money , m;
	int print = 0;

	while(scanf("%d" , &n) != EOF){
		if(print) printf("\n");
		memset(net_worth , 0 , sizeof(net_worth));
		for( i = 0 ; i < n ; i++)
			scanf("%s" , people[i]);
		for(i = 0 ; i < n ; i++){
			scanf("%s%d%d" , name, &money , &m);
			idx = lquery(name , n ,people );
			net_worth[idx] += (m > 0?money % m - money:0);
			for(j = 0 ; j < m ; j++){
				scanf("%s" , name);
				idx = lquery(name , n , people);
				net_worth[idx] += money/m;
			}
		}
		for(i = 0 ; i< n ; i++)
			printf("%s %d\n" , people[i] , net_worth[i]);
		print = 1;
	}
	return 0;
}
