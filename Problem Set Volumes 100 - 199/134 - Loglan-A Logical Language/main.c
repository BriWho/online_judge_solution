#include<stdio.h>
#include<string.h>
#include<stdlib.h>

enum GRAMS { UNKNOWN , A , MOD , BA , DA , LA ,
	NAM , PREDA , SENTENCE , PREDCLAIM , PREDS ,
	PREDNAME , PREDSTRING , STATEMENT , VERBPRED
};

int vowel[26] = { 1 , 0 , 0 , 0, 1, 
	0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };

enum GRAMS whichsymbol(char* str){
	int i , len = strlen(str);
	if(vowel[str[len-1] - 'a'] == 0)
		return NAM;

	switch(len){
	case 1: return A;
	case 2: 
		switch(str[0]){
			case 'g' :	return MOD;
			case 'b' :	return BA;
			case 'd' :	return DA;
			case 'l' :	return LA;
		}
		break;
	case 5:
		return !vowel[str[0] - 'a'] && !vowel[str[3] - 'a'] && 
		(vowel[str[1] - 'a'] != vowel[str[2] - 'a']) ? PREDA : UNKNOWN;
	}

	return UNKNOWN;
}

int Loglan(int n , enum GRAMS stack[512]){
	if(stack[0] == UNKNOWN)
		return 0;
	int i , nxt[512];

	for(i = 0 ; i < n ; i++)
		nxt[i] = i + 1;
	nxt[n-1] = -1;

	for(i = 0 ; i != -1 ; i = nxt[i]){
		if(stack[i] == PREDA){
			while(nxt[i] != -1 && stack[nxt[i]] == PREDA)
				nxt[i] = nxt[nxt[i]];
			stack[i] = PREDSTRING;
		}
	}

	for(i = 0 ; i != -1 ; i = nxt[i]){
		if(nxt[i] == -1) break;
		if(stack[i] == LA && stack[nxt[i]] == PREDSTRING)
			nxt[i] = nxt[nxt[i]], stack[i] = PREDNAME;
		if(stack[i] == MOD && stack[nxt[i]] == PREDSTRING)
			nxt[i] = nxt[nxt[i]], stack[i] = VERBPRED;
	}

	for(i = 0 ; i != -1 ;){
		if(nxt[i] == -1 || nxt[nxt[i]] == -1) 
			break;
		if(stack[i] == PREDSTRING && stack[nxt[i]] == A && stack[nxt[nxt[i]]] == PREDSTRING)
			stack[i] = PREDSTRING , nxt[i] = nxt[nxt[nxt[i]]];
		else
			i = nxt[i];
	}

	for(i = 0 ; i != -1 ; i = nxt[i]){
		if(stack[i] == NAM)
			stack[i] = PREDNAME;
		if(stack[i] == PREDSTRING)
			stack[i] = PREDS;
	}

	for(i = 0 ; i != -1 ; i= nxt[i]){
		if(nxt[i] == -1 || nxt[nxt[i]] == -1)
			break;
		if(stack[i] == PREDNAME){
			if(stack[nxt[i]] == BA && stack[nxt[nxt[i]]] == PREDS)
				stack[i] = PREDCLAIM , nxt[i] = nxt[nxt[nxt[i]]];
			if(stack[nxt[i]] == VERBPRED && stack[nxt[nxt[i]]] == PREDNAME)
				stack[i] = STATEMENT , nxt[i] = nxt[nxt[nxt[i]]];
		}
	}

	for(i = 0 ; i != -1 ; i= nxt[i]){
		if(nxt[i] == -1) break;
		if(stack[i] == DA && stack[nxt[i]] == PREDS)
			stack[i] = PREDCLAIM , nxt[i] = nxt[nxt[i]];
		if(stack[i] == PREDNAME && stack[nxt[i]] == VERBPRED)
			stack[i] = STATEMENT , nxt[i] = nxt[nxt[i]];
	}

	for(i = 0 ; i != -1 ; i = nxt[i]){
		if(stack[i] == STATEMENT || stack[i] == PREDCLAIM)
			stack[i] = SENTENCE;
	}

	return nxt[0] == -1 && stack[0] == SENTENCE;
}

int main(){
	enum GRAMS stack[512];
	char input[128];
	int n = 0;

	while(scanf("%s" , input)!=EOF){
		if(strcmp(input , "#") == 0) break;
		int len = strlen(input);
		int end = input[len - 1] == '.';
		if(end)	input[--len] = 0;
		
		if((stack[n++] = whichsymbol(input)) == UNKNOWN)
			stack[0] = UNKNOWN;

		if(end) {
			printf("%s\n" , Loglan(n , stack)? "Good": "Bad!" );
			n = 0;
		}
	}
	return 0;
}
