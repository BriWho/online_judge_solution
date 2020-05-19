#include<stdio.h>
#include<string.h>

int main(){
	int grid[64][64];
	int value[64][64];
	int cost[64][64];
	int Wallcost;
	int m , n , p;
	int i;

	memset(grid , 0 , sizeof(grid));
	scanf("%d%d" , &m , &n);
	scanf("%d%d" , &Wallcost , &p);

	for( i =0 ; i < p ; i++){
		int x , y , v , c;
		scanf("%d%d%d%d" , &x , &y , &v , &c );
		x-- , y--;
		value[x][y] = v;
		cost[x][y] = c;
		grid[x][y] = 1;
	}

	int x, y , dir , lt;
	int sum = 0;
	while(scanf("%d%d%d%d" , &x , &y , &dir , &lt) != EOF){
		x-- , y--;
		int point = 0;
		while(lt > 1){
			int tx = x , ty = y;
			switch(dir){
				case 0: tx++; break; 
				case 1: ty++; break;
				case 2: tx--; break;
				case 3: ty--; break;
			}

			if(tx == m -1 || tx == 0 || ty == n-1 || 
				ty == 0 || grid[tx][ty]){
				dir = (dir + 3) % 4;
				if(grid[tx][ty]){
					point += value[tx][ty];
					lt -= cost[tx][ty];
				}else
					lt -= Wallcost;
			}else
				x = tx , y = ty;
			lt--;
		}
		printf("%d\n" , point );
		sum+= point;
	}

	printf("%d\n" , sum);
	return 0;
}
