#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Table{
	char code[8];
	char locality_name[32];
	double price_pm;
}Table;

Table tables[4098];
int isIDD(char code[], char number[]){
	int m1 = strlen(code);
	int m2 = strlen(number);
	if(code[0] == '0' && code[1] == '0' && m1 >= 3 && m1 <= 5 &&m2 >= 4 && m2 <= 10)
		return 1;
	return 0;
}

int isSTD(char code[] , char number[]){
	int m1 = strlen(code);
	int m2 = strlen(number);
	if(code[0] == '0' && m1 >= 2 && m1 <= 6 &&m2 >= 4 && m2 <= 7)
		return 1;
	return 0;
}

int searchPrefix(int n , char number[]){
	int i;
	for(i = 0 ; i < n ; i++){
		int m = strlen(tables[i].code);
		if(strncmp( number , tables[i].code , m) == 0 && 
			(isIDD(tables[i].code , number + m) || isSTD(tables[i].code , number + m)))
			return i;
	}

	return -1;
}

int main(){
	char input[2][64];
	double num;
	int n = 0;

	while(scanf("%s" ,input[0])!=EOF){
		if(strcmp(input[0] , "000000") == 0)
			break;

		strcpy(tables[n].code , input[0]);
		scanf(" %[^\n]" , input[1]);
		strcpy( tables[n].locality_name , strtok(input[1] , "$"));
		sscanf(strtok(NULL , "$") , "%lf" , &tables[n].price_pm);

		n++;
	}
	
	while(scanf("%s" , input[0]) !=EOF){
		if(input[0][0] == '#') break;
		scanf("%lf" , &num);
		if(input[0][0] == '0'){
			int index = searchPrefix(n , input[0]);
			if(index < 0){
				printf("%-16s%-25s          %5.0lf        -1.00\n" , input[0] ,"Unknown" , num);
			}else{
				printf("%-16s%-25s%10s%5.0lf%6.2lf%7.2lf\n" , input[0] , tables[index].locality_name , 
					input[0] + 1*strlen(tables[index].code) , num , tables[index].price_pm/100 , 
					tables[index].price_pm/100 *num );
			}
		}else{
				printf("%-16s%-25s%10s%5.0lf  0.00   0.00\n" , input[0] ,"Local" , input[0], num);
		}

	}

	return 0;
}