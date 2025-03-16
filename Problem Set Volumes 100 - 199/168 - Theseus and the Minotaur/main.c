#include <stdio.h>
#include <string.h>

#define MAX_N 32

int flee(int edge[MAX_N][MAX_N] , int M , int T){
    int i;
    for(i = 0 ;i < MAX_N ; i++)
        if(edge[M][i] && i != T)
            return i;
    return -1;
}

int main(){
    
    char input[256];
    int edge[MAX_N][MAX_N];
    int k;
    int i;
    int M, T;
    
    while(scanf("%s" , input) == 1) {
        if(strcmp(input , "#") == 0)
            break;
            
        memset(edge , 0 , sizeof(edge));
            
        for(i = 0 ; i < strlen(input) ;i++){
            int cur = i;
            i++;
            if(input[i] == ':'){
                i++;
                while(input[i] != ';' && input[i] != '.'){
                    edge[input[cur] - 'A'][input[i] - 'A'] = 1;
                    i++;
                }
            }
        }
        scanf("%s" , input);
        M = input[0] - 'A';
        scanf("%s" , input);
        T = input[0] - 'A';
        scanf("%d" ,&k);
        
        int counter = k, next;
        while((next = flee(edge, M , T)) >= 0){
            if(counter == 0){
                printf("%c " , T + 'A');
                for(i = 0 ; i < MAX_N ; i++)
                    edge[i][T] = 0;
                counter = k;
            }
            counter--;
            T = M;
            M = next;
        }
        
        if(counter == 0){
            printf("%c " , T + 'A');
        }
        
        printf("/%c\n" , M + 'A');
    }
    return 0;
}
