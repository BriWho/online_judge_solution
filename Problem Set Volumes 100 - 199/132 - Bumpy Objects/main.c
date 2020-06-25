#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#define MAXN 128

typedef struct{ int x , y; } point;

void _pswap(point* a , point* b){ point t = *a; *a = *b; *b = t; }
point _padd(point a , point b){ 
	point t = { a.x + b.x , a.y + b.y }; 
	return t; 
}
point _psub(point a, point b) { 
	point t = { a.x - b.x , a.y - b.y }; 
	return t; 
}
int _plen2(point a){ 
	return (a.x * a.x) + (a.y * a.y); 
}
int _cross(point a , point b){ 
	return (a.x * b.y) - (a.y * b.x); 
}

int iscollinear(point a , point b , point c){
	return (c.x - a.x) * (b.y - a.y) == (c.y - a.y)*(b.x - a.x);
}

int dot(point o , point a , point b ){
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

int between(point a , point b , point c){
	return dot(a , b , c) >= 0 && dot(b , a , c) >= 0;
}

int angle_cmp(const void* v , const void* v0){
	point* V = (point*)v , *V0 = (point*)v0;
	int clockwise = _cross(*V , *V0);
	if(clockwise < 0) return 1;
	else if(clockwise > 0) return -1;
	else if(_plen2(*V) > _plen2(*V0)) return 1;
	else return -1;
}

int graham_scan(int n , point p[]){
	int i;
	point v[MAXN+1];

	for(i = 1 ; i < n ; i++)
		if(p[i].y < p[0].y || (p[i].y == p[0].y && p[i].x < p[0].x))
			_pswap(&p[i] , &p[0]);
	
	for(i = 0 ; i < n ; i++ )
		v[i] = _psub(p[i] , p[0]);

	qsort(v, n , sizeof(point) , angle_cmp);

	int m = 0;

	for(i = 0 ; i < n ; i++){
		while( i>= 2 && _cross(_psub(v[i] , v[m-2]) ,_psub(v[m-1] ,v[m-2])) > 0)
			m--;
		v[m++] = v[i];
	}
	for(i = 0 ; i < m ; i++)
		p[i] = _padd(v[i] , p[0]);

	return m;
}

int main(){
	char name[128];
	point cg , p[MAXN] , t[MAXN];
	int i , j;

	while(scanf("%s" , name) != EOF){
		if(strcmp(name , "#") == 0) break;
		int n = 0;
		int min = INT_MAX;
		scanf("%d%d" , &cg.x , &cg.y);
		while(scanf("%d%d" ,&p[n].x , &p[n].y ) == 2){
			if(p[n].x == 0 && p[n].y == 0) break;
			n++;
		}

		memcpy(t , p , sizeof(point) * n);
		int m = graham_scan(n , t);

		for(i = 2 ; i < m ; i++){
			while(i < m && iscollinear(t[i-2] , t[i-1] , t[i])){
				for(j = i - 1; j < m -1 ; j++)
					t[j] = t[j+1];
				m--;
			}
		}

		for(i = 0 ; i < m ;i++){
			point p1 = t[i] , p2 = t[(i+1)%m];
			if(between(p1 , p2 , cg)){
				int max_v = 0;
				for(j = 0 ; j < n ; j++){
					if(between(p1 , p2 , p[j]) && iscollinear(p1 , p2 , p[j]))
						max_v = j + 1 > max_v? j+1 : max_v;
				}
				min = max_v < min? max_v : min; 
			}
		}

		printf("%-20s%d\n" , name , min);
	}
	return 0;
}
