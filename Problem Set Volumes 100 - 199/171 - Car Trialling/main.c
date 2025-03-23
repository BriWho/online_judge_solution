#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 128

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

int find_text_from_right(char* input , int L , int R , char* text) {
    int i , len = strlen(text);
    int match_idx = len;
    for(i = R - 1 ; i >= L ; i--){
        if(input[i] == text[match_idx - 1]){
            if(isspace(text[match_idx - 1])){
                match_idx = trim_right(input , L , R );
                i = trim_right(text , L , i);
            } else 
                match_idx--;
            if(0 == match_idx )
                return i;
        } else 
            match_idx = len;
    }
    return -1;
}


int parse_bold_text(char* input , int L , int R , char* output , int OL , char* text) {
    int len = strlen(text);
    if(len + L == R && L == find_text_from_right(input , L , R , text)){
        memcpy(output + OL , text , sizeof(char) * len);
        return OL + len; 
    }
    return -1;
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
    int change_average_speed_tail = parse_bold_text(input ,L , R ,output , OL , "CHANGE AVERAGE SPEED");

    if(change_average_speed_tail != -1)
        return change_average_speed_tail;

    return parse_bold_text(input , L , R , output , OL , "CAS");
}
int parse_change(char* input , int L , int R , char* output , int OL){
    int to_head = find_text_from_right(input , L , R , "TO");
    if(to_head == -1) return -1;
        
    int cas_tail = trim_and_call(parse_cas , input , L , to_head , output , OL);
    if(cas_tail == -1) return -1;

    int kmh_head = find_text_from_right(input , to_head + 2 , R , "KMH");
    if(kmh_head == -1) return -1;
    
    int nnn_tail = trim_and_call(parse_nnn , input , to_head + 2 , kmh_head , output , cas_tail + 4);
    if(nnn_tail == -1) return -1;

    memcpy(output + cas_tail , " TO " , sizeof(char) * 4);
    memcpy(output + nnn_tail , " KMH" , sizeof(char) * 4);

    return nnn_tail + 4;
}
int parse_record(char* input , int L , int R , char* output , int OL ){
    return parse_bold_text(input , L , R , output , OL , "RECORD TIME");
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
    for(i = R - 1; i > L ; i--){
        if(!isspace(input[i-1])) continue;

        int signwords_tail = trim_and_call(parse_signwords , input , L , i , output , OL  );
        if(signwords_tail == -1) return -1;
        int s_word_tail = parse_s_word(input , i , R , output , signwords_tail + 1 );
        if(s_word_tail == -1) return -1;
        output[signwords_tail] = ' ';
        return s_word_tail;
    }

    return parse_s_word(input , L , R , output , OL );
}

int parse_sign(char* input , int L , int R , char* output , int OL ){
    if(input[L] != '\"' || input[R-1] != '\"') return -1;
        
    int signwords_tail = trim_and_call(parse_signwords , input , L + 1 , R - 1 , output , OL + 1);
    if(signwords_tail == -1) return -1;
    output[OL] = output[signwords_tail] = '\"';
    return signwords_tail+1;
}

int parse_where(char* input , int L , int R , char* output , int OL){
    int at_tail = parse_bold_text(input , L , L + 2 , output , OL , "AT");
    //printf("at: %d\n" , at_tail);
    if(at_tail == -1) return -1;
    int sign_tail = trim_and_call(parse_sign , input , L + 2 , R  , output , OL + 3);
        //printf("sign: %d\n" , sign_tail);
    if(sign_tail == -1) return -1;
    output[OL + 2] = ' ';
    return sign_tail;
    return -1;
}

int parse_when(char* input , int L , int R , char* output , int OL ) {
    int first_tail = parse_bold_text(input , L , R , output , OL , "FIRST" );
    if(first_tail != -1) return first_tail;
    int second_tail = parse_bold_text(input , L , R , output , OL , "SECOND" );
    if(second_tail != -1) return second_tail;
    return parse_bold_text(input , L , R , output , OL , "THIRD" );
}

int parse_direction(char* input , int L , int R , char* output ,int OL ) {
    int right_tail = parse_bold_text(input , L , R , output , OL , "RIGHT");
    if(right_tail != -1) return right_tail;
    return parse_bold_text(input , L , R , output , OL , "LEFT");
}

int parse_how(char* input , int L , int R, char* output , int OL) {
    int go_tail = parse_bold_text(input , L , R , output , OL , "GO" );
    if(go_tail != -1) return go_tail;
    go_tail = parse_bold_text(input , L , L+2 , output , OL , "GO" );
    if(go_tail != -1){
        int when_tail = trim_and_call( parse_when , input , L+2 , R , output , OL + 3 );
        if(when_tail != -1){
            output[OL + 2] = ' ';
            return when_tail;
        }
    }
    return parse_bold_text(input , L , R , output , OL , "KEEP");
}

int parse_directional(char* input , int L , int R , char* output , int OL ) {
    int i , j;
    //printf("parse_directional: %d %d\n" , L , R );
    for(i = L + 1 ; i < R ; i++ ){
        int how_tail = trim_and_call(parse_how , input , L , i , output , OL );
        if(how_tail == -1) continue;
            //printf("how tail: %d\n" , how_tail);
        for(j = i ; j < R ; j ++){

            int direction_tail = trim_and_call(parse_direction , input , i ,  j , output , how_tail + 1);
            if(direction_tail == -1) continue;
                //printf("direction_tail %d L: %d R: %d\n" , direction_tail , j , R);
            int where_tail = trim_and_call(parse_where, input , j , R , output , direction_tail + 1);
            if(where_tail == -1) continue;
                //printf("where_tail: %d\n" , where_tail);
            output[how_tail] = output[direction_tail] = ' ';
            return where_tail;
        }
        int direction_tail = trim_and_call(parse_direction , input , i ,  R , output , how_tail + 1);
        if(direction_tail == -1) continue;

        output[how_tail] = ' ';
        return direction_tail;
    }
    return -1;
}

int parse_navigational(char* input , int L , int R , char* output , int OL) {
    int and_then_head = find_text_from_right(input , L , R , "AND THEN");
    
    if(and_then_head != -1){
        int navigational_tail = trim_and_call(parse_navigational , input , L , and_then_head , output , OL );
        //printf("nav %d\n" , navigational_tail);
        if(navigational_tail != -1){
            int directional_tail = trim_and_call(parse_directional , input , and_then_head + 8 , R , output , navigational_tail + 10);
            //printf("dir %d\n" , directional_tail );
            if(directional_tail != -1){
                memcpy(output + navigational_tail , " AND THEN ", sizeof(char) * 10);   
                return directional_tail;
            }
        }
    }

    return parse_directional(input , L , R , output , OL);
}


int parse_instruction(char* input , int L , int R , char* output , int OL) {
    int and_head = find_text_from_right(input , L , R , "AND");

    if( and_head != -1){
        int navigational_tail = trim_and_call(parse_navigational, input , L , and_head , output , OL );
        if(navigational_tail != -1){
            int time_keeping_tail = trim_and_call(parse_time_keeping ,input , and_head + 3, R , output , navigational_tail + 5);
            if(time_keeping_tail != -1){
                memcpy( output + navigational_tail , " AND " , sizeof(char) * 5);
                return time_keeping_tail;
            }
        }
        //printf("hello %d\n" , navigational_tail);
    }

    int navigational_tail = parse_navigational( input , L , R , output , OL );
    //printf("nav_tail: %d\n" , navigational_tail);
    if(navigational_tail != -1)
        return navigational_tail;
    return  parse_time_keeping(input , L , R , output , OL );
}

int main(){
    char input[MAX_LENGTH];
    char output[MAX_LENGTH];
    int count = 1;

    while(fgets(input, sizeof(input), stdin)) {
        int i , len = strlen(input);
        input[--len] = 0;

        if(strcmp("#" , input) == 0)
            break;

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
