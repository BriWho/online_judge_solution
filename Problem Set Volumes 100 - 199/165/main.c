#include <stdio.h>

char dp[16][256];

int lar_cont_seq(int H, int stamps[], int idx) {
    int i, j , k;
    memset(dp, 0 , sizeof(dp));
    dp[0][0]=1;
    for(i = 1;i <= H; i++){
        memcpy(dp[i], dp[i-1], sizeof(char) * 256);
        for(j = 0; j <= idx ;j++)
            for(k = stamps[j]; k <= stamps[idx]*i;k++)
                dp[i][k] = dp[i-1][k-stamps[j]];
    }

    int v = 0；
    while(dp[H][v] != 0)
        v++;
    return v;

}

int dfs(int H, int K, int stamps[], int idx , int max_stamps[], int h) {

    if( idx == K ) {
        if( h )
        for(i = 0; i<K;i++)
            max_stamps[i]=stamps[i];
        return 0;
    }
    
    int i , max=0;
    for(i=stamps[idx-1]+1;i<= h+1;i++){
        stamps[idx]=i;
        int r = dfs(H, K, stamps, idx+1, max_stamps,lar_cont_seq(H, stamps, idx));
        if(r > max)
            max = r;
    }
    
    return max;
    
}

int n(int H , int K , int max_stamps[]){
    
    int stamps[16];
    stamps[0]=1;
    
    return dfs(H , K , stamps , 1 , max_stamp, H );
    
}

int main() {
    int H, K;
    int max_stamps[16];
    int i;
    while(scanf("%d %d", &H, &K)==2){
        if(H==0 && K==0){
            break;
        }
        
        int r = n(H , K , max_stamps);
        
        for(i=0; i<H ;i++){
            printf("%3d" , max_stamps[i]);
        }
        printf("->%3d\n" , r );
    }

    return 0;
}