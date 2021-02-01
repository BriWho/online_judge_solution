#include<stdio.h>
#include<string.h>
#include<stdlib.h>
const int MONTH[13] = { 0 , 31 , 59 , 90 , 120 , 151 , 181 ,212 , 243 , 273 , 304 , 334 , 365};
const int LEAPMONTH[13] = { 0 , 31 , 60 , 91 , 121 , 152 , 182 ,213 , 244 , 274 , 305 , 335 , 366};

struct Event{
	int idx;
	int day , month , p;
	int star , diff;
	char e[512];
};

struct Event events[2048];
struct Event* event_p[2048];

int daysFromFirstDay(int y , int m , int d){
	return (y % 4 == 0?LEAPMONTH[m-1]:MONTH[m-1]) + d;
}

int cmp(const void* a , const void* b){
	struct Event* A = *(struct Event**)a,* B = *(struct Event**)b;
	if(A -> diff > B -> diff) return 1;
	else if(A -> diff < B -> diff) return -1;
	else if(A -> star < B -> star && A -> diff != 0 ) return 1;
	else if(A -> star > B -> star && A -> diff != 0 ) return -1;
	else if(A -> idx > B -> idx) return 1;
	else return -1;
}

int main(){
	int n , i , first;
	char a[2] , s[16] ,e[512];
	int Y , D , M;

	n = 0 , first = 1;
	scanf("%d" , &Y);
	while(scanf("%s" , a) !=EOF){
		if(a[0] ==  '#') break;
		int daysinYear = Y%4==0?LEAPMONTH[12]:MONTH[12];

		scanf("%d%d" , &D , &M);
		if(a[0] == 'A'){
			events[n].day = D , events[n].month = M;
			scanf("%d" , &events[n].p);
			gets(e);
			for(i = 0 ; i < 1 * strlen(e) ; i++){
				if(e[i] != '\n' && e[i] != ' ' && e[i] != '\t'){
					strcpy(events[n].e , e + i);
					break;
				}
			}
			events[n].idx = n;
			n++;
		}else if(a[0] == 'D'){
			if(!first) puts("");
			else first = 0;
			int m = 0;
			for(i = 0 ; i < n ; i++){
				int diff = (daysFromFirstDay(Y , events[i].month , events[i].day) - daysFromFirstDay(Y , M , D) + daysinYear)%daysinYear;
				if(diff < 0) continue;
				events[i].star = events[i].p - diff + 1;
				events[i].diff = diff;
				if((events[i].star <= 7 && events[i].star > 0) || diff == 0)
					event_p[m++] =  &events[i];
			}
			qsort(event_p , m , sizeof(struct Event*) , cmp);

			printf("Today is:%3d%3d\n" , D , M);
			for(i = 0 ; i < m ; i++){
				memset(s , ' ' , sizeof(char) * 7) , s[7] = 0;
				memset(s , '*' , sizeof(char) * event_p[i] -> star);
				if(event_p[i] -> day == D && event_p[i] -> month == M)
					strcpy(s , "*TODAY*");
				printf("%3d%3d %7s %s\n" , event_p[i] -> day , event_p[i]-> month , s , event_p[i]-> e );
			}
		}
	}

	return 0;
}
