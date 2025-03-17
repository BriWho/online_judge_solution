#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Word {
    char sorted[256];
    int start[512];
    int end[512];
};

struct Word* words[1024];
int words_count = 0;

struct Word create_word(char* str, int s , int e) {
    
}

void search_word(char* msg) {
    int i , j;
    int len = strlen(msg);
    
    for(i = 0 ; i < len ; i++){
        
    }
}


int main() {
    char buf[64];
    char msg[1024];
    
    int m_len = 0;
    
    while(fgets(buf , sizeof(buf) , stdin) != NULL) {
        if(buf[0]=='#')
            break;
        
        int i, b_len = strlen(buf) - 1;
        if(b_len == 0)
            continue;
        for(i = 0 ; i < b_len; i++)
            if('a' <= buf[i] && buf[i] <= 'z')
                msg[m_len++] = buf[i];
        msg[m_len] = 0;
        if(buf[b_len - 1] == '-') 
            continue;
        
        
        printf("%s\n" , msg);
        
        m_len = 0;
 
    }

    return 0;
}
