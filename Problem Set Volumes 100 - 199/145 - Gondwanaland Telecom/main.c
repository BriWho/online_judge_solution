#include<stdio.h>
#include<string.h>
typedef unsigned int T;
typedef struct DETAIL_TIME { T timer[3]; } DE_TIME;
#define switchtoT(h , m) (h * 60 + m)

double rate[5][3] = {
	{ 0.10 , 0.06 , 0.02 },
	{ 0.25 , 0.15 , 0.05 },
	{ 0.53 , 0.33 , 0.13 },
	{ 0.87 , 0.47 , 0.17 },
	{ 1.44 , 0.8 , 0.30}
};

const T segment[4] = {
	0,
	switchtoT(8 , 0) ,
	switchtoT(18 , 0) ,
	switchtoT(22 , 0)
};

DE_TIME decompose(T a){
	DE_TIME time;
	memset(&time , 0 , sizeof(time));
	int i;
	for(i = 0 ; i < 3 ; i++){
		if(a > segment[i+1]){
			time.timer[(i+2)%3] += segment[i+1] - segment[i];
		}else{
			time.timer[(i+2)%3] += a - segment[i];
			break;
		}
	}
	if(a > segment[3])
		time.timer[2] += a - segment[3];

	return time;
}

int main(){
	char step[2];
	char called_num[64];
	int sh , sm , th , tm; 
	int day , evening , night;
	double *r;

	while(scanf("%s" , step ) != EOF){
		if(strcmp(step , "#") == 0) break;
		scanf("%s %d %d %d %d" , called_num , &sh , &sm , &th , &tm);
		T start = switchtoT(sh , sm);
		T term = switchtoT(th , tm);
		DE_TIME start_t = decompose(start);
		DE_TIME term_t = decompose(term);

		if(start >= term){
			term_t.timer[0] += 600;
			term_t.timer[1] += 240;
			term_t.timer[2] += 600;
		}
		day = term_t.timer[0] - start_t.timer[0];
		evening = term_t.timer[1] - start_t.timer[1];
		night = term_t.timer[2] - start_t.timer[2];
		r = rate[step[0] - 'A'];
		printf("%10s%6d%6d%6d%3s%8.2lf\n" , called_num , day ,evening , night , step , day * r[0] + evening * r[1] + night * r[2]);

	}

	return 0;
}
