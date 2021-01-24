#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int MONTH_D[2][13] = {
	{ 0 , 31,59,90,120,151,181,212,243,273,304,334,365},
	{ 0 , 31,60,91,121,152,182,213,244,274,305,335,366}
};
char* WEEK[7] = {"Sunday" ,"Monday" , "Tuesday" , "Wednesday" , "Thursday" ,"Friday", "Saturday" };
char* MONTH[12] = {"January" , "February" , "March" , "April" , "May" , 
	"June" , "July" , "August" , "September" , "October" , "November" , "December"};

int YEAR_D[2][3000];

int isLeap(int y , int new){
	return (new && ((y%4 == 0 && y%100 != 0) || y%400 == 0)) || (!new && y%4 == 0);
}

int calDays(int y , int m , int d , int new){
	int ly = y - 1;
	return 365 * ly + ly/4 - new * (ly/100 - ly/400) + MONTH_D[isLeap(y , new)][m-1] + d - 1;
}

int main(){
	int i;
	char week[16] , month[16];
	int y , d;

	YEAR_D[0][0] = YEAR_D[1][0] = 0;
	for(i = 1; i < 3000 ; i++){
		YEAR_D[0][i] += YEAR_D[0][i-1] + MONTH_D[isLeap(i , 0)][12];
		YEAR_D[1][i] += YEAR_D[1][i-1] + MONTH_D[isLeap(i , 1)][12];
	}

	while(scanf("%s" , week)!=EOF){
		if(strcmp("#" , week) == 0) break;
		int w  = 0, m = 0;

		scanf("%d %s %d" ,&d , month , &y );

		for(i = 0 ; i < 7 ; i++)
			if(strcmp(WEEK[i] , week) == 0)
				w = i;
		for(i = 0 ; i < 12 ;i ++)
			if(strcmp(MONTH[i] , month) == 0)
				m = i + 1;

		int flag = 0;
		int days , aY , aM , aD;

		if((calDays(y,m,d ,1) - calDays(1582,10,15 , 1) + 5)%7 ==w )
			flag = 1;
		if((calDays(y,m,d , 0) - calDays(1582,10,5 , 0) + 5)%7 == w)
			flag = 0;

		days = calDays(y,m,d,flag) -2 + 4 * flag;

		flag = !flag; 
		for(i = y -10 ; i < y + 10 ; i++){
			if(days < YEAR_D[flag][i]){
				aY = i;
				break;
			}
		}
		days -= calDays(aY , 1 , 1 , flag) - 1;

		int lflag = isLeap(aY , flag);
		for(i = 0 ; i < 12 ; i++ ){
			if(days <= MONTH_D[lflag][i+1]){
				aM = i;
				aD = days - MONTH_D[lflag][i];
				break;
			}
		}

		if(flag){
			printf("%s %d %s %d\n" , week, aD ,MONTH[aM] , aY);
		}else{
			printf("%s %d* %s %d\n" , week, aD ,MONTH[aM] , aY);
		}

	}

	return 0;
}
