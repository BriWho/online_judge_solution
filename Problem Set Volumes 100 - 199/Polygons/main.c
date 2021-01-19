#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _point{ double x, y; } Point;
typedef struct _point Vector;

double cross(Vector a ,Vector b){
	return a.x * b.y - b.x * a.y;
}

double cross2(Point o , Point p1 , Point p2){
	Vector v1 = { p1.x - o.x , p1.y - o.y};
	Vector v2 = { p2.x - o.x , p2.y - o.y};
	return cross(v1 , v2);
}

double area(int n , Point poly[]){
	if(n == 0) return 0;
	int i;
	double A = 0;
	for(i = 0 ; i < n ; i++){
		A -= cross(poly[i] , poly[(i+1)%n]);
	}
	return A/2;
}

Point computeIntersect(Point a1 , Point a2 , Point b1 , Point b2){
	double t = cross2(b1 , b2 , a1)/((a2.x - a1.x)*(b2.y - b1.y)-(a2.y - a1.y)*(b2.x - b1.x));
	Point intersectP = { .x=a1.x + (a2.x - a1.x) * t , .y= a1.y + (a2.y - a1.y) * t};
	return intersectP;
}

double intersectArea(int n1 , Point poly[] , int n2 , Point clipPoly[]){
	Point intersectPoly[200];
	Point afterClipPoly[200];
	int i , j , n = 0;

	memcpy(afterClipPoly , poly, sizeof(Point) * n1);

	for(i = 0 ; i < n2 ; i++ ){
		Point curClipPoint = clipPoly[i];
		Point prevClipPoint = clipPoly[(n2 -1 + i)%n2];
		n = 0;

		for(j = 0 ; j < n1 ; j++){
			Point curPoint = afterClipPoly[j];
			Point prevPoint = afterClipPoly[(n1 - 1 + j)%n1];

			if(cross2(prevClipPoint , curClipPoint , curPoint) <= 0){
				if(cross2(prevClipPoint , curClipPoint , prevPoint) > 0)
					intersectPoly[n++] = computeIntersect(curPoint , prevPoint ,curClipPoint , prevClipPoint);
				intersectPoly[n++] = curPoint;
			}else if(cross2(prevClipPoint , curClipPoint , prevPoint) <= 0)
				intersectPoly[n++] = computeIntersect(curPoint , prevPoint ,curClipPoint , prevClipPoint);
		}

		memcpy(afterClipPoly , intersectPoly , sizeof(Point) * n);
		n1 = n;
	}

	return area( n , intersectPoly);
}

int main(){
	int i , j;
	int n1 , n2;
	Point poly1[200] , poly2[200];
	double A[200];
	int m = 0;

	while(scanf("%d" , &n1) != EOF){
		if(n1 == 0) break;
		for(i = 0 ; i < n1 ; i++)
			scanf("%lf %lf" , &poly1[i].x , &poly1[i].y);
		scanf("%d" , &n2);
		for(i = 0 ; i < n2 ; i++)
			scanf("%lf %lf" , &poly2[i].x , &poly2[i].y);

		A[m++] = area(n1 , poly1) + area(n2 , poly2) - 2 * intersectArea(n1 , poly1 , n2 , poly2);
	}


	for(i = 0 ; i < m ; i++)
		printf("%8.2lf" , A[i]);
	printf("\n");
	return 0;
}