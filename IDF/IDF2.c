#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	char *string;
	int cnt;
	struct node *lnode;
	struct node *rnode;
};
int search(struct node *root, char *string){
        if(root == NULL) return 0;
        struct node *ptr = root;
        while(ptr){
                if(strcmp(string, ptr->string) > 0){
                        ptr = ptr->rnode;
                }
                else if(strcmp(string, ptr->string) < 0){
                        ptr = ptr->lnode;
                }
                else{
                        ptr->cnt++;
                        return 1;
                }
        }
        return 0;
}
struct node *insert(struct node *root, char *string){
	char track;
        struct node *trace = root;
	struct node *tmp;
	if(root == NULL){
		tmp = (struct node *)malloc(sizeof(struct node));
		tmp->string = strdup(string);
		tmp->cnt = 1;
		tmp->rnode = NULL;
		tmp->lnode = NULL;
		return tmp;
	}
	while(trace){
		tmp = trace;
		if(strcmp(string, trace->string) > 0){
			track = 'r';
			trace = trace->rnode;
		}
		else if(strcmp(string, trace->string) < 0){
			track = 'l';
			trace = trace->lnode;
		}
	}
	if(track == 'r'){
		tmp->rnode = insert(tmp->rnode, string);
	}	
	else tmp->lnode = insert(tmp->lnode, string);
	return root;
}

int put(struct node **arr, struct node *root, int position){
        int p=position;
        struct node *ptr = root;
        while(ptr){
                arr[p] = ptr;
                p++;
                ptr = ptr->lnode;
        }
        return p;
}
void traverse(struct node *root,int *max){
	if(root == NULL) return;
	traverse(root->lnode, max);
	traverse(root->rnode, max);
	if(root->cnt > *max) {
		*max = root->cnt;
	}
} 
/*void traverse(struct node *root, int *max)          //find max
  {
          if(root == NULL) return;
          traverse(root->lnode, max);
          traverse(root->rnode, max);
          if(root->cnt > *max) *max = root->cnt;
  }*/

struct node *Max(struct node **spa, struct node *root, int max){
	int find=0;
	find = put(spa, root, 0);
	while(find >= 0){
		find--;
		if(spa[find]->cnt == max){
			spa[find]->cnt = 0;
			return spa[find];
		}
		else if(spa[find]->rnode){
			find = put(spa ,spa[find]->rnode, find);
		}
	}
	return NULL;
}


/*int main()
{
        int i=0, fet = 0, fett = 0;
        char *line = (char *)malloc(sizeof(char)*50000);
        char *word;
        char temp[] = " ";
        struct node *root = NULL;
        struct node *root2 = NULL;
        struct node *arr = (struct node *)malloc(sizeof(struct node *)*1024);
        while(fgets(line, 50000, stdin)){
                line[strlen(line)-1] = '\0';
                if(*line){
                        word = strtok(line, temp);
                        while(word){

                                fet = search(root2, word);

                                if(fet==1){
                                    fet=0;
                                }
                                else{
                                    root2 = insert(root2, word);
                                    fett = search(root, word);
                                    if(fett==0) root = insert(root, word);
                                    else fett = 0;
                                }
                                word = strtok(NULL, temp);
                        }
                        free(root2);
                        root2 = NULL;
                }
        }

        struct node *ptr;
        int max;
        for(i=0; i<10; i++){
                max = 0;
                traverse(root, &max);
                ptr = Max(arr, root, max);
                printf("%s\n", ptr->string);
        }
}*/



int main(){
        int i=0, fet = 0, fett = 0;
        char *line = (char *)malloc(sizeof(char)*50000);
        char *word;
        char temp[] = " ";
        struct node *root = NULL;
        struct node *root2 = NULL;
        struct node *arr = (struct node *)malloc(sizeof(struct node *)*1024);
        while(fgets(line, 50000, stdin)){
                line[strlen(line)-1] = '\0';
                if(*line){
                        word = strtok(line, temp);
                        while(word){

                                fet = search(root2, word);

                                if(fet==1){
                                    fet=0;
                                }
                                else{
                                    root2 = insert(root2, word);
                                    fett = search(root, word);
                                    if(fett==0) root = insert(root, word);
                                    else fett = 0;
                                }
                                word = strtok(NULL, temp);
                        }
                        free(root2);
                        root2 = NULL;
                }
        }
        struct node *ptr;
        int max;
        for(i=0; i<10; i++){
                max = 0;
                traverse(root, &max);
                ptr = Max((struct node **)arr, root, max);
                printf("%s\n", ptr->string);
        }
}

