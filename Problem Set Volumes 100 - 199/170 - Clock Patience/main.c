#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char rank , suit;
} Card;

typedef struct {
    Card cards[4];
    int top;
} Pile;


int is_empty(Pile* p){
    return p -> top == 0;
}

Card pop(Pile* p) {
    if(p -> top > 0) 
        return p -> cards[--(p -> top)];
    Card tmp = { .rank = 0 , .suit = 0 };
    return tmp;
}

void push(Pile* p , Card c){
    if(p -> top < 4)
        p -> cards[(p -> top)++] = c;
}


int rank2Num(char rank) {

    switch(rank){
    case 'A': return 0;
    case 'T': return 9;
    case 'J': return 10;
    case 'Q': return 11;
    case 'K': return 12;
    default: return rank - '1';
    }
}


int main() {
    int i , j;
    char input[3];
    Card cards[52], pick;
    Pile piles[13];
    
    while(scanf("%s" , input)!=EOF){
        if(input[0] == '#') break;
        cards[0].rank = input[0];
        cards[1].suit = input[1];
        for(i = 1 ; i < 52 ; i++){
            scanf("%s" , input);
            cards[i].rank = input[0];
            cards[i].suit = input[1];
        }
        memset(piles , 0 , sizeof(piles));
        for(i = 51 ; i >= 0 ; i--)
            push(&piles[12 - (i%13)] , cards[i]);
        int count = 0, next_pile = 12;
        while( !is_empty(&piles[next_pile])){
            pick = pop(&piles[next_pile]);
            next_pile = rank2Num(pick.rank);
            count++;
        }
        printf("%02d,%c%c\n" , count , pick.rank , pick.suit);
    }

    return 0;
}
