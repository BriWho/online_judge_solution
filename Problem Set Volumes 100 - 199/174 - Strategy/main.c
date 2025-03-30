#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum { NONE , TRADE , CHEAT };

int match(char strategy[] , int L , int R , char* w ){
    int i, len = strlen(w);
    if(R != L + len) return 0;
    for(i = L ; i < R ; i++)
        if(strategy[i] != w[i - L])
            return 0;
    return 1;
}

int find_idx(char strategy[] , int L , int R , char* w){
    int i , match_idx = 0;
    int len = strlen(w);
    for(i = L ; i < R ; i++){
        if(strategy[i] != w[match_idx])
            match_idx = 0;
        if(strategy[i] == w[match_idx]){
            match_idx++;
            if(len == match_idx)
                return i - len + 1;
        }
    }

    return -1;
}

int parse_command(char strategy[] , int L , int R){
    if(match(strategy , L , R , "TRADE")) return TRADE;
    if(match(strategy , L , R , "CHEAT")) return CHEAT; 
    return NONE;
}

int parse_memory(char strategy[] , int L , int R ,int my_mem[2] , int your_mem[2]){
    if(match(strategy , L , L+2 , "MY")){
        if(match(strategy , L+2 , R , "LAST1")) return my_mem[0];
        if(match(strategy , L+2 , R , "LAST2")) return my_mem[1];
    }
    if(match(strategy , L , L+4 , "YOUR")){
        if(match(strategy , L+4 , R , "LAST1")) return your_mem[0];
        if(match(strategy , L+4 , R , "LAST2")) return your_mem[1];
    }

    return NONE;
}

int parse_cond(char strategy[] , int L , int R ,int my_mem[2] , int your_mem[2]){
    int equal_idx = find_idx(strategy , L , R , "=");
    if(equal_idx >= 0){
        int mem = parse_memory(strategy , L , equal_idx , my_mem , your_mem);
        if(match(strategy , L + 1 , R , "NULL" ))
            return mem == NONE;
        return mem == parse_command(strategy , equal_idx + 1 , R );
    }

    int not_equal_idx = find_idx(strategy , L , R , "#");
    if(not_equal_idx >= 0){
        int mem = parse_memory(strategy , L , not_equal_idx , my_mem , your_mem);
        if(match(strategy , L + 1 , R , "NULL" ))
            return mem == NONE;
        return mem == parse_command(strategy , not_equal_idx + 1 , R );
    }
    

    return 0;
}


int parse_condition(char strategy[] , int L , int R ,int my_mem[2] , int your_mem[2]){
    int start_idx = L;
    int and_idx = find_idx(strategy , start_idx , R , "AND");
    int or_idx = find_idx(strategy , start_idx , R , "OR");

    if(and_idx == -1 && or_idx == -1)
        return parse_cond(strategy , L , R , my_mem , your_mem);
    if(and_idx != -1)
        start_idx = and_idx;
    else if(or_idx != -1)
        start_idx = or_idx;
    else if(and_idx < or_idx)
        start_idx = and_idx;
    else
        start_idx = or_idx;
    int condition = parse_cond(strategy , start_idx , and)
    do{
        if(and_idx == -1){
            start_idx = or_idx;
        } else if(or_idx == -1){
            start_idx = and_idx;
        } else if( and_idx < or_idx){
            start_idx = and_idx;
        } else {
            start_idx = or_idx;
        }
    } while( and_idx != -1 || or_idx != -1 );

    if(and_idx >= 0)
        return parse_cond(strategy , L , and_idx , my_mem , your_mem) || 
            parse_condition(strategy , and_idx + 3 , R , my_mem , your_mem );
    if(or_idx >= 0)
        return parse_cond(strategy , L , or_idx , my_mem , your_mem) &&
            parse_condition(strategy , or_idx + 2 , R , my_mem , your_mem);
    return parse_cond(strategy , L , R , my_mem , your_mem);
}


int parse_statement(char strategy[] , int L , int R ,int my_mem[2] , int your_mem[2]){
    if(match(strategy , L , L+2 , "IF")){
        int then_idx = find_idx(strategy , L + 2 , R , "THEN");
        if(then_idx < 0) return NONE;

        int condition = parse_condition(strategy , L + 2 , then_idx , my_mem , your_mem);

        int else_idx = find_idx(strategy , then_idx + 4 , R , "ELSE");
        if(else_idx < 0) return NONE;
        int if_idx = find_idx(strategy , then_idx + 4 , else_idx , "IF");
        while(if_idx >= L){
            else_idx = find_idx(strategy , else_idx + 4 , R , "ELSE");
            if(else_idx < 0) return NONE;
            if_idx = find_idx(strategy , if_idx + 2 , else_idx , "IF");
        }

        if(condition)
            return parse_statement(strategy , then_idx + 4 , else_idx , my_mem , your_mem);
        else
            return parse_statement(strategy , else_idx + 4 , R , my_mem , your_mem);

    } 
    return parse_command(strategy , L , R );
}

int program(char strategy[] ,int my_mem[2] , int your_mem[2]){
    return parse_statement(strategy , 0 , strlen(strategy) , my_mem , your_mem);
}

int main(){
    char input[256];
    char strategy[16][256];
    int s_len = 0;
    int i , j, k , n = 0;


    while(fgets(input ,256 , stdin)) {
        int len = strlen(input);
        input[--len] = 0;
        if(strcmp(input , "#") == 0)
            break;
        for(i = 0 ; i < len ; i++){
            if(input[i] == '.'){
                strategy[n++][s_len] = 0;
                s_len = 0;
                break;
            }
            if(!isspace(input[i]))
                strategy[n][s_len++] = input[i];
        }
    }

    int mem[2][2];
    int score[16];

    memset( score , 0 , sizeof(score));

    for(i = 0 ; i < n ; i++){
        for(j = i + 1 ; j < n ; j++){
            mem[0][0] = mem[0][1] = NONE;
            mem[1][0] = mem[1][1] = NONE;

            for(k = 0 ; k < 10 ; k++){
                int cmd1 = program(strategy[i] , mem[0] , mem[1]);
                int cmd2 = program(strategy[j] , mem[1] , mem[0]);

                if(cmd1 == TRADE && cmd2 == TRADE)
                    score[i]++, score[j]++;
                if(cmd1 == TRADE && cmd2 == CHEAT)
                    score[i]-=2, score[j]+=2;
                if(cmd1 == CHEAT && cmd2 == TRADE)
                    score[i]+=2, score[j]-=2;
                if(cmd1 == CHEAT && cmd2 == CHEAT)
                    score[i]--, score[j]--;
    
                mem[0][1] = mem[0][0];
                mem[1][1] = mem[1][0];
                mem[0][0] = cmd1;
                mem[1][0] = cmd2;
            }
        }
    }

    for(i = 0 ; i < n ; i++)
        printf("%d\n" , score[i]);
    return 0;
}
