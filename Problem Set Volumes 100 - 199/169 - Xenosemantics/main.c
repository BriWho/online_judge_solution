#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Word {
    int a[26];
    int start[512];
    int len;
    int count;
};

struct Word words[1026];
int n_words = 0;
char overlap[1026][1026];

int word_cmp(char* w1 , char* w2) {
    int i;
    for(i = 0 ; i < 26 ; i++)
        if(w1 -> a[i] != w2 -> a[i])
            return 1;
    return 0;
}

void insert_new_word(struct Word * w) {
    int i , j;
    for(i = 0 ; i < n_words ; i++ )
        if(words[i].len == w -> len && word_cmp(w , &words[i]) == 0)
            break;
    if( i < n_words )
        for(j = 0 ; j < w -> count ; j++)
            words[i].start[words[i].count++] = w -> start[j]; 
    else
        memcpy(words[n_words++] ,  w , sizeof(struct Word));
}

int filter_repeat_words() {
    int i , n = 0;
    for(i = 0 ; i < n_words ; i++)
        if(words[i].count >= 2)
            memcpy(&words[n++] , &word[i] , sizeof(struct Word));
}

int is_overlap(char* w1 , char * w2 ){
    
}

void filter_overlap_words() {
    int i , j , n = 0; 
    memset( overlap , 0 , sizeof(overlap));
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
        
        int j , k;
        struct Word word;
    
        for(i = 0 ; i < 26 ; i++){
            memset(word , 0 , sizeof(struct Word));
            
            for(j = 0 ; j < m_len ; j++){
                if(msg[j] == 'a' + i) break;
                word.a[msg[j] - 'a']++;
            }
            
            if(j < m_len && j >= 2 && j <= 250){
                word.len = j;
                word.start[0] = 0;
                word.count = 1;
                
                insert_new_word(word);
            }
        }
    
        for(i = 0 ; i < m_len ; i++){

            memset(word , 0 , sizeof(struct Word));
            
            for(j = i + 1 ; j < m_len ; j++){
                if(msg[j] == msg[i]) break;
                word.a[msg[j] - 'a']++;
            }
            
            int len = j - i - 1;
            if(len >= 2 && len <= 250) {
                word.len = len;
                word.start[0] = j;
                word.count = 1;
                
                insert_new_word(word);
            }
            
        }
        
        filter_repeat_words();
        filter_overlap_words();


        for(i = 0 ; i < n_words ; i++){
            int start = words[i].start;
            for(j = 0 ; j < words[i].len ; j++)
                printf("%c" , msg[start + j]);
            printf("\n");
        }
        
        printf("%s\n" , msg);
        
        m_len = 0;
 
    }

    return 0;
}
}
