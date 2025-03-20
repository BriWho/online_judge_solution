#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Word {
    int a[26];
    int start[512];
    int len;
    int count;
};

struct Word words[1026];
struct Word* repeat_words[1026];
struct Word* true_words[1026];
int n_words;

int cmp(const void* a , const void* b) {
    struct Word* A = *(struct Word**)a , *B = *(struct Word**)b;
    int a_last = A -> start[0] + A -> len;
    int b_last = B -> start[0] + B -> len; 
    if(a_last == b_last) return 0;
    else if(a_last > b_last) return 1;
    else return -1;
}

int word_cmp(struct Word* a , struct Word* b) {
    int i;
    for(i = 0 ; i < 26 ; i++)
        if(a -> a[i] != b -> a[i])
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
        memcpy(&words[n_words++] ,  w , sizeof(struct Word));
}


int is_overlap(struct Word* a , struct Word * b ){
    int a_idx = 0, b_idx = 0;

    while( a_idx < a -> count &&  b_idx < b -> count ) {
        int a_start = a -> start[a_idx];
        int b_start = b -> start[b_idx];
        if(a_start <= b_start) {
            if(b_start < a_start + a -> len)
                return 0;
            a_idx++;
        } else {
            if(a_start < b_start + b -> len)
                return 0;
            b_idx++;
        }
    }

    return 1;
}


int main() {
    char buf[64];
    char msg[1024];
    
    int m_len = 0;
    
    while(fgets(buf , sizeof(buf) , stdin) != NULL) {
        if(buf[0]=='#')
            break;
        int i , j , k;
        int b_len = strlen(buf);
        for(i = 0 ; i < b_len; i++)
            if(islower(buf[i]))
                msg[m_len++] = buf[i];
        msg[m_len] = 0;
        if(b_len >= 2 && buf[b_len - 2] == '-') 
            continue;
        n_words = 0;

        struct Word word;
    
        for(i = 0 ; i < 26 ; i++){
            memset(&word , 0 , sizeof(struct Word));
            
            for(j = 0 ; j < m_len ; j++){
                if(msg[j] == 'a' + i) break;
                word.a[msg[j] - 'a']++;
            }
            
            if(j < m_len && j >= 2 && j <= 250){
                word.len = j;
                word.start[0] = 0;
                word.count = 1;
                
                insert_new_word(&word);
            }
        }
        for(i = 1 ; i < m_len ; i++){

            memset(&word , 0 , sizeof(struct Word));
            
            for(j = i ; j < m_len ; j++){
                if(msg[j] == msg[i-1]) break;
                word.a[msg[j] - 'a']++;
            }
            
            int len = j - i;
            if(len >= 2 && len <= 250) {
                word.len = len;
                word.start[0] = i;
                word.count = 1;
                
                insert_new_word(&word);
            }
            
        }

        int n_repeat_words = 0 , n_true_words = 0;

        for(i = 0 ; i < n_words ; i++)
            if(words[i].count >= 2)
                repeat_words[n_repeat_words++] = &words[i];
        for(i = 0 ; i < n_repeat_words ; i++){
            for(j = 0 ; j < n_repeat_words ; j++ )
                if(i != j && is_overlap(repeat_words[i] , repeat_words[j]) == 0){
                    true_words[n_true_words++] = repeat_words[i];
                    break;
                }
        }

        qsort(true_words , n_true_words , sizeof(struct Word*) , cmp);

        for(i = 0 ; i < n_true_words ; i++){
            int s = true_words[i] -> start[0];
            for(j = 0 ; j < true_words[i] -> len ; j++)
                putchar(msg[s + j]);
            puts("");
        }
        puts("*");
        
        m_len = 0;
 
    }

    return 0;
}
