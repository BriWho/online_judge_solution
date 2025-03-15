#include <stdio.h>
#include <string.h>

const int coin_value[6] = { 1, 2, 4, 10, 20 , 40 };
int dp[128][128];

int greedy_change(int amount){
    int i , n = 0;
    for(i = 5 ; i >= 0 ; i--){
        n += amount/coin_value[i];
        amount %= coin_value[i];
    }
    return n;
}

int change_coins(int amount, int n_coins[]) {
    int i , j;
    int total = 0;
    int coins[128];
    
    memset( dp , 0 , sizeof(dp));
    
    for(i = 0 ; i < 6; i++)
        for(j = 0 ; j < n_coins[j] ; j++)
            coins[total++] = coin_value[i];
            
    for(i = 1; i <= total ; i++)
        for(j = coins[i] ; j <= amount; j++)
            if()
    
    return dp[total][amount];
}


int main() {
    int n_coins[6];
    int amount;
    
    while(scanf("%d%d%d%d%d%d", 
        &n_coins[0] ,&n_coins[1], &n_coins[2] , 
        &n_coins[3] , &n_coins[4], &n_coins[5]) == 6) {
        
        if(n_coins[0] == 0 && n_coins[1] == 0 && n_coins[2] == 0 &&
            n_coins[3] == 0 && n_coins[4] == 0 && n_coins[5] == 0 )
            break;
        
        int a, b;
        scanf("%d.%d" , &a , &b);
        
        amount = (a * 100 + b)/5;
        
        printf("%d\n" , change_coins(amount, n_coins));
            
    }

    return 0;
}
