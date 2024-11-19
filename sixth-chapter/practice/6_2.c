#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct tnode {
	char *word;
	int match;
	struct tnode *left;
	struct tnode *right;
};

#define WORDMAX 100
#define	YES	1
#define NO	0

struct tnode *addtree(struct tnode *, char *, int, int *);
void treeprint(struct tnode *);
int compare(struct tnode *, char *, int, int *);
int getword(char *, int);
int newatoi(char *);			


int main(int argc, char *argv[]){
	struct tnode *root = NULL;		//  根节点
	int fount = NO;
	char word[WORDMAX];		//  读到的单词 长度限定为100
	int num = (--argc && ((**++argv) == '-'))? newatoi(++*argv) : 6;
	printf("%d\n", num);
	while (getword(word, WORDMAX) != EOF){
		if (isalpha(*word) && strlen(word) >= num)
			root = addtree(root, word, num, &fount);
		fount = NO;
	}
	treeprint(root);
	return 0;
}

int newatoi(char *s){
	int sum;
	for (sum = 0; *s != '\0'; ++s)
		sum = sum * 10 + (*s - '0');
	return sum;
}

struct tnode *talloc(void);
char *newstrdup(char *);

struct tnode *addtree(struct tnode *p, char *word, int num, int *fount){
	int cont;
	if (p == NULL){
		p = talloc();
		p->word = newstrdup(word);
		p->match = *fount;
		p->left = p->right = NULL;
	}
	else if ((cont = compare(p, word, num, fount)) < 0)
		p->left = addtree(p->left, word, num, fount);
	else if (cont > 0)
		p->right = addtree(p->right, word, num, fount);
	return p;
}

#include <stdlib.h>

struct tnode *talloc(void){
	return (struct tnode *)malloc(sizeof(struct tnode));
}
char *newstrdup(char *s){
	char *p = (char *)malloc(strlen(s)+1);
	char *t = p;
	if (p != NULL)
		strcpy(p, s);
	return p;
}

int compare(struct tnode *p, char *s, int num, int *fount){
	char *word = p->word;
	int i;
	for (i = 0; *word == *s; ++i, ++s, ++word)
		if (*s == '\0')
			return 0;
	if (i >= num){
		p->match = YES;
		*fount = YES;
	}
	return *s - *word;
}


int getword(char *word, int lim){
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	char temp;

	while (isspace(c = getch()))		//  跳过空格
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)){			//  如果不是字母 返回c
		switch(c){
			case '_':
			case '#':
			case '<':
				while (!isspace(c = getch()) && c != EOF)
					*w++ = c;
					*w = '\0';
					return word[0];
				break;
			case '\"':
				while ((c = getch()) != '\"' && c != EOF)
					*w++ = c;
					*w++ = c;
					*w = '\0';
					return word[0];
				break;
			case '/':
				if ((c = getch()) == '/'){
					while ((c = getch()) != '\n')
						;
					*w = '\0';
					return w[0];
				}
				else if (c == '*'){
					while ((c = getch()) != EOF){
						if (c == '*' && (c = getch())== '/'){
							*w = '\0';
							return w[0];
						}
					}
					if (c == EOF)
						return EOF;
					*w = '\0';
					return w[0];
				}
				else{
					*w = '\0';
					ungetch(c);
					return w[0];
				}
				break;
			default:
				*w = '\0';
				return c;
				break;
		}
	}
	for (; --lim > 0; w++)
		if(!isalnum(*w = getch())){
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100

int buf[BUFSIZE];
int sp = 0;

int getch(void){
	return sp ? buf[--sp]: getchar();
}

void ungetch(int s){
	if (sp == BUFSIZE)
		printf ("error: ungetch too big\n");
	else
		buf[sp++] = s;
}

void treeprint(struct tnode *p){
	if (p != NULL){
		treeprint(p->left);
		if (p->match)
			printf("%s\n", p->word);
		treeprint(p->right);
	}
}
