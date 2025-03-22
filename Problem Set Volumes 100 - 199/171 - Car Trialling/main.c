#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 128

int match_string(char* input , int L , int R , char* str) {
    int i , j , match_idx = 0;
    int len = strlen(str);
    for(i = L ; i < R ; i++){
        if(input[i] == str[match_idx]){
            match_idx++;
            if(len == match_idx )
                return i - len + 1;
        } else 
            match_idx = 0;
    }
    return -1;
}

int trim_left(char* input , int L , int R){
    int i;
    for(i = L ; i < R ; i++)
        if(!isspace(input[i]))
            return i;
    return R;
}

int trim_right(char* input , int L , int R ){
    int i;
    for(i = R ; i > L ; i--)
        if(!isspace(input[i-1]))
            return i;
    return L;
}

int trim_and_call(int (*parse)(char* , int , int , char* , int) ,
    char* input , int L , int R , char* output , int OL ) {
    return parse(input , trim_left(input , L , R ) , trim_right(input , L , R) , output , OL);
}

int is_digit(char d){
    return '0' <= d && d <= '9';
}
int parse_nnn(char* input , int L , int R , char* output , int OL){
    int i;
    for(i = L ; i < R ; i++){
        if(is_digit(input[i]))
            output[OL - L + i] = input[i];
        else
            return -1;
    }
    return OL + R - L;
}
int parse_cas(char* input , int L , int R ,char* output , int OL) {
    if(R - L == 20 && match_string(input , L , R , "CHANGE AVERAGE SPEED") == L){
        memcpy( output + OL , "CHANGE AVERAGE SPEED" , sizeof(char) * 20);
        return OL + 20;
    }
    if(R - L == 3 && match_string(input , L , R , "CAS") == L){
        memcpy( output + OL , "CAS" , sizeof(char) * 3);
        return OL + 3;
    }
    return -1;
}
int parse_change(char* input , int L , int R , char* output , int OL){
    int to_head = match_string(input , L , R , "TO");

    if(to_head != -1){
        int cas_tail = trim_and_call(parse_cas , input , L , to_head , output , OL);
        if(cas_tail != -1){
            int kmh_head = match_string(input , to_head + 2 , R , "KMH");
            if(kmh_head != -1){
                int nnn_tail = trim_and_call(parse_nnn , input , to_head + 2 , kmh_head , output , cas_tail + 4);
                memcpy(output + cas_tail , " TO " , sizeof(char) * 4);
                memcpy(output + nnn_tail , " KMH" , sizeof(char) * 4);
                return nnn_tail + 4;
            }
        }
    }

    return -1;
}
int parse_record(char* input , int L , int R , char* output , int OL ){
    return R - L == 11 && match_string(input , L , R , "RECORD TIME") == L? OL + 11 : -1;
}
int parse_time_keeping(char* input , int L , int R , char* output , int OL){
    int record_tail = parse_record(input , L , R , output , OL);
    if(record_tail != -1) return record_tail;
    return parse_change(input , L , R , output , OL );
}

int is_letter(char a){
    return ('A' <= a && a <= 'Z') || a == '.'; 
}

int parse_s_word(char* input , int L , int R , char* output , int OL) {
    int i;
    for(i = L ; i < R ; i++){
        if(is_letter(input[i]))
            output[OL - L + i] = input[i];
        else
            return -1;
    }
    return OL + R - L;
}

int parse_signwords(char* input , int L , int R , char* output , int OL) {
    int i;
    int s_word_tail = trim_and_call(parse_s_word , input , L , R , output , OL);

    if(s_word_tail != -1)
        return s_word_tail;

    for(i = L + 1; i < R ; i++){
        int signwords_tail = trim_and_call(parse_signwords , input , L , i , output ,  OL );
        if(signwords_tail == -1) continue;
        s_word_tail = trim_and_call(parse_signwords , input , i , R , output , signwords_tail + 1);
        if(s_word_tail != -1){

        }
    }
    return -1;
}

int parse_sign(char* input , int L , int R , char* output , int OL ){
    if(input[L] == '\"' && input[R] == '\"')
        return trim_and_call(parse_signwords , input , L + 1 , R - 1 , output , OL + 1) + 1;
    return -1;
}

int parse_where(char* input , int L , int R , char* output , int OL){
    int i;
    for(i = L ; i < R ; i++)
        printf("%c" , input[i]);
    puts("");
    if(match_string(input , L , R , "AT") == L){
        int sign_tail = trim_and_call(parse_sign , input , L + 2 , R  , output , OL + 3);
        printf("sign %d\n" , sign_tail);
        if(sign_tail != -1){
            memcpy(output + OL , "AT " , sizeof(char) * 3);
            return sign_tail;
        }
    }
    return -1;
}

int parse_when(char* input , int L , int R , char* output , int OL ) {
    if(match_string(input , L , R , "FIRST") == L && R - L == 5){
        memcpy(output + OL , "FIRST" , sizeof(char) * 5);
        return OL + 5;
    }
    if(match_string(input , L , R , "SECOND") == L && R - L == 6){
        memcpy(output + OL , "SECOND" , sizeof(char) * 6);
        return OL + 6;
    }
    if(match_string(input , L , R , "THIRD" ) == L && R - L == 5){
        memcpy(output + OL , "THIRD" , sizeof(char) * 5);
        return OL + 5;
    }
    return -1;
}

int parse_direction(char* input , int L , int R , char* output ,int OL ) {
    if(match_string(input , L , R , "RIGHT") == L && R - L == 5){
        memcpy(output + OL , "RIGHT" , sizeof(char) * 5);
        return OL + 5;
    }
    if(match_string(input , L , R , "LEFT") == L && R - L == 4){
        memcpy(output + OL , "LEFT" , sizeof(char) * 4);
        return OL + 4;
    }
    return -1;
}

int parse_how(char* input , int L , int R, char* output , int OL) {
    if(R - L == 4 && match_string(input , L , R , "KEEP") == L){
        memcpy(output + OL , "KEEP" , sizeof(char) * 4);
        return OL + 4;
    }
    if(match_string(input , L , R , "GO") == L){
        if(R - L == 2){
            memcpy(output + OL , "GO" , sizeof(char) * 2);
            return OL + 2;
        }
        int when_tail = trim_and_call(parse_when , input , L + 2 , R , output , OL + 3);
        if(when_tail != -1) {
            memcpy( output + OL , "GO ", sizeof(char) * 3); 
            return when_tail;
        }
    }
    return -1;
}

int parse_directional(char* input , int L , int R , char* output , int OL ) {
    int i , j;
    for(i = L + 1 ; i < R ; i++ ){
        int how_tail = trim_and_call(parse_how , input , L , i , output , OL );
        if(how_tail == -1) continue;

        int direction_tail = trim_and_call(parse_direction , input , i ,  R , output , how_tail + 1);
        if(direction_tail != -1) {
            output[how_tail] = ' ';
            return direction_tail;
        }

        for(j = i ; j < R ; j ++){

            direction_tail = trim_and_call(parse_direction , input , i ,  j , output , how_tail + 1);
            if(direction_tail == -1) continue;

            int where_tail = trim_and_call(parse_where, input , j , R , output , direction_tail + 1);
            printf("%d\n" , where_tail);
            if(where_tail != -1){
                output[how_tail] = output[direction_tail] = ' ';
                return where_tail;
            }
        }
    }
    return -1;
}

int parse_navigational(char* input , int L , int R , char* output , int OL) {
    int and_then_head = match_string(input , L , R , "AND THEN");
    
    if( and_then_head != -1){
        int navigational_tail = trim_and_call(parse_navigational , input , L , and_then_head , output , OL );
        
        if(navigational_tail != -1){
        
            int directional_tail = trim_and_call(parse_directional , input , and_then_head + 8 , R , output , navigational_tail + 10);

            if(directional_tail != -1){
                memcpy(output + navigational_tail , " AND THEN ", sizeof(char) * 10);   
                return directional_tail;
            }
        }
        
    }

    return parse_directional(input , L , R , output , OL);
}


int parse_instruction(char* input , int L , int R , char* output , int OL) {
    int and_head = match_string(input , L , R , "AND");
    if( and_head != -1){
        int navigational_tail = trim_and_call(parse_navigational, input , L , and_head , output , OL );
        if(navigational_tail != -1){
            int time_keeping_tail = trim_and_call(parse_time_keeping ,input , and_head + 3, R , output , navigational_tail + 5);
            if(time_keeping_tail != -1){
                memcpy( output + navigational_tail , " AND " , sizeof(char) * 5);
                return time_keeping_tail;
            }
        }

    }

    int navigational_tail = parse_navigational( input , L , R , output , OL );
    if(navigational_tail != -1)
        return navigational_tail;
    return  parse_time_keeping(input , L , R , output , OL );
}

int main(){
    char input[MAX_LENGTH];
    char output[MAX_LENGTH];
    int count = 1;

    while(fgets(input, sizeof(input), stdin)) {
        if(input[0] == '#') break;
        int i , len = strlen(input);
        input[--len] = 0;

        len = trim_and_call(parse_instruction , input , 0 , len , output , 0);
        if(len != -1){
            output[len] = 0;
            printf("%3d. %s\n" , count , output);
        }else
            printf("%3d. Trap!\n" , count );
        count++;
    }

    return 0;
}
