#include <stdio.h>
#define MAX_SUM 100 
#define MAX 20000
#define min(a,b) ((a < b)? a :b)
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
    int i , j , k;
    int dp[2][128];
    int* cur_dp = dp[0];
    int* pre_dp = dp[1];
    int min_change = MAX;
    
    for(i = 0 ; i <= MAX_SUM ; i++)
        cur_dp[i] = MAX;

    cur_dp[0] = 0;
    for(i = 0 ; i < 6 ; i++){
        for(j = 0 ; j < n_coins[i] ; j++){
            
            int* tmp_dp = cur_dp;
            cur_dp = pre_dp;
            pre_dp = tmp_dp;
    
            for(k = 0 ; k< coin_value[i] ; k++)
                cur_dp[k] = pre_dp[k];
            for(k = coin_value[i] ; k <= MAX_SUM ; k++)
                cur_dp[k] = min(pre_dp[k] , pre_dp[k - coin_value[i]] + 1);
        }
    }
    
    for(i = amount ; i <= MAX_SUM; i++){
        min_change = min(min_change , cur_dp[i] + greedy_change(i - amount));
    }

    return min_change;
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
        
        printf("%3d\n" , change_coins(amount, n_coins));
            
    }

    return 0;
}
