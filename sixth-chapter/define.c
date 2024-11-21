#include <stdio.h>
#include <ctype.h>

struct nlist {			/*  链表项  */
	struct nlist *next;	/*  链表中下一表项  */
	char *name;		/*  定义的名字  */
	char *defn;		/*  替换文本  */
};

#define HASHSIZE	101
#define WORDMAX		100
#define LINEMAX		1000

static struct nlist *hashtab[HASHSIZE];		/*  指针表  */

struct nlist *lookup(char *s);
unsigned hash(char *);
struct nlist *install(char *, char *);
void undef(char *);
int getword(char *, int);
void getdef(char *);
void Error(char *);
int getch();
void ungetch(char);
void unget(char *);


int main(){
	char word[WORDMAX];
	struct nlist *pn;
	while (getword(word, WORDMAX) != EOF){
		if (*word == '#')			//  读取第一个是#的行
			getdef(word);
		else if (isupper(word) && ((pn = lookup(word)) != NULL))		//  单词为大写  搜索定义
			unget(pn->defn);
		else if (pn == NULL)		//  没有定义 报错
			Error(word);
		else
			printf ("%s", word);
	}
	return 0;
}

int newgetline(char *,char *, int);

/*  三种情况
 *  1. #undef
 *  2. #define
 *  3. 其他 例如：#include
 *  */
void getdef(char *s){
	int c;
	char name[WORDMAX];
	char defn[WORDMAX];
	switch (*s+1){
	case 'u':
		while (isspace(c = getch()) && c != '\n')
			;
		if (c == '\n')
			Error(s);
		else {
			ungetch(c);
			if (getword(name, WORDMAX))
				undef(name);
			else
				Error(s);
		}
		break;
	case 'd':
		while (isspace(c = getch()) && c != '\n')
			;
		if (c == '\n')
			Error(s);
		else {
			ungetch(c);
			if (!newgetline(name, defn, LINEMAX))
				install(name, defn);
			else 
				Error(s);
		}
		break;
	default:
		printf("%s",s);
		break;
	}
}

int newgetline(char *name, char *defn, int limit){
	int i, c;
	for (i = 0; i < limit-1 && (c = getch()) != EOF && !isspace(c); ++i)
		*(name+i) = c;
	*(name+i) = c;
	while (isspace(c = getch()) && c != '\n')
		;
	if(c != '\n')
		ungetch(c);
	else
		return 1;
	for (i = 0; i < limit-1 && (c = getch()) != EOF && !isspace(c); ++i)
		*(defn+i) = c;
	*(defn+i) = c;
	return 0;
}

void Error(char *s){
	printf ("Error: %s\n", s);
}

int getword(char *s, int limit){
	int i, c;
	for (i = 0; i < limit - 1 && (c = getch()) != EOF && 
	(isalnum(c) || c == '_'); ++i)
		s[i] = c;
	if (!i)
		s[i++] = c;
	else
		ungetch(c);
	s[i] = '\0';
	return i;
}

#define BUFMAX 100
int sp = 0;
int buf[BUFMAX];

int getch(){
	return sp ? buf[--sp]: getchar();
}
void ungetch(char c){
	if (sp == BUFMAX)
		printf ("Error: ungetch too big\n");
	else
		buf[sp++] = c;
}
void unget(char *s){
	while (*s != '\0'){
		if (sp == BUFMAX)
			printf ("Error: ungetch too big\n");
		else
			buf[sp++] = *s++;
	}
}

/*  hash函数: 为字符串s生成散列值(哈希值)  */
unsigned hash(char *s){
	unsigned hashval;
	
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

#include <stdlib.h>
#include <string.h>

struct nlist *lookup(char *);
char *newstrdup(char *);

/*  install函数: 将(name, defn)加入到hashtab中  */
struct nlist *install(char *name, char *defn){
	struct nlist *np;
	unsigned hashval;
	/*  未找到  */
	if ((np = lookup(name))	== NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = newstrdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else		/*  已存在  */
		free((void *) np->defn);	/*  释放前一个defn  */
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

/*  lookup函数: 在hashtab中查找s  */
struct nlist *lookup(char *s){
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (!strcmp(s, np->name))
			return np;	/*  找到s  */
	return NULL;			/*  未找到s  */
}

char *newstrdup(char *s){
	char *p = malloc(strlen(s)+1);
	strcpy(p, s);
	return p;
}

void undef(char *name){
	struct nlist *t, *p;
	t = NULL;

	for (p = hashtab[hash(name)]; p != NULL; p = p->next){
		if (!strcmp(name, p->next->name))		/*  找到了  */
			break;
		t = p;
	}
	if (p != NULL) {
		if (t == NULL)
			hashtab[hash(name)] = p->next;
		else
			t->next = p->next;
		free((void *) p->name);
		free((void *) p->defn);
		free((void *) p);
	}
}
