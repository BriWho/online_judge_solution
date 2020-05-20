#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 512
#define MAXL 32

int min(int a , int b){
	return a < b? a: b;
}

int abs(int a){
	return a < 0? -a: a;
}

int linear_query(char* t_name, int n,  char names[][MAXL]){
	int i;
	for(i = 0 ; i < n ; i++){
		if(strcmp(t_name , names[i]) == 0)
			return i;
	}
	return -1;
}

int least_common_ancestor(int n , int pidx[] , int a , int b){
	if(a < 0 || b < 0)
		return -1;
	int ta = a;
	while(ta >= 0){
		int tb = b;
		while(tb >= 0 ){
			if(ta == tb)
				return ta;
			tb = pidx[tb];
		}
		ta = pidx[ta];
	}

	return -1;
}
int main(){
	char t_name[2][MAXL];
	char names[MAXN][MAXL];
	int parent_index[MAXN];
	int i;
	int n = 0;

	while(scanf("%s%s" , t_name[0] , t_name[1]) != EOF){
		if(strcmp(t_name[0] , "no.child") == 0) break;
		int cidx = linear_query(t_name[0], n, names);
		int pidx = linear_query(t_name[1] ,n, names);
		if(cidx < 0 && pidx < 0){
			strcpy(names[n] , t_name[0]);
			strcpy(names[n+1] , t_name[1]);
			parent_index[n] = n + 1;
			parent_index[n+1] = -1;
			n += 2;
		}else if(cidx < 0){
			strcpy(names[n] , t_name[0]);
			parent_index[n] = pidx;
			n++;
		}else if(pidx < 0){
			strcpy(names[n] , t_name[1]);
			parent_index[cidx] = n;
			parent_index[n] = -1;
			n++;
		}else
			parent_index[cidx] = pidx;

	}

	while(scanf("%s%s" , t_name[0] , t_name[1]) != EOF){
		int ridx = linear_query( t_name[0] ,n , names);
		int sidx = linear_query( t_name[1] ,n , names);

		int r_an = ridx , s_an = sidx;
		int rth = 0 , sth = 0;
		int r = least_common_ancestor(n , parent_index , sidx , ridx);
		if(r < 0)
			puts("no relation");
		else if(r == sidx){
			while(r_an >= 0 && r_an != sidx)
				r_an = parent_index[r_an] , rth++;
			for(i = 0 ; i < rth ; i++){
				switch(rth - i){
				case 1: printf("child\n"); break; 
				case 2: printf("grand "); break;
				default: printf("great ");
				}
			}
		}else if(r == ridx){
			while(s_an >= 0 && s_an != ridx)
				s_an = parent_index[s_an] , sth++;
			for(i = 0 ; i < sth ; i++){
				switch(sth - i){
				case 1: printf("parent\n"); break; 
				case 2: printf("grand "); break;
				default: printf("great "); 
				}
			}
		}else{
			while(r != parent_index[s_an] )
				s_an = parent_index[s_an] , sth++;
			while(r != parent_index[r_an])
				r_an = parent_index[r_an] , rth++;
			int k = min(sth , rth);
			int j = abs(sth - rth);
			if(sth == 0 && rth == 0)
				puts("sibling");
			else{
				printf("%d cousin" , k);
				if(j > 0) 
					printf(" removed %d" , j);
				puts("");
			}
		}

	}

	return 0;
}