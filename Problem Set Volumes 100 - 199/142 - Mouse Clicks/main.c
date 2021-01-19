#include<stdio.h>
#include<limits.h>
#define MAXICONS 100
#define MAXREGIONS 100

int inRegion(int x , int y,int region[4]){
	return x >= region[0] && y >= region[1] && x <= region[2] && y <= region[3]; 
}

int iconDist(int x , int y , int icon[2]){
	return (x - icon[0]) * (x - icon[0]) + (y - icon[1]) * (y - icon[1]);
}

int main(){
	int regions[MAXREGIONS][4];
	int icons[MAXICONS][2];

	char type[2];
	int r = 0, i = 0;
	int x, y , j, k;

	while(scanf("%s" , type)!=EOF){
		if(type[0] == '#') break;
		else if(type[0] == 'I'){
			scanf("%d%d" , &icons[i][0] , &icons[i][1]);
			for(j = 0 ; j < r ; j++){
				if(inRegion(icons[i][0] , icons[i][1] , regions[j])){
					icons[i][0] = icons[i][1] = -1;
					break;
				}
			}
			i++;
		}else if(type[0] == 'R'){
			scanf("%d%d%d%d" , &regions[r][0] , &regions[r][1] , &regions[r][2] , &regions[r][3]);
			for(j = 0 ; j < i ; j++){
				if(inRegion(icons[j][0] , icons[j][1] , regions[r])){
					icons[j][0] = icons[j][1] = -1;
				}
			}
			r++;
		}else if(type[0] == 'M'){
			scanf("%d%d" , &x , &y);
			int minDist = INT_MAX;
			int isInRegion = 0;

			for(j = r - 1 ; j >= 0 ; j--){
				if(inRegion(x , y , regions[j])){
					printf("%c" , j + 'A');
					isInRegion =1;
					break;
				}
			}
			for(j = 0 ; j < i && !isInRegion; j++){
				if(icons[j][0] < 0 || icons[j][1] < 0)
					continue;
				int dist2 = iconDist(x , y , icons[j]);
				if(minDist > dist2) minDist = dist2; 
			}
			for(j = 0 ; j < i && !isInRegion ; j++){
				if(icons[j][0] < 0 || icons[j][1] < 0)
					continue;
				int dist2 = iconDist(x , y , icons[j]);
				if(minDist == dist2) printf("%3d" , j +1); 
			}
			puts("");
		}

	}

	return 0;
}
