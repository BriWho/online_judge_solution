#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int abs(const int a){ return a > 0? a : -a;}

int parse_num(char* p){
	int n = 0;
	if(!isdigit(p[0]))
		return 1;
	while(p[0] != 0 && isdigit(p[0])){
		int r = p[0] - '0';
		n = n * 10 + r;
		p++;
	}
	return n;
}

void parse(char poly[] , int coeff[256][256] , int d[2]){
	char* p = poly;
	int c = 1, x = 0, y = 0;
	d[0] = d[1] = 0;

	if(p[0] == '0' && strlen(p) - 1 == 0)
		return;
	if(p[0] == '-'){
		c = -parse_num(p + 1);
		p++;		
	}else
		c = parse_num(p);

	while(p[0] != 0){
		switch(p[0]){
			case '-': c = -parse_num(p + 1); break;
			case '+': c = parse_num(p + 1); break;
			case 'x': x = parse_num(p + 1); break;
			case 'y': y = parse_num(p + 1); break;
		}

		p++;
		if(p[0] == '+' || p[0] == '-' || p[0] == 0){
			coeff[x][y] += c;
			d[0] = x > d[0]? x : d[0];
			d[1] = y > d[1]? y : d[1];
			x = y = 0;
		}
	}
}

int main(){
	char poly[256];	int i;
	int coeff[3][256][256];

	while(scanf("%s" , poly) != EOF){
		if(strcmp(poly ,"#") == 0)
			break;
		memset(coeff , 0 , sizeof(coeff) );

		int d[3][2];
		parse(poly , coeff[0] , d[0]);

		scanf("%s" , poly);
		parse(poly , coeff[1] , d[1]);

		d[2][0] = d[1][0] + d[0][0];
		d[2][1] = d[1][1] + d[0][1];

		int x1 , y1 , x2 , y2;
		for(x1 = 0 ; x1 <= d[0][0] ; x1++)
			for(y1 = 0 ; y1 <= d[0][1] ; y1++)
				for(x2 = 0 ; x2 <= d[1][0] ; x2++)
					for(y2 = 0 ; y2 <= d[1][1] ; y2++)
						coeff[2][x1 + x2][y1 + y2] += coeff[0][x1][y1] * coeff[1][x2][y2];
/*
		for(x1 = 0 ; x1 <= d[0][0] ; x1 ++)
			for(y1 = 0 ; y1 <=  d[0][1] ; y1++)
				printf("%d%c" , coeff[0][x1][y1] , " \n"[y1 == d[0][1]]);
		for(x2 = 0 ; x2 <= d[1][0] ; x2 ++)
			for(y2 = 0 ; y2 <=  d[1][1] ; y2++)
				printf("%d%c" , coeff[1][x2][y2] , " \n"[y2 == d[1][1]]);*/


		int x , y;
		char exp[256];
		char output[256];
		int first = 1;
		int len = 0;

		memset(exp , 0 , sizeof(exp));

		for(x = d[2][0] ; x >= 0; x --){
			for(y = 0 ; y <= d[2][1] ; y++){
				if(coeff[2][x][y] != 0){
					if(first){
						if(coeff[2][x][y] < 0)
							output[len++] = '-';
						first = 0;
					}else{
						output[len++] = ' ';
						output[len++] = "+-"[coeff[2][x][y] < 0];
						output[len++] = ' ';
					}

					int c = abs(coeff[2][x][y]);
					if(c != 1 || (x == 0 && y == 0))
						len += sprintf( output + len , "%d" ,c );
					if(x != 0)
						output[len++] = 'x';
					if(x > 1){
						int l = sprintf( exp + len , "%d" , x);
						for(i = 0 ; i < l ; i++)
							output[len++] = ' ';
					}
					if(y != 0)
						output[len++] = 'y';
					if(y > 1){
						int l = sprintf( exp + len , "%d" , y);
						for(i = 0 ; i < l ; i++)
							output[len++] = ' ';
					}
				}
			}
		}

		for(i = 0 ; i < len ; i++)
			exp[i] = exp[i] == 0? ' ': exp[i];
		if(len == 0)
			output[len++] = '0';
		output[len] = 0;

		printf("%s\n%s\n" , exp ,  output);
	}

	return 0;
}
