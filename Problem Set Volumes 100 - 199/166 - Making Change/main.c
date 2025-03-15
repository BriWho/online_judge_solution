#include <stdio.h>
#include <limits.h>
#define MAX_VAL 100 

const int coin_value[6] = { 1, 2, 4, 10, 20 , 40 };


int greedy_change(int amount){
    int i , n = 0;
    for(i = 5 ; i >= 0 ; i--){
        n += amount/coin_value[i];
        amount %= coin_value[i];
    }
    return n;
}

int change_coins(int amount, int n_coins[]) {
    int i , j, k ;
    int dp[128];
    int min_change = INT_MAX;
    
    for(i = 0 ; i <= MAX_VAL ; i++)
        dp[i] = INT_MAX;
    dp[0] = 0;
    
    for(i = 0 ; i < 6; i++){
        for(j = 0 ; j < n_coins[j] ; j++)
            for(k = coin_value[i]; k <= MAX_VAL ; k++ )
                if(dp[k - coin_value[i]] + 1 < dp[k] ){
                     dp[k] = dp[k - coin_value[i]] + 1 ;     
                }
    }
    
    for(i = 0 ; i <= amount; i++)
        printf("%d%c" , dp[i] , " \n"[i==amount]);
  /*  
    for(i = amount; i <= MAX_VAL ; i++){
        int change = dp[i] + greedy_change(i - amount);
        if(change < min_change)
            min_change = change;
    }*/
    
    return dp[amount];
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
