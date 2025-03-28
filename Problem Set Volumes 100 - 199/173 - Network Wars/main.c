#include <stdio.h>
#include <string.h>

int main(){
    char input[256];
    int e[26][26];
    char p[2] , l[2];
    int P_visited[26] , L_visited[26];

    while(scanf("%s" , input) != EOF){
        if(strcmp(input , "#") == 0)
            break;

        memset(e , 0 , sizeof(e));
        memset(P_visited , 0 , sizeof(P_visited));
        memset(L_visited , 0 , sizeof(L_visited));

        int state = 0 , node = -1;
        int i , len = strlen(input);
        for(i = 0 ; i < len ; i++){
            if(input[i] == ':') state = 1;
            if(input[i] == ';') state = 0;
            if(input[i] == '.') break;
            if('A' <= input[i] && input[i] <= 'Z'){
                if(state == 0){
                    node = input[i];
                } else {
                    e[node-'A'][input[i] - 'A'] = 1;
                    e[input[i] - 'A'][node -'A'] = 1;
                }
            }
        }
        scanf("%s %s" , p , l);
        int P = p[0] - 'A' , L = l[0] - 'A';
        int P_traped = 0 , L_traped = 0;

        while(P != L && !P_traped && !L_traped && !P_visited[L]){
            P_visited[P] = L_visited[L] = 1;
            for(i = 1 ; i < 26 ; i++){
                int next = (P + i) % 26;
                if(e[P][next] && !P_visited[next] && !L_visited[next]){
                    P = next;
                    break;
                }
                if(i == 25)
                    P_traped = 1;
            }

            
            for(i = 1 ; i < 26 ; i++){
                int next = (L - i + 26) % 26;
                if(e[L][next] && !L_visited[next]){
                    L = next;
                    break;
                }
                if(i == 25)
                    L_traped = 1;
            }

        }

        int status[4] = { P_traped , L_traped , P == L  , P != L && P_visited[L] };
        char* names[4] = { "Paskill" , "Lisper" , "Both" , "Lisper" };
        char* actions[4] = { "trapped" , "trapped", "annihilated" , "destroyed"};
        char nodes[4] = { P + 'A' , L + 'A' , P + 'A' , L + 'A'};
        int first = 1;

        for(i = 0 ; i < 4 ; i++ ){
            if(status[i]){
                if(first) first = 0; 
                else printf(" ");
                printf("%s %s in node %c" , names[i] , actions[i] , nodes[i]);
            }
        }
        puts("");
    }
    return 0;
}
