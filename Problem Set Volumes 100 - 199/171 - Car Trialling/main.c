#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 128
#define MAX_N 128

char shift(char text[MAX_LENGTH]){
    int i , len = strlen(text);
    char e = text[0];
    for(i = 1 ; i < len ; i++)
        text[i-1] = text[i];
    text[len - 1] = 0;
    return e;
}

void unshift(char text[MAX_LENGTH] , char c){
    int i , len = strlen(text);
    for(i = len ; i > 0 ; i--)
        text[i] = text[i-1];
    text[0] = c;
    text[len+1] = 0;
}

char pop(char text[MAX_LENGTH]) {
    int len = strlen(text);
    char e = text[len -1];
    text[len - 1] = 0;
    return e;
}

void push(char text[MAX_LENGTH] , char c){
    int len = strlen(text);
    text[len] = c;
    text[len + 1] = 0;
}


int is_digit(char d){
    return '0' <= d && d <= '9';
}

int parse_nnn(char text[][MAX_LENGTH] , int L , int R){
    if(R - L != 1) return 0;
    int i , len = strlen(text[L]);
    for(i = 0 ; i < len ; i++)
        if(!is_digit(text[L][i]))
            return 0;
    return 1;
}
int parse_cas(char text[][MAX_LENGTH] , int L , int R) {
    if(R - L == 3){
        return strcmp(text[L] , "CHANGE") == 0 && 
            strcmp(text[L+1] , "AVERAGE") == 0 && 
            strcmp(text[L+2] , "SPEED") == 0;
    }
    if(R - L == 1)
        return strcmp(text[L] , "CAS") == 0;
    return 0;
}
int parse_change(char text[][MAX_LENGTH] , int L , int R){
    if(R - L >= 4 && strcmp(text[R-1] , "KMH") == 0){
        int i , j;
        for( i = L ; i < R - 1 ; i++){
            if(strcmp(text[i] , "TO") == 0)
                return parse_cas(text , L , i) && parse_nnn(text , i + 1 , R - 1);
        }
    }
    return 0;
}

int parse_record(char text[][MAX_LENGTH] , int L , int R ){
    return R - L == 2 && strcmp(text[L] , "RECORD") == 0 &&
        strcmp(text[L+1] , "TIME") == 0 ;
}

int parse_time_keeping(char text[][MAX_LENGTH] , int L , int R){
    return parse_record(text , L , R) || parse_change(text, L , R);
}

int is_letter(char a){
    return ('A' <= a && a <= 'Z') || a == '.'; 
}

int parse_s_word(char text[][MAX_LENGTH] , int L) {
    int i , len = strlen(text[L]);
    for(i = 0 ; i < len ; i++)
        if(!is_letter(text[L][i]))
            return 0;
    return 1;
}

int parse_signwords(char text[][MAX_LENGTH] , int N) {
    if(N == 1) return parse_s_word(text , N - 1);
    return parse_signwords(text , N - 1) && parse_s_word(text , N - 1);
}

int parse_sign(char text[][MAX_LENGTH] , int L , int R){
    int len = strlen(text[L]);
    if(R - L != 1 || text[L][0] != '\"' || text[L][len-1] != '\"') 
        return 0;
    char i , tmp[MAX_N][MAX_LENGTH];
    int n = 0 , state = 0 , m = 0;
    for(i = 1 ; i < len -1 ; i++){
        if(isspace(text[L][i])){
            if(state == 1) 
                tmp[n++][m] = 0;
            state = 0 , m = 0;
        } else {
            tmp[n][m++] = text[L][i];
            state = 1;
        }
    }
    if(state == 1)
        tmp[n++][m] = 0;
    if(parse_signwords(tmp , n)){
        text[L][1] = 0;
        for(i = 0 ; i < n - 1; i++){
            strcat( text[L] , tmp[i] );
            strcat( text[L] , " ");
        }
        strcat( text[L] , tmp[n-1] );
        strcat( text[L] , "\"");
        return 1;
    }
    return 0;
}

int parse_where(char text[][MAX_LENGTH] , int L , int R){
    return R - L > 1 && strcmp(text[L] , "AT") == 0 && parse_sign( text , L + 1 , R); 
}

int parse_when(char text[][MAX_LENGTH] , int L , int R ) {
    return R - L == 1 && (strcmp(text[L] , "FIRST") == 0 || strcmp(text[L] , "SECOND") == 0 || strcmp(text[L] , "THIRD") == 0); 
}

int parse_direction(char text[][MAX_LENGTH] , int L , int R ) {
    return R - L == 1 && (strcmp(text[L] , "RIGHT") == 0 || strcmp(text[L] , "LEFT") == 0);
}

int parse_how(char text[][MAX_LENGTH], int L , int R) {
    if(R - L == 1) return strcmp(text[L] , "GO") == 0 || strcmp( text[L] , "KEEP") == 0;
    return R - L > 1 && strcmp(text[L] , "GO") == 0 && parse_when(text , L + 1, R);
}

int parse_directional(char text[][MAX_LENGTH] , int L , int R ) {
    int i , j;
    for(i = L + 1 ; i < R ; i++ ){
        if(!parse_how( text , L , i ))
            continue;

        for(j = i ; j < R ; j ++){
            if(parse_direction(text , i , j) && parse_where(text , j , R))
                return 1;
        }
        if(parse_direction(text , i , R))
            return 1;
    }
    return 0;
}

int parse_navigational(char text[][MAX_LENGTH] , int L , int R) {
    int i;
    for(i = R-1 ; i >= 0 ; i--){
        if(strcmp(text[i] , "AND") == 0 && strcmp(text[i+1] , "THEN") == 0 ){
            if(parse_navigational(text , L , i ) && parse_directional(text , i + 2, R))
                return 1;
        }
    }

    return parse_directional(text , L , R);
}


int parse_instruction(char text[][MAX_LENGTH] , int L , int R) {
    int i;
    for( i = R - 1; i >= 0 ; i--){
        if(strcmp(text[i] , "AND") == 0){
            if(parse_navigational(text , L , i) && parse_time_keeping(text , i+1 ,R))
                return 1;
        }
    }
    return parse_navigational(text , L , R) || parse_time_keeping(text , L ,R);
}

int main(){
    char input[MAX_LENGTH];
    char text[MAX_N][MAX_LENGTH];
    int count = 1;


    while(fgets(input, sizeof(input), stdin)) {
        int i , len = strlen(input);
        input[--len] = 0;
        if(strcmp("#" , input) == 0)
            break;
        int n = 0 ,state = 0 , m = 0;
        for(i = 0 ; i < len ; i++){
            if(isspace(input[i]) && state!=2){
                if(state == 1){ 
                    text[n++][m] = 0;
                    state = 0 , m = 0;
                }
            } else if(input[i] == '\"') {
                if(state == 2) state = 1;
                else state = 2;
                text[n][m++] = input[i];
            } else {
                text[n][m++] = input[i];
                if(state == 0)
                    state = 1;
            }
    
        }
        if(state == 1 || state == 2)
            text[n++][m] = 0;
        if(parse_instruction(text , 0 , n)){
            printf("%3d. " , count);
            for(i = 0 ; i < n ; i++)
                printf("%s%c" , text[i] , " \n"[i==n-1]);
        }else
            printf("%3d. Trap!\n" , count );
        count++;
    }

    return 0;
}
