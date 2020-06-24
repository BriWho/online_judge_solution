#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#define swap(a , b) {int t = a; a = b; b = t;}

const char* name[9] = {
	"straight-flush" , "four-of-a-kind" , "full-house" ,
	"flush" , "straight" , "three-of-a-kind" , 
	"two-pairs" , "one-pair" , "highest-card"
};

int cmp(const void* a , const void* b){
	int* A = (int*)a , *B = (int*)b;
	if(A[0] > B[0]) return 1;
	else if(A[0] < B[0]) return -1;
	else if(A[1] > A[1]) return 1;
	else return -1;
}

int isOP(int cards[5][2]){
	return cards[0][0] == cards[1][0] ||
		cards[1][0] == cards[2][0] ||
		cards[2][0] == cards[3][0] ||
		cards[3][0] == cards[4][0];
}

int isS(int cards[5][2]){
	return (cards[0][0] + 1 == cards[1][0] &&
		cards[1][0] + 1 == cards[2][0] &&
		cards[2][0] + 1 == cards[3][0] &&
		cards[3][0] + 1 == cards[4][0]) || (
		cards[0][0] == 1 && cards[1][0] == 10 &&
		cards[2][0] == 11 && cards[3][0] == 12 &&
		cards[4][0] == 13);
}

int isF(int cards[5][2]){
	return cards[0][1] == cards[1][1] &&
		cards[1][1] == cards[2][1] &&
		cards[2][1] == cards[3][1] &&
		cards[3][1] == cards[4][1];
}


int isSF(int cards[5][2]){
	if(isS(cards) && isF(cards))
		return 1;
	return 0;
}

int isFoaK(int cards[5][2]){
	return (cards[0][0] == cards[1][0] && cards[1][0] == cards[2][0] && 
		cards[2][0] == cards[3][0]) || (cards[1][0] == cards[2][0] && 
		cards[2][0] == cards[3][0] && cards[3][0] == cards[4][0]);
}
int isFH(int cards[5][2]){
	return ( cards[0][0] == cards[1][0] && cards[2][0] == cards[3][0] &&
		cards[3][0] == cards[4][0]) || (cards[0][0] == cards[1][0] &&
		cards[1][0] == cards[2][0] && cards[3][0] == cards[4][0]);
}

int isToaK(int cards[5][2]){
	return (cards[0][0] == cards[1][0] && cards[1][0] == cards[2][0]) || 
		(cards[1][0] == cards[2][0] && cards[2][0] == cards[3][0]) ||
		(cards[2][0] == cards[3][0] && cards[3][0] == cards[4][0]);
}
int isTP(int cards[5][2]){
	return (cards[0][0] == cards[1][0] && cards[2][0] == cards[3][0]) ||
		(cards[0][0] == cards[1][0] && cards[3][0] == cards[4][0]) ||
		(cards[1][0] == cards[2][0] && cards[3][0] == cards[4][0]) ;
}

int (*is[8])(int(*)[2])  = {
	isSF , isFoaK , isFH , isF,
	isS ,isToaK ,isTP , isOP
};

int play(int hand[][2] , int deck[][2] , int idx , int ischanged[]){
	int i , j;
	int type = 8;
	int t[5][2];

	memcpy(t , hand , sizeof(int) * 10);
	qsort(t , 5 , sizeof(int) * 2 , cmp);

	for(i = 0 ; i < 8 ; i++){
		if((*is[i])(t) && i < type){
			type = i;
			break;
		}
	}

	if(idx == 5)
		return type;

	for(i = 0 ; i < 5 ; i++){
		if(ischanged[i]) continue;
		ischanged[i] = 1;
		swap(hand[i][0],deck[idx][0]);
		swap(hand[i][1],deck[idx][1]);

		int ret = play(hand , deck , idx + 1 , ischanged);
		if(ret < type) type = ret;
		ischanged[i] = 0;
		swap(hand[i][0],deck[idx][0]);
		swap(hand[i][1],deck[idx][1]);
	}

	return type;
}

int main(){

	int cards[10][2];
	char inputs[10][3];
	int ischanged[5];
	int N = 0 , i;

	int temp[256];

	temp['A'] = 1 , temp['T'] = 10 , temp['J'] = 11;
	temp['Q'] = 12  , temp['K'] = 13 , temp['C'] = 1;
	temp['D'] = 2 , temp['H'] = 3 , temp['S'] = 4;
	for(i = 2 ; i <= 9 ; i++)
		temp['0' + i] = i;


	while(scanf("%s", inputs[N]  ) != EOF){
		cards[N][0] = temp[inputs[N][0]];
		cards[N][1] = temp[inputs[N][1]];
		N++;
		if(N == 10){
			printf("Hand: ");
			for(i = 0 ; i < 5 ; i++)
				printf("%s " , inputs[i]);
			printf("Deck: ");
			for(i = 5 ; i < 10 ; i++)
				printf("%s " , inputs[i]);
			printf("Best hand: ");
			memset(ischanged , 0 , sizeof(ischanged));

			printf("%s\n" , name[play(cards , cards + 5 , 0 , ischanged)]);
			N = 0;
		}
	}

	return 0;
}