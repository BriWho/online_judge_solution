#include<stdio.h>
#include<math.h>

typedef struct Point{
	double x , y;
}Point;

#define swap(type, a , b) { type t = a; a =b; b =t;}
#define min(a , b) (a < b?a:b)
#define max(a , b) (a > b?a:b)
double cross(Point o , Point a , Point b){
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

int inTriangle(Point obj , Point points[3]){
	return cross(points[0] , points[1] , obj) > -1e-9 &&
		cross(points[1] , points[2] , obj) > -1e-9 &&
		cross(points[2] , points[0] , obj) > -1e-9;
}

int main(){
	Point points[3];

	while(scanf("%lf%lf%lf%lf%lf%lf" , &points[0].x , &points[0].y ,
		&points[1].x , &points[1].y, &points[2].x , &points[2].y) != EOF){

		if(points[0].x == 0.0 && points[0].y == 0.0 && points[1].x == 0.0 &&
			points[1].y == 0.0 && points[2].x == 0.0 && points[2].y == 0.0){

			break;
		}

		double min_x = min(ceil(points[0].x) , min(ceil(points[1].x) , ceil(points[2].x)));
		double max_x = max(floor(points[0].x) , max(floor(points[1].x) , floor(points[2].x)));
		double min_y = min(ceil(points[0].y) , min(ceil(points[1].y) , ceil(points[2].y)));
		double max_y = max(floor(points[0].y) , max(floor(points[1].y) , floor(points[2].y)));

		if(cross(points[0] , points[1] , points[2]) < 0)
			swap(Point , points[1] , points[2]);

		int count = 0;
		Point tree = { .x = 0 , .y = 0};
		for(tree.x = max(min_x , 1.0) ; tree.x <= min(max_x , 99.0) ; tree.x++)
			for(tree.y = max(min_y , 1.0) ; tree.y <= min(max_y , 99.0) ; tree.y++)
				if(inTriangle(tree , points))
					count++;
		printf("%4d\n" , count);
	}
	return 0;
}