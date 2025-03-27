#include <stdio.h>
#include <string.h>
#include <ctype.h>

int parse(char* input , int* vars , int L , int R){
    int i , lval = 0 , sign = 1;
    int brackets = 0;
    char var_idx = -1;

    for(i = L ; i < R ; i++){
        char c = input[i];
        if(c == '(')
            brackets++;
        else if(brackets > 0){
            if(c == ')'){
                brackets--;
                if(brackets == 0)
                    lval = parse(input , vars , L + 1 , i);
            }
        } 
        else if('A' <= c && c <= 'Z')
            var_idx = c - 'A';
        else if('0' <= c && c <= '9')
            lval = 10 * lval + (c - '0');
        else if(c == '_')
            sign = -1;
        else {
            int rval = parse(input , vars , i + 1 , R);
            lval = var_idx < 0? lval : vars[var_idx];
            if(c == '=') return vars[var_idx] = rval;
            if(c == '+') return sign * lval + rval;
            if(c == '-') return sign * lval - rval;
            if(c == '*') return sign * lval * rval;
            if(c == '/') return sign * lval / rval;
        }
    }

    return sign * (var_idx < 0 ? lval : vars[var_idx]);

}

int main(){
    int vars[2][26];
    char input[128];
    memset(vars , 0 , sizeof(vars));

    while(fgets(input , 128 , stdin)){
        int i , n = 0;
        int len = strlen(input);
        input[--len] = 0;
        if(strcmp(input , "#") == 0) break;

        for( i = 0 ; i < len ; i++){
            if(!isspace(input[i]))
                input[n++] = input[i];
        }
        input[n] = 0;
        memcpy(vars[1] ,  vars[0] , sizeof(int) * 26);

        parse(input , vars[0]  , 0 , n);

        int n_change = 0;
        for( i = 0 ; i < 26 ; i++){
            if(vars[0][i] != vars[1][i]){
                if(n_change > 0)
                    printf(", ");
                printf("%c = %d" , i + 'A' , vars[0][i]);
                
                n_change++;
            }
        }

        if(n_change == 0)
            printf("No Change");
        puts("");

    }


    return 0;

}
