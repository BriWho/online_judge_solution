#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cards[4];
    int n;
} Pile;


int is_empty(Pile* p){
    printf("%d\n" , p-> n);
    return p -> n == 0;
}

int pop(Pile* p) {
    if(p -> n > 0) 
        return p -> cards[--(p -> n)];
    return -1;
}

void push(Pile* p , int c){
    if(p -> n < 4)
        p -> cards[(p -> n)++] = c;
}


int card2Num(char* s) {
    int rank = 0 , suit = 0;
    switch(s[1]) {
    case 'H': suit = 0; break;
    case 'D': suit = 1; break;
    case 'C': suit = 2; break;
    case 'S': suit = 3; break;
    }

    switch(s[0]){
    case 'A': rank = 0; break;
    case 'T': rank = 9; break;
    case 'J': rank = 10; break;
    case 'Q': rank = 11; break;
    case 'K': rank = 12; break;
    default: rank = s[0] - '1'; break;
    }
    return rank * 4 + suit;
}

char* num2Card(int n , char* out ) {
    const char SUIT[4] = { 'H' , 'D' , 'C' , 'S' };
    const char RANK[13] = {
        'A' , '2' , '3' , '4' , '5' , '6' ,
        '7' , '8' , '9' , 'T' , 'J' , 'Q' , 'K' 
    };
    out[0] = RANK[n/4];
    out[1] = SUIT[n%4];
    return out;
}

int main() {
    int i , j;
    char input[3] , output[3];
    Pile piles[13];
    

    while(scanf("%s" , input)!=EOF){
        if(input[0] == '#') break;
        memset(output , 0 , sizeof(output));
        memset(piles , 0 , sizeof(piles));
        push( &piles[0] , card2Num(input));
        for(i = 1 ; i < 52 ; i++){
            scanf("%s" , input);
            push(&piles[i%13] , card2Num(input));
        }
        int count = 1 ,cur = pop(&piles[12]);
        while( !is_empty(&piles[cur/4])){
            printf("%d %d %s %d " , count , cur/4 , num2Card(cur , output) , is_empty(&piles[cur/4]));
            for(i = 0 ; i < 13 ; i++)
                printf("%d%c" , piles[i].n , " \n"[i==12]);
            cur = pop(&piles[cur/4]) , count++;
        }
        printf("%d,%s\n" , count , num2Card(cur, output));
    }

    return 0;
}

/*
4 4 4 4 4 4 4 4 4 4 4 4 3
4 4 3 4 4 4 4 4 4 4 4 4 3
3 4 3 4 4 4 4 4 4 4 4 4 3
2 4 3 4 4 4 4 4 4 4 4 4 3
2 4 3 4 4 3 4 4 4 4 4 4 3
2 4 3 4 4 3 4 4 4 4 3 4 3
2 4 3 4 4 3 4 4 4 4 3 3 3
2 4 3 4 4 2 4 4 4 4 3 3 3
2 4 3 4 4 2 4 4 4 4 2 3 3
2 4 3 3 4 2 4 4 4 4 2 3 3
2 4 3 3 4 1 4 4 4 4 2 3 3
2 4 3 3 4 1 4 4 4 4 2 2 3
2 4 3 3 4 0 4 4 4 4 2 2 3
2 3 3 3 4 0 4 4 4 4 2 2 3
2 3 3 3 4 0 3 4 4 4 2 2 3
2 3 3 3 4 0 2 4 4 4 2 2 3
2 3 3 3 4 0 2 3 4 4 2 2 3
1 3 3 3 4 0 2 3 4 4 2 2 3
1 3 3 3 4 0 2 3 3 4 2 2 3
1 3 3 3 3 0 2 3 3 4 2 2 3
1 3 3 3 3 0 2 3 3 4 2 2 2
1 3 3 3 3 0 2 3 2 4 2 2 2
1 3 3 3 3 0 2 2 2 4 2 2 2
1 3 2 3 3 0 2 2 2 4 2 2 2
1 3 2 3 3 0 2 2 1 4 2 2 2
1 3 2 2 3 0 2 2 1 4 2 2 2
1 3 2 2 2 0 2 2 1 4 2 2 2
1 3 2 2 2 0 1 2 1 4 2 2 2
1 3 2 2 2 0 1 2 1 3 2 2 2
1 3 2 2 2 0 1 2 1 2 2 2 2
1 3 1 2 2 0 1 2 1 2 2 2 2
1 3 1 2 2 0 0 2 1 2 2 2 2
1 3 0 2 2 0 0 2 1 2 2 2 2
1 3 0 2 2 0 0 1 1 2 2 2 2
1 2 0 2 2 0 0 1 1 2 2 2 2
1 2 0 1 2 0 0 1 1 2 2 2 2
1 2 0 1 2 0 0 1 1 2 1 2 2
0 2 0 1 2 0 0 1 1 2 1 2 2
0 2 0 1 2 0 0 1 1 1 1 2 2
0 2 0 1 1 0 0 1 1 1 1 2 2
0 1 0 1 1 0 0 1 1 1 1 2 2
0 1 0 1 1 0 0 1 1 1 0 2 2
0 1 0 1 1 0 0 1 1 0 0 2 2
0 0 0 1 1 0 0 1 1 0 0 2 2
0 0 0 1 1 0 0 1 1 0 0 1 2
0 0 0 0 1 0 0 1 1 0 0 1 2
0 0 0 0 1 0 0 0 1 0 0 1 2
0 0 0 0 1 0 0 0 1 0 0 1 1
0 0 0 0 0 0 0 0 1 0 0 1 1
0 0 0 0 0 0 0 0 1 0 0 0 1
51,KC
0 0 0 0 1 0 0 0 1 0 0 1 1
0 0 0 0 0 0 0 0 1 0 0 1 1
0 0 0 0 0 0 0 0 1 0 0 0 1
0 0 0 0 1 0 0 0 1 0 0 1 1
0 0 0 0 0 0 0 0 1 0 0 1 1
0 0 0 0 1 0 0 0 1 0 0 1 1
0 0 0 0 1 0 0 0 1 0 0 1 1
0 0 0 0 1 0 0 0 1 0 0 1 1
0 0 0 0 1 0 0 0 1 0 0 1 1
0 0 0 0 0 0 0 0 1 0 0 1 1
0 0 0 0 0 0 0 0 1 0 0 0 1
*/
