#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum { NONE , PROFILE , TITLE };
#define MAX_N_KEYWORDS 128
#define MAX_N_PROFILES 64
#define MAX_N_TITLES 256

int pair_of_keywords_profile_map[MAX_N_KEYWORDS][MAX_N_KEYWORDS][MAX_N_PROFILES];
int pair_of_keywords_profile_count[MAX_N_KEYWORDS][MAX_N_KEYWORDS];
char keywords[MAX_N_KEYWORDS][MAX_N_KEYWORDS];
int n_keywords = 0;

int find_keyword_idx(char word[128]){
    int i;
    for( i = 0 ; i < n_keywords ; i++)
        if(strcmp(keywords[i] , word) == 0)
            return i;
    return -1;
}

int main(){
    char input[128];

    int thresholds[MAX_N_PROFILES];
    int n_profiles = 0;
    int result[MAX_N_PROFILES][MAX_N_TITLES];
    int n_titles = 0;

    int state = NONE;
    int profile_keywords_idx[MAX_N_KEYWORDS];
    int n_profile_keywords;
    int title_keywords_idx[MAX_N_KEYWORDS];
    int n_title_keywords;

    memset(pair_of_keywords_profile_map , 0 , sizeof(pair_of_keywords_profile_map));
    memset(pair_of_keywords_profile_count , 0 , sizeof(pair_of_keywords_profile_count));
    memset(result , 0 , sizeof(result));

    while(scanf("%s" , input) != EOF){
        if(strcmp(input , "#") == 0){
            int i;
            printf("n %d\n" , n_profiles);
            for(i = 1 ; i <= n_profiles ; i++){
                printf("%d:" , i);
                int j , first = 1;
                for(j = 1; j <= n_titles ; j++){
                    if(result[i][j]){
                        if(first) printf(" ") , first = 0;
                        else printf(",");
                        printf("%d" , j );
                    }
                }
                puts("");
            }
            break;
        }
        if(input[1] == ':'){
            if(input[0] == 'P'){
                scanf("%d" , &thresholds[++n_profiles]);
                n_profile_keywords = 0;
                state = PROFILE;
            }
            if(input[0] == 'T'){
                n_title_keywords = 0;
                n_titles++;
                state = TITLE;
            }
        } else {
            if(state == PROFILE){
                int i , idx = find_keyword_idx(input);
                if(idx < 0) {
                    idx = n_keywords;
                    strcpy(keywords[n_keywords++] , input);
                }
                for(i = 0 ; i < n_profile_keywords ; i++){
                    int old_keyword_idx = profile_keywords_idx[i];
                    int profile_count = pair_of_keywords_profile_count[old_keyword_idx][idx];
                    pair_of_keywords_profile_map[old_keyword_idx][idx][profile_count] = n_profiles;
                    pair_of_keywords_profile_count[old_keyword_idx][idx]++;

                    profile_count = pair_of_keywords_profile_count[idx][old_keyword_idx];
                    pair_of_keywords_profile_map[idx][old_keyword_idx][profile_count] = n_profiles;
                    pair_of_keywords_profile_count[idx][old_keyword_idx]++;
                }
                profile_keywords_idx[n_profile_keywords++] = idx;

            }
            if(state == TITLE){
                int i , len = strlen(input);
                if(input[len-1] == '|'){
                    input[--len] = 0;
                    state = NONE;
                }

                char word[128];
                int word_len = 0;

                for(i = 0 ; i < len; i++){
                    if(isalpha(input[i]))
                        word[word_len++] = tolower(input[i]);
                }
                word[word_len] = 0;

                if(word_len == 0) continue;

                int j , idx = find_keyword_idx( word);

                for(i = 0 ; idx >= 0 && i < n_title_keywords; i++){
                    int old_keyword_idx = title_keywords_idx[i];
                    if(old_keyword_idx <= 0) continue;
                    for(j = 0 ; j < pair_of_keywords_profile_count[old_keyword_idx][idx]; j++){
                        int profile_idx = pair_of_keywords_profile_map[old_keyword_idx][idx][j];
                        if(n_title_keywords - i > thresholds[profile_idx])
                            result[profile_idx][n_titles] = 1;
                    }
                }

                title_keywords_idx[n_title_keywords++] = idx;

            }
        }

    }

    return 0;

}
