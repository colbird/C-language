#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct tnode {			/*  树的节点  */
	char *word;		/*  指向单词的指针  */
	int count;		/*  单词出现的次数  */
	struct tnode *left;	/*  左子节点  */
	struct tnode *right;	/*  右子节点  */
};

#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int main(){
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

struct tnode *talloc(void);
char *newstrdup(char *);

struct tnode *addtree(struct tnode *p, char *w){
	int cond;

	if (p == NULL) {		/*  该单词是一个新单词  */
		p = talloc();
		p->word  = newstrdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left,w);
	else
		p->right = addtree(p->right,w);
	return p;
}

void treeprint(struct tnode *p){
	if (p!= NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

#include <stdlib.h>

struct tnode *talloc(void){
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *newstrdup(char *s){
	char *p;

	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

int getword(char *word, int lim){
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while (isspace(c = getch()))            //  跳过空格
	        ;
	if (c != EOF)
	        *w++ = c;
	if (!isalpha(c)){                       //  如果不是字母 返回c
	        *w = '\0';
	        return c;
	}
	for (; --lim > 0; w++)
	        if(!isalnum(*w = getch())){
	                ungetch(*w);
	                break;
	        }
	*w = '\0';
	return word[0];
}

#define  BUFZISE 100

int buf[BUFZISE];
int sp = 0;

int getch(void) {
	return sp ? buf[--sp]: getchar();
}
void ungetch(int c){
	if (sp == BUFZISE)
		printf ("error: ungetch too big\n");
	else
		buf[sp++] = c;
}
