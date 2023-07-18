#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAXLEN 30002
#define MAXNUM 1000

struct BSnode
{
	char *key;
	unsigned int cnt;
	struct BSnode *L;
	struct BSnode *R;
};

struct BSnode *insert(struct BSnode *root, char *key)
{
	struct BSnode *q;
	if(root == NULL)
	{
		q = (struct BSnode *)malloc(sizeof(struct BSnode));
		q->key = strdup(key);
		q->cnt = 1;
		q->L = NULL;
		q->R = NULL;
		return q;
	}
	char RL = '\0';
	struct BSnode *p = root;
	while(p)
	{
		q = p;
		if(strcmp(key, p->key) > 0)
		{
			RL = 'R';
			p = p->R;
		}
		else if(strcmp(key, p->key) < 0)
		{
			RL = 'L';
			p = p->L;
		}
	}
	if(RL == 'R') q->R = insert(q->R, key);
	else q->L = insert(q->L, key);
	return root;
}

int find(struct BSnode *root, char *key)
{
	if(root == NULL) return FALSE;
	struct BSnode *p = root;
	while(p)
	{
		if(strcmp(key, p->key) > 0)
		{
			p = p->R;
		}
		else if(strcmp(key, p->key) < 0)
		{
			p = p->L;
		}
		else 
		{
			p->cnt++;
			return TRUE;
		}
	}
	return FALSE;
}

void traversal(struct BSnode *root, unsigned int *max)		//find max
{
	if(root == NULL) return;
	traversal(root->L, max);
	traversal(root->R, max);
	if(root->cnt > *max) *max = root->cnt;
}

int push(struct BSnode **arr, struct BSnode *root, int pos)
{
	int i=pos;
	struct BSnode *ptr = root;
	while(ptr)
	{
		arr[i] = ptr;
		i++;
		ptr = ptr->L;
	}
	return i;
}


struct BSnode *findMaxNode(struct BSnode **arr, struct BSnode *root, unsigned int max)		//find max
{
	int i=0;
	i = push(arr, root, 0);
	while(i >= 0)
	{
		i--;
		if(arr[i]->cnt == max) {arr[i]->cnt = 0; return arr[i];}
		else if(arr[i]->R) i = push(arr, arr[i]->R, i);
	}
	return NULL;
}


int main()
{
	int len, i, asize=0, pos, get = FALSE, get2 = FALSE;
	char *line = (char *)malloc(sizeof(char)*MAXLEN);
	char *wd;
	char d[] = " ";
	struct BSnode *root = NULL;
	struct BSnode *root2 = NULL;
	struct BSnode *arr = (struct BSnode *)malloc(sizeof(struct BSnode *)*MAXNUM);

	i=0;
	while(fgets(line, MAXLEN, stdin))
	{
		len = strlen(line);
		if(line[len-1] == '\n') line[len-1] = '\0';
		
		if(*line)
		{
			wd = strtok(line, d);
			while(wd)
			{
				
				get = find(root2, wd);
				
				if(!get) 
				{
					root2 = insert(root2, wd);
					
					get2 = find(root, wd);
					if(!get2) root = insert(root, wd);
					else get2 = FALSE;
				}
				else get = FALSE;

				wd = strtok(NULL, d);
			}

			free(root2);
			root2 = NULL;
		}
	}
	
	struct BSnode *ptr;
	unsigned int max;
	for(i=0; i<10; i++)
	{
		max = 0;
		traversal(root, &max);
		ptr = findMaxNode(arr, root, max);
		printf("%s\n", ptr->key);
	}
	free(arr);
	free(root);
	free(line);
	
	return 0;
}
