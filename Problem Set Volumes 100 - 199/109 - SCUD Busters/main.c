#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXK 32
#define MAXN 128

typedef struct{ int x , y; } point;

void _pswap(point* a , point* b){ point t = *a; *a = *b; *b = t; }
point _padd(point a , point b){ point t = { a.x + b.x , a.y + b.y }; return t; }
point _psub(point a, point b) { point t = { a.x - b.x , a.y - b.y }; return t; }
int _plen2(point a){ return (a.x * a.x) + (a.y * a.y); }
int _cross(point a , point b){ return (a.x * b.y) - (a.y * b.x); }

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

double area(int n , point p[]){
	int i;
	point t[MAXN+1];

	memcpy(t , p , n * sizeof(point));
	int m = graham_scan(n ,t);

	t[m] = t[0];
	double area = 0;
	for(i = 1 ; i <= m; i++)
		area += 1ll * _cross(t[i-1] , t[i]);
	return area/2;
}

double missile_fire(point mis ,int N , point sites[]){
	sites[N] = mis;
	return area(N + 1 , sites);
}

int main(){
	int i;
	int k = 0;
	int N[MAXK];
	double A[MAXK];
	point sites[MAXK][MAXN];
	point t;
	int destroy[MAXK] = {};

	while(scanf("%d" , &N[k]) != EOF){
		if(N[k] < 0) break;
		for(i = 0 ; i < N[k] ; i++)
			scanf("%d%d" , &sites[k][i].x , &sites[k][i].y);
		A[k++] = area(N[k] , sites[k]);
	}

	double area = 0;
	while(scanf("%d%d" , &t.x , &t.y) != EOF){
		for(i = 0 ; i < k ; i++){
			double a = missile_fire( t , N[i], sites[i]);
			if(a == A[i] && !destroy[i]){
				area += a;
				destroy[i] = 1;
			}
		}
	}

	printf("%.2lf\n" , area);

	return 0;
}
