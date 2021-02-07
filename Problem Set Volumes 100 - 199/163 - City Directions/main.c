#include<stdio.h>
#include<string.h>

enum { NORTH ,NORTHEAST , EAST , SOUTHEAST , SOUTH , SOUTHWEST , WEST , NORTHWEST };
const int dx[8] = {0,1,1,1,0,-1,-1,-1};
const int dy[8] = {1,1,0,-1,-1,-1,0,1};
const char DIR[8][4] = {"N" ,"NE" , "E" , "SE" , "S" , "SW" , "W" , "NW"};

int str2int(char* str){
	int len = strlen(str);
	int i;
	int num = 0;
	for(i = 0 ; i < len ; i++){
		if(str[i] <= '9' && str[i] >= '0')
			num = num * 10 + str[i] - '0';
	}
	return num; 
}

int onGrayRoad(int x, int y , int h){
	return (x % 50 == 0 && dx[h] == 0) || (y % 50 == 0 && dy[h] == 0) || (x == y && dx[h] == dy[h]) || (x == -y && dx[h] == -dy[h]);
}

int onWhiteRoad(int x , int y , int h){
	return dx[h] == 0 || dy[h] == 0  || ((x + y) % 50 == 0 &&  dx[h] != dy[h] && x != -y)|| ((x - y) % 50 == 0 &&  dx[h] == dy[h] && x != y);
}

int diagonalRoad(int x , int y , int h){
	return ((x - y) % 50 == 0 &&  dx[h] == dy[h] ) || ((x+ y) % 50 == 0 && dx[h] == -dy[h]);
}

int intersectRoad(int x, int y){
	return x % 50 == 0 && y % 50 == 0;
}

int main(){
	char input[128];
	char str[3][128];
	char cmd[128];
	int n , i;

	int x , y , h;

	while(gets(input)){
		int len = strlen(input);
		input[len] = 0;

		if(strcmp("END" , input) == 0)
			break;		

		sscanf( input , "%s %s %s" , str[0] , str[1] , str[2]);	

		for(i = 0 ; i < 2 ; i++){
			int len = strlen(str[i]);

			if(str[i][0] == 'A'){
				x = str2int(str[i] + 1);
				if(str[i][len-1] == 'W')
					x = -x;
			}
			if(str[i][0] == 'S'){
				y = str2int(str[i] + 1);
				if(str[i][len-1] == 'S')
					y = -y;
			}
		}
		for(i = 0 ; i < 8 ; i++)
			if(strcmp(str[2] , DIR[i]) == 0)
				h = i;

		while(gets(input)){
			len = strlen(input);
			input[len] = 0;

			if(strcmp("STOP" , input) == 0){
				if(onGrayRoad(x,y,h))
					printf("Illegal stopping place\n");
				else
					printf("A%d%c S%d%c %s\n" , x<0?-x:x ,"EW"[x < 0] , y<0?-y:y , "NS"[y < 0] , DIR[h]);
				break;
			}

			int isvalid = 0;
			int tx = x , ty = y , th = h;
			if(sscanf(input, "TURN %s %s" , str[0] , str[1]) == 2){
				if((strcmp(str[0] , "SHARP") == 0 || strcmp(str[0] , "HALF") == 0) &&
					(strcmp(str[1] , "LEFT") == 0 || strcmp(str[1],"RIGHT") == 0)){
					int sharp = strcmp(str[0] , "SHARP") == 0;
					int left = strcmp(str[1] , "LEFT") == 0;

					tx += dx[th] , ty += dy[th];
					th = (th + (sharp?3:1) * (left?-1:1) + 8)%8;

					if(onGrayRoad(tx , ty , th) || onWhiteRoad(tx , ty , th)){
						if(onGrayRoad(x,y, h) != onGrayRoad(tx , ty , th))
							if((sharp && left) || intersectRoad(tx , ty) || intersectRoad(x , y)) 
								isvalid = 1;
						if(onGrayRoad(x , y , h) == onGrayRoad(tx , ty , th))
							isvalid = 1;
					}
				}
			}
			if(sscanf(input , "TURN %s" , str[0]) == 1){
				if(strcmp("LEFT" , str[0]) == 0 || strcmp("RIGHT" , str[0]) == 0){
					int left = strcmp(str[0] , "LEFT") == 0;

					tx += dx[th] , ty += dy[th];
					th = (th + (left?-2:2) + 8) %8;

					if(onGrayRoad(tx , ty , th) || onWhiteRoad(tx , ty , th)){
						if(onGrayRoad(x,y, h) != onGrayRoad(tx , ty , th))
							if(left && !diagonalRoad(x,y,h) && !diagonalRoad(tx , ty , th))
								isvalid = 1;
						if(onGrayRoad(x , y , h) == onGrayRoad(tx , ty , th))
							isvalid = 1;
					}
				}
			}
			if(sscanf(input , "GO STRAIGHT %d %s" , &n , str[0]) == 1 || sscanf(input , "GO %d %s" , &n , str[0]) == 1){
				if(n >= 1 && n <= 99){
					tx += dx[h] * n , ty += dy[h] * n;
					isvalid = 1;
				}
			}

			if(isvalid)
				x = tx , y = ty , h = th;
		}

	}
	return 0;
}
