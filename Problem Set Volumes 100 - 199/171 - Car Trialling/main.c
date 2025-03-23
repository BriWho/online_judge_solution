#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int L , R;
} Bound;
#define MAX_LENGTH 128


Bound trim(char* input , Bound bound ){
    while(bound.R > bound.L && isspace(input[bound.R-1]))
        bound.R--;
    while(bound.L < bound.R && isspace(input[bound.L]))
        bound.L++;
    return bound;
}

Bound find_text_from_right(char* input , Bound bound , char* text) {
    int i = bound.R, len = strlen(text);
    int match_idx = len;
    while(i > bound.L){
        if(input[i-1] == text[match_idx - 1]){
            if(isspace(text[match_idx - 1])){
                while(i > bound.L && isspace(input[i-1]))
                    i--;
                while(match_idx > 0 && isspace(text[match_idx-1]))
                    match_idx--;
            } else 
                match_idx-- , i--;
        } else 
            match_idx = len ,i-- , bound.R = i;

        if(0 == match_idx){
            bound.L = i;
            return bound;
        }
    }
    bound.L = bound.R = -1;
    return bound;
}


int parse_bold_text(char* input , Bound bound , char* output , int OL , char* text) {
    int len = strlen(text);
    Bound new_bound = find_text_from_right(input , bound , text);
    if(new_bound.L == -1) return -1;
    memcpy(output + OL , text , sizeof(char) * len);
    return OL + len;
}


int is_digit(char d){
    return '0' <= d && d <= '9';
}
int parse_nnn(char* input , Bound bound , char* output , int OL){
    int i;
    for(i = bound.L ; i < bound.R ; i++){
        if(is_digit(input[i]))
            output[OL - bound.L + i] = input[i];
        else
            return -1;
    }
    return OL + bound.R - bound.L;
}
int parse_cas(char* input , Bound bound ,char* output , int OL) {
    int change_average_speed_tail = parse_bold_text(input , bound ,output , OL , "CHANGE AVERAGE SPEED");

    if(change_average_speed_tail != -1)
        return change_average_speed_tail;

    return parse_bold_text(input , bound , output , OL , "CAS");
}
int parse_change(char* input , Bound bound , char* output , int OL){
    Bound to_bound = find_text_from_right(input , bound , " TO ");
    if(to_bound.L == -1) return -1;
    Bound cas_bound = { .L = bound.L , .R = to_bound.L };
    int cas_tail = parse_cas(input , cas_bound , output , OL);
    if(cas_tail == -1) return -1;
    Bound kmh_bound = find_text_from_right(input , bound , " KMH");
    if(kmh_bound.L == -1) return -1;
    Bound nnn_bound = { .L = to_bound.R , .R = kmh_bound.L };
    int nnn_tail = parse_nnn(input , nnn_bound , output , cas_tail + 4);
    if(nnn_tail == -1) return -1;

    memcpy(output + cas_tail , " TO " , sizeof(char) * 4);
    memcpy(output + nnn_tail , " KMH" , sizeof(char) * 4);

    return nnn_tail + 4;
}
int parse_record(char* input , Bound bound , char* output , int OL ){
    return parse_bold_text(input , bound , output , OL , "RECORD TIME");
}
int parse_time_keeping(char* input , Bound bound , char* output , int OL){
    int record_tail = parse_record(input , bound , output , OL);
    if(record_tail != -1) return record_tail;
    return parse_change(input , bound , output , OL );
}

int is_letter(char a){
    return ('A' <= a && a <= 'Z') || a == '.'; 
}

int parse_s_word(char* input , Bound bound , char* output , int OL) {
    int i;
    for(i = bound.L ; i < bound.R ; i++){
        if(is_letter(input[i]))
            output[OL - bound.L + i] = input[i];
        else
            return -1;
    }
    return OL + bound.R - bound.L;
}

int parse_signwords(char* input , Bound bound , char* output , int OL) {
    int i;
    for(i = bound.R - 1; i > bound.L ; i--){
        if(!isspace(input[i-1])) continue;
        Bound signwords_bound = { .L = bound.L , .R = i };
        int signwords_tail = parse_signwords( input , signwords_bound , output , OL  );
        if(signwords_tail == -1) return -1;
        Bound s_word_bound = { .L = i , .R = bound.R };
        int s_word_tail = parse_s_word(input , s_word_bound , output , signwords_tail + 1 );
        if(s_word_tail == -1) return -1;
        output[signwords_tail] = ' ';
        return s_word_tail;
    }

    return parse_s_word(input , bound , output , OL );
}

int parse_sign(char* input , Bound bound , char* output , int OL ){
    if(input[bound.L] != '\"' || input[bound.R-1] != '\"') return -1;
    Bound signwords_bound = { .L = bound.L + 1 , .R = bound.R - 1 };
    int signwords_tail = parse_signwords(input , signwords_bound , output , OL + 1);
    if(signwords_tail == -1) return -1;
    output[OL] = output[signwords_tail] = '\"';
    return signwords_tail+1;
}

int parse_where(char* input , Bound bound , char* output , int OL){
    int at_tail = parse_bold_text(input , bound , output , OL , "AT ");
    //printf("at: %d\n" , at_tail);
    if(at_tail == -1) return -1;
    Bound sign_bound = { .L = bound.L+3 , .R = bound.R };
    int sign_tail = parse_sign(input , trim(input , sign_bound)  , output , OL + 3);
        //printf("sign: %d\n" , sign_tail);
    if(sign_tail == -1) return -1;
    output[OL + 2] = ' ';
    return sign_tail;
    return -1;
}

int parse_when(char* input , Bound bound , char* output , int OL ) {
    int first_tail = parse_bold_text(input , bound , output , OL , "FIRST" );
    if(first_tail != -1) return first_tail;
    int second_tail = parse_bold_text(input , bound , output , OL , "SECOND" );
    if(second_tail != -1) return second_tail;
    return parse_bold_text(input , bound , output , OL , "THIRD" );
}

int parse_direction(char* input , Bound bound , char* output ,int OL ) {
    int right_tail = parse_bold_text(input , bound , output , OL , "RIGHT");
    if(right_tail != -1) return right_tail;
    return parse_bold_text(input , bound , output , OL , "LEFT");
}

int parse_how(char* input , Bound bound, char* output , int OL) {
    int go_tail = parse_bold_text(input , bound , output , OL , "GO" );
    if(go_tail != -1) return go_tail;

    go_tail = parse_bold_text(input , bound , output , OL , "GO " );
    if(go_tail != -1){
        Bound when_bound = { .L = bound.L + 2 , .R = bound.R };
        int when_tail = parse_when(input , trim(input , when_bound) , output , OL + 3 );
        if(when_tail != -1){
            output[OL + 2] = ' ';
            return when_tail;
        }
    }
    return parse_bold_text(input , bound , output , OL , "KEEP");
}

int parse_directional(char* input , Bound bound , char* output , int OL ) {
    int i , j;
    //printf("parse_directional: %d %d\n" , L , R );
    for(i = bound.L + 1 ; i < bound.R ; i++ ){
        Bound how_bound = { .L = bound.L , .R = i };
        int how_tail = parse_how( input ,  how_bound , output , OL );
        if(how_tail == -1) continue;
            //printf("how tail: %d\n" , how_tail);
        for(j = i ; j < bound.R ; j ++){
            Bound direction_bound = { .L = i , .R = j };
            int direction_tail = parse_direction( input , direction_bound , output , how_tail + 1);
            if(direction_tail == -1) continue;
                //printf("direction_tail %d L: %d R: %d\n" , direction_tail , j , R);
            Bound where_bound = { .L = j , .R = bound.R };
            int where_tail = parse_where( input , where_bound , output , direction_tail + 1);
            if(where_tail == -1) continue;
                //printf("where_tail: %d\n" , where_tail);
            output[how_tail] = output[direction_tail] = ' ';
            return where_tail;
        }
        Bound direction_bound = { .L = i , .R = bound.R};
        int direction_tail = parse_direction( input , direction_bound , output , how_tail + 1);
        if(direction_tail == -1) continue;

        output[how_tail] = ' ';
        return direction_tail;
    }
    return -1;
}

int parse_navigational(char* input , Bound bound , char* output , int OL) {
    Bound and_then_bound = find_text_from_right(input , bound , " AND THEN ");
    //printf("and_then_bound: L: %d R: %d\n" , and_then_bound.L , and_then_bound.R);
    if(and_then_bound.L != -1){
        Bound navigational_bound = { .L = bound.L , .R = and_then_bound.L };
        int navigational_tail = parse_navigational( input , navigational_bound , output , OL );
        //printf("nav %d\n" , navigational_tail);
        if(navigational_tail != -1){
            Bound directional_bound = { .L = and_then_bound.R , .R = bound.R };
            int directional_tail = parse_directional( input , directional_bound , output , navigational_tail + 10);
            //printf("dir %d\n" , directional_tail );
            if(directional_tail != -1){
                memcpy(output + navigational_tail , " AND THEN ", sizeof(char) * 10);   
                return directional_tail;
            }
        }
    }

    return parse_directional(input , bound , output , OL);
}


int parse_instruction(char* input , Bound bound , char* output , int OL) {
    Bound and_bound = find_text_from_right(input , bound , " AND ");

    //printf("%d %d\n" , and_bound.L , and_bound.R);
    if( and_bound.L != -1){
        Bound navigational_bound = { .L = bound.L , .R = and_bound.L };
        int navigational_tail = parse_navigational( input , navigational_bound , output , OL );
        //printf("nav_tail: %d\n" , navigational_tail);
        if(navigational_tail != -1){
            Bound time_keeping_bound = { .L = and_bound.R , .R = bound.R };
            int time_keeping_tail = parse_time_keeping(input , time_keeping_bound , output , navigational_tail + 5);
            //printf("time_keeping: %d\n" , time_keeping_tail);
            if(time_keeping_tail != -1){
                memcpy( output + navigational_tail , " AND " , sizeof(char) * 5);
                return time_keeping_tail;
            }
        }
        //printf("hello %d\n" , navigational_tail);
    }

    int navigational_tail = parse_navigational( input , bound , output , OL );
    //printf("nav_tail: %d\n" , navigational_tail);
    if(navigational_tail != -1)
        return navigational_tail;
    return  parse_time_keeping(input , bound , output , OL );
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
        Bound bound = { .L = 0 , .R = len };
        len = parse_instruction(input , trim(input , bound) , output , 0);
        if(len != -1){
            output[len] = 0;
            printf("%3d. %s\n" , count , output);
        }else
            printf("%3d. Trap!\n" , count );
        count++;
    }

    return 0;
}
