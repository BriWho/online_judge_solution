#include <stdio.h>
#include <string.h>
#define N 8
#define max(a,b) ((a > b)?a:b)
#define min(a,b) ((a < b)?a:b)

int board[N][N];
int queens[N][N];

int is_valid(int r, int c){
    int i;
    for(i = 1 ; i <= r ; i++)
        if(queens[r-i][c]) return 0;
    for(i = 1 ; i <= min(r , N - c -1) ; i++)
        if(queens[r-i][c+i]) return 0;
    for(i = 1 ; i <= min(r, c) ; i++)
        if(queens[r-i][c-i]) return 0;
    return 1;
}

int dfs(int r , int score){
    if(r == N) return score;
    int i , max_score = -1;
    for(i = 0 ; i < N ; i++){
        if(is_valid(r , i)){
            queens[r][i] = 1;
            max_score = max( max_score , dfs(r + 1 , score + board[r][i])); 
            queens[r][i] = 0;
        }
    }
    return max_score;
}

int main(){
    
    int i, j;
    int k;

    scanf("%d" , &k);
    while(k--){
        for(i = 0 ; i < N ;i++)
            for(j = 0;j < N ; j++)
                scanf("%d" , &board[i][j]);
        memset(queens , 0 , sizeof(queens));
        
        printf("%5d\n" , dfs(0 , 0));
    }
    
    return 0;
}
