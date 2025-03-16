#include <stdio.h>
#include <string.h>
#define toIdx(a) (a - 'A')
#define toAlpha(i) (i + 'A')

int edge[32][32];
int n_edge[32];
int light[32];

int flee(int M , int T){
    int i;
    for(i = 0 ;i < n_edge[M] ; i++){
        int e = edge[M][i];
        if(!light[e] && e != T)
            return e;
    }
    return -1;
}

int main(){
    
    char input[256];
    int k;
    int i;
    int M, T;
    
    while(scanf("%s" , input) == 1) {
        if(strcmp(input , "#") == 0)
            break;
            
        memset(n_edge , 0 , sizeof(n_edge));
        memset(light , 0 , sizeof(light));
        
        int cur, state = 0;
        for(i = 0 ; i < strlen(input) ;i++){
            if(input[i] == '.')
                break;
            if(input[i] == ';')
                state = 0 , i++;
            if(input[i] == ':')
                state = 1 , i++;
            if(state == 0)
                cur = toIdx(input[i]);
            if(state == 1)
                edge[cur][n_edge[cur]++] = toIdx(input[i]);
        }
        
        scanf("%s" , input);
        M = toIdx(input[0]);
        scanf("%s" , input);
        T = toIdx(input[0]);
        scanf("%d" ,&k);
        
        int counter = 0, next;
        while((next = flee(M , T)) >= 0){
            T = M;
            M = next;
            counter++;
            if(counter%k == 0){
                printf("%c " , toAlpha(T));
                light[T] = 1;
            }
        }

        printf("/%c\n" , toAlpha(M));
    }
    return 0;
}
