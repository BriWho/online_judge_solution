#include<stdio.h>
#include<string.h>

struct card{
	char suit , num;
};

struct stack{
	struct card cards[128];
	int top;
};

int pop(struct stack* s , struct card* e){
	if(s -> top <= 0) return 0;
	*e = s -> cards[--(s -> top)];
	return 1;
}

int push(struct stack* s , struct card e){
	if(s -> top >= 128) return 0;
	s -> cards[(s -> top)++] = e;
	return 1;
}

void placeUnder(struct stack* bottomS , struct stack* topS){
	struct stack ts;
	struct card tc;
	memset(&ts , 0 , sizeof(ts));
	while(pop(topS , &tc)) push(&ts , tc);
	while(pop(bottomS , &tc)) push(topS , tc);
	while(pop(&ts , &tc)) push(topS , tc);
}

int main(){
	char a[3];
	int i;
	int n = 0;
	struct stack s[3];
	struct card c;

	memset(s , 0 , sizeof(s));
	while(scanf("%s" , a) !=EOF){
		if(a[0] == '#') break;
		c.suit =a[0] , c.num = a[1];
		push(&s[n%2] ,c);
		n++;
		if(n == 52){
			int change = -1;
			int flag = 0;
			while(pop(&s[flag] ,  &c)){
				push(&s[2] , c);

				if(c.num == 'J' || c.num == 'Q' || c.num == 'K' || c.num == 'A'){
					change = 0;
					switch(c.num){
					case 'A': change++;
					case 'K': change++;
					case 'Q': change++;
					case 'J': change++;
					}

					flag = !flag;
				}else{
					if(change > 1) change--;
					else if( change == 1){
						flag = !flag;
						placeUnder(&s[2] , &s[flag]);
						change = 0;
					}else
						flag = !flag;
				}
			}
			printf("%c%3d\n" , "12"[flag] , s[!flag].top);
			memset(s , 0 , sizeof(s));
			n= 0;
		}
	}

	return 0;
}