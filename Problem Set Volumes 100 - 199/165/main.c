#include <stdio.h>
#include <string.h>

char dp[16][256];
int max_stamps[16];
int H, K, N;

int cont_seq(int stamps[], int idx) {
    int i, j , k;
    memset(dp, 0 , sizeof(dp));
    dp[0][0]=1;
    for(i = 1;i <= H; i++){
        memcpy(dp[i], dp[i-1], sizeof(char) * stamps[idx] * i);
        for(j = 0; j <= idx ;j++)
            for(k = stamps[j]; k <= stamps[idx]*i;k++)
                dp[i][k] = dp[i-1][k-stamps[j]];
    }

    int val = 0;
    while(dp[H][val] != 0)
        val++;
    return val;

}

void dfs(int stamps[], int idx , int max) {

    if( idx == K ) {
        if( max > N){
            memcpy(max_stamps, stamps, sizeof(int) * K);
            N = max;
        }
        return;
    }

    int i;
    for(i=stamps[idx-1]+1;i<= max+1;i++){
        stamps[idx]=i;
        dfs(stamps, idx+1, cont_seq(stamps, idx));
    }

}

int main() {
    int stamps[16];
    int i;
    while(scanf("%d %d", &H, &K)==2){
        if(H==0 && K==0){
            break;
        }
        stamps[0] = 1;
        N = 0;
        dfs(stamps, 1, H);

        for(i=0; i<H ;i++){
            printf("%3d", max_stamps[i]);
        }
        printf("->%3d\n" , N );
    }

    return 0;
}