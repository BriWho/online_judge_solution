#include <stdio.h>
#include <string.h>
#include <limits.h>

enum OPERATION {
    NONE ,
    INSERT ,
    DELETE ,
    CHANGE
};

int main() {
    char input[32] , target[32];
    int cost[32][32];
    int op[32][32];
    char buffer[1024];
    int i , j , k;

    while(scanf("%s" , input) == 1) {
        if(strcmp("#" , input) == 0)
            break;
        scanf("%s" , target);

        int n = strlen(input);
        int m = strlen(target);

        cost[0][0] = 0 , op[0][0] = NONE;
        
        for(j = 1 ; j <= m ; j++)
            cost[0][j] = j, op[0][j] = INSERT;
            
        for(i = 1 ; i <= n ; i++){
            cost[i][0] = i , op[i][0] = DELETE;
            for(j = 1 ; j <= m ; j++){
                int min_cost = INT_MAX;
                
                if(cost[i][j-1] + 1 < min_cost)
                    min_cost = cost[i][j-1] + 1 , op[i][j] = INSERT;
                if(cost[i-1][j] + 1 < min_cost)
                    min_cost = cost[i-1][j] + 1 , op[i][j] = DELETE;
                if(input[i-1] == target[j-1]){
                    if(cost[i-1][j-1] < min_cost)
                        min_cost = cost[i-1][j-1] , op[i][j] = NONE;
                } else {
                    if(cost[i-1][j-1] + 1 < min_cost)
                        min_cost = cost[i-1][j-1] + 1, op[i][j] = CHANGE; 
                }
                    
                cost[i][j] = min_cost;
            }
        }
        
        i = n , j = m , k = cost[n][m];
        
        buffer[k * 4] = 0;
        while(k > 0){
            switch(op[i][j]){
                case NONE:
                    i--, j--;
                    break;
                case CHANGE:
                    i--, j--, k--;
                    buffer[k * 4] = 'C';
                    buffer[k * 4 + 1] = target[j];
                    buffer[k * 4 + 2] = (j+1)/10 + '0';
                    buffer[k * 4 + 3] = (j+1)%10 + '0';
                    break;
                case DELETE:
                    i--, k--;
                    buffer[k * 4] = 'D';
                    buffer[k * 4 + 1] = input[i];
                    buffer[k * 4 + 2] = (j+1)/10 + '0';
                    buffer[k * 4 + 3] = (j+1)%10 + '0';
                    break;
                case INSERT:
                    j-- , k--;
                    buffer[k * 4] = 'I';
                    buffer[k * 4 + 1] = target[j];
                    buffer[k * 4 + 2] = (j+1)/10 + '0';
                    buffer[k * 4 + 3] = (j+1)%10 + '0';
                    break;
                default:
                    break;
            }
        }
        
        printf("%sE\n" , buffer);
        
    }

    return 0;
}
