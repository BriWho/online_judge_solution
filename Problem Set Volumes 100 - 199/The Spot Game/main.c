#include<stdio.h>
#include<string.h>

typedef struct Board{
	long long row[50];
	int N;
}Board;

#define RESET(board) (memset(&board , 0 , sizeof(Board)))
#define GET(board , x , y) ((board.row[x] >> y) & 1)
#define SET(board , x , y , val) { \
	if(val) board.row[x] |= (1ll << y); \
	else board.row[x] &= ((-1ll) ^ (1ll << y)); \
}

Board rotate(Board board){
	int i , j;
	Board new_board;
	RESET(new_board);

	new_board.N = board.N;
	for(i = 0 ; i < board.N ; i++){
		for(j = 0 ; j < board.N ; j++)
			SET(new_board , j , board.N - i - 1 , GET(board , i , j));
	}
	return new_board;
}

int isSame(Board board1 , Board board2 ){
	if(board1.N != board2.N) return 0;

	int i;
	int same = 1;
	for(i = 0 ; i < board1.N ; i++){
		if(board1.row[i] != board2.row[i])
			same = 0;
	}

	return same;
}

int samePattern(Board board1 , Board board2){
	Board board3 = rotate(board2);
	Board board4 = rotate(board3);
	Board board5 = rotate(board4);
	return isSame(board1 , board2) || isSame(board1 , board3) ||
		isSame(board1 , board4) || isSame(board1 , board5);
}

int main(){
	int i , j;
	Board records[100];
	Board cur_board;
	int x , y;
	char str[2];

	RESET(cur_board);

	while(scanf("%d" , &cur_board.N) != EOF){
		if(cur_board.N == 0) break;
		int isWin = 0;
		int winPlayer = 0,  winMove = 0;
		for(i = 0 ; i < 2 * cur_board.N ; i++){
			scanf("%d%d%s" ,&x , &y , str);
			x-- , y--;
			if(str[0] == '+')
				SET(cur_board , x , y , 1);
			if(str[0] == '-')
				SET(cur_board , x , y , 0);

			for(j = 0 ; j < i ; j++){
				if(samePattern(records[j] , cur_board)){
					if(!isWin)
						winPlayer = (i + 1) % 2 +1 , winMove = i + 1;  
					isWin = 1;
				}
			}

			records[i] = cur_board;
		}

		if(isWin){
			printf("Player %d wins on move %d\n" , winPlayer, winMove);
		}else
			printf("Draw\n");

		RESET(cur_board);
	}

	return 0;
}