#include <stdio.h>

int main(){
    int k , count = 0;
    while(scanf("%d" , &k) != EOF){
        int i , j , l, m = k - 1;

        if(count > 0)
            puts("");

        for(i = 0 ; i < k ; i++){
            printf("1");
            for( j = 1 ; j < k ; j++)
                printf(" %d" , i * m + j + 1);
            puts("");
        }
        for(i = 0 ; i < m ; i++){
            for(j = 0 ; j < m ; j++){
                printf("%d" , i + 2);

                for(l = 0 ; l < m ; l++)
                    printf(" %d" , (j + (l*i))%m + l * m + k + 1 );
                puts("");
            }
        }

        count++;
    }

    return 0;
}
