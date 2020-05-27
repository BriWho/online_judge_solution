#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{ 
	int a;
	struct node* L ,* R;
};

struct node* insert(struct node* root , char* p, int a){
	if(root == NULL){
		root = (struct node*)malloc(sizeof(struct node));
		root -> L = root -> R = NULL;
		root -> a = -1;
	}
	if(p[0] == ')'){
		if(root -> a == -1)
			root -> a = a;
		else if(root -> a > 0)
			root -> a = -2;
	}
	if(p[0] == 'L')
		root -> L = insert(root -> L, p + 1 , a);
	if(p[0] == 'R')
		root -> R = insert(root -> R, p + 1 , a);

	return  root;
}

int iscomplete(struct node* root){
	if(root == NULL) return 1;
	if(root -> a < 0) return 0;
	return iscomplete(root -> L) && iscomplete(root -> R);
}

void depthfirst(struct node* root){
	struct node* queue[256];
	int head = 0 , tail = 0;
	queue[head++] = root;
	while(tail < head){
		struct node* n = queue[tail++];
		if(n -> L != NULL)
			queue[head++] = n -> L;
		if(n -> R != NULL)
			queue[head++] = n -> R;
	}
	for(tail = 0 ; tail < head ; tail++)
		printf("%d%c" , queue[tail] -> a , " \n"[head -1 == tail]);
}

void clean(struct node* root){
	if(root == NULL) return;
	clean(root -> L);
	clean(root -> R);
	free(root);
}

int main(){
	char str[512] , *p;
	struct node* root = NULL;

	while(scanf("%s" ,str ) != EOF){
		if(strcmp("()" , str) == 0){
			if(iscomplete(root))
				depthfirst(root);
			else
				printf("not complete\n");
			clean(root);
			root = NULL;
			continue;
		}

		int a;

		for(p = str ; p[0] != 0 ; p++){
			if(p[0] == '(')
				sscanf(p + 1 , "%d" , &a );
			if(p[0] == ','){
				root = insert(root , p + 1 , a);
				break;
			}
		}
	}

	return 0;
}