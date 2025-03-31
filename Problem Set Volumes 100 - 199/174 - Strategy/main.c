#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum { NONE , TRADE , CHEAT };

int match(char strategy[] , int* idx , char* w ){
    int i, len = strlen(w);
    for(i = 0 ; i < len ; i++)
        if(strategy[*idx + i] != w[i])
            return 0;
    *idx += len;
    return 1;
}

int parse_command(char strategy[] , int* idx){
    if(match(strategy , idx , "TRADE")) return TRADE;
    if(match(strategy , idx , "CHEAT")) return CHEAT; 
    return NONE;
}

int parse_memory(char strategy[] , int* idx ,int my_mem[2] , int your_mem[2]){
    if(match(strategy , idx , "MY")){
        if(match(strategy , idx , "LAST1")) return my_mem[0];
        if(match(strategy , idx , "LAST2")) return my_mem[1];
    }
    if(match(strategy , idx , "YOUR")){
        if(match(strategy , idx , "LAST1")) return your_mem[0];
        if(match(strategy , idx , "LAST2")) return your_mem[1];
    }

    return NONE;
}

int parse_cond(char strategy[] , int* idx ,int my_mem[2] , int your_mem[2]){
    int mem = parse_memory(strategy , idx , my_mem , your_mem);
    if(match(strategy , idx , "=")){
        if(match(strategy , idx , "NULL"))
            return mem == NONE;
        return mem == parse_command(strategy , idx );
    }
    if(match(strategy , idx , "#")){
        if(match(strategy , idx , "NULL" ))
            return mem != NONE;
        return mem != parse_command(strategy , idx );
    }
    return 0;
}


int parse_condition(char strategy[] , int* idx ,int my_mem[2] , int your_mem[2]){
    int condition = parse_cond(strategy , idx , my_mem , your_mem);
    if(match(strategy , idx , "AND"))
        condition = condition & parse_condition(strategy , idx , my_mem , your_mem);
    if(match(strategy , idx , "OR"))
        condition =  condition | parse_condition(strategy , idx , my_mem , your_mem);
    return condition;
}


int parse_statement(char strategy[] , int* idx ,int my_mem[2] , int your_mem[2]){
    if(match(strategy , idx , "IF")){
        int condition = parse_condition(strategy , idx , my_mem , your_mem);
        if(match(strategy , idx , "THEN")){
            int left = parse_statement(strategy , idx , my_mem , your_mem);
            int right = NONE;
            if(match(strategy , idx , "ELSE"))
                right = parse_statement(strategy , idx , my_mem , your_mem);
            return condition ? left : right;
        }
        return NONE;
    } 
    return parse_command(strategy , idx );
}

int program(char strategy[] ,int my_mem[2] , int your_mem[2]){
    int idx = 0;
    return parse_statement(strategy , &idx , my_mem , your_mem);
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
                
                mem[0][1] = mem[0][0], mem[0][0] = cmd1; 
                mem[1][1] = mem[1][0], mem[1][0] = cmd2;
            }
        }
    }

    for(i = 0 ; i < n ; i++)
        printf("%3d\n" , score[i]);
    return 0;
}
