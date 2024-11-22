#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct nlist {			/*  链表项  */
	struct nlist *next;	/*  链表中下一表项  */
	char *name;		/*  定义的名字  */
	char *defn;		/*  替换的文本  */
};

#define HASHSIZE	101
#define WORDMAX		100
static struct nlist *hashtab[HASHSIZE];	/*  指针表  */

/*  hash函数: 为字符串s生成散列值  */
unsigned hash(char *s);
/*  lookup函数: 在hashtab中查找s  */
struct nlist *lookup(char *s);
/*  install函数: 将(name, defn)加入到hashtab中  */
struct nlist *install(char *name, char *defn);
/*  undef函数: 删除定义的名字和替换的文本  */
void undef(char *name);
/*  getword函数: 获取单词  */
char getword(char *s, int max);
int getch(void);
void ungetch(int);
void ungetstr(char *);

void getdefn(void);

int main(){
	char c, word[WORDMAX];
	struct nlist *np;
	while ((c = getword(word, WORDMAX)) != EOF){
			if (c == '#')
				getdefn();
			else if ((np = lookup(word)) == NULL)
				printf ("%s", word);
			else
				ungetstr(np->defn);
	}
	return 0;
}

#define LINEMAX	1000
void newgetline(char *s){
	char c;
	while ((c = getch()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
}
/*  getdefn函数: 处理#define 和 #undef  */
void getdefn(void){
	char line[LINEMAX];
	char name[WORDMAX];
	char defn[WORDMAX];
	int i = 0, j = 0;
	newgetline(line);
	switch(line[0]){
		case 'u':
			while (isalnum(line[i]))	//  跳过undef
				i++;
			while (isspace(line[i]))
				i++;
			while (isalnum(line[i]))
				name[j++] = line[i++];
			name[j] = '\0';
			undef(name);
			break;
		case 'd':
			while (isalnum(line[i]))	//  跳过define
				i++;
			while (isspace(line[i]))
				i++;
			while (isalnum(line[i]))
				name[j++] = line[i++];
			name[j] = '\0';
			j = 0;
			while (isspace(line[i]))
				i++;
			while (!isspace(line[i]))
				defn[j++] = line[i++];
			defn[j] = '\0';
			install(name, defn);
			break;
		default:
			printf ("#%s", line);
			break;
	}
}

/*  hash函数: 为字符串s生成散列值  */
unsigned hash(char *s){
	unsigned hashval;

	for (hashval = 0; *s != '\0'; ++s)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}


/*  lookup函数: 在hashtab中查找s  */
struct nlist *lookup(char *s){
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;	//  找到了返回地址
	return NULL;
}


/*  install函数: 将(name, defn)加入到hashtab中  */
struct nlist *install(char *name, char *defn){
	struct nlist *np;
	unsigned hashval;
	/*  为找到  */
	if ((np = lookup(name)) == NULL){
		np = (struct nlist *) malloc (sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else	/*  已存在  */
		free((void *) np->defn);	//  释放前一个defn
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}


/*  undef函数: 删除定义的名字和替换的文本  */
void undef(char *name){
	struct nlist *tp, *pn;
	unsigned hashval = hash(name);
	
	for (tp = NULL, pn = hashtab[hashval]; pn != NULL; pn = pn->next){
		if (strcmp(name, pn->name) == 0)
			break;
		tp = pn;
	}
	if (tp == NULL && pn != NULL)		//  在第一个找到
		hashtab[hashval] = pn->next;
	else if (pn != NULL)			//  在第一后面找到
		tp->next = pn->next;
	else if (pn == NULL)			//  未找到
		return;
	free(pn->name);
	free(pn->defn);
	free(pn);
}

/*  getword函数: 获取单词  */
//char getword(char *s, int limit){
//	char i, c;
//
//	for (i = 0; i < limit - 1 && (c = getch()) != EOF && isspace(c) && c != '\n'; ++i )	/*  读取连在一起的空白字符  */
//		s[i] = c;
//	if (i > 0 || c == '\n'){
//		if (c == '\n'){
//			s[i] = c;
//			i++;
//		}
//		else if (c != EOF)
//			ungetch(c);
//		s[i] = '\0';
//		return *s;
//	}
//	if (isalnum(c) || c == '_'){
//		for ( ; i < limit - 1 && c != EOF && isalnum(c) && c == '_'; ++i){	/*  读取连在一起的字母和数字  */
//			s[i] = c;
//			c = getch();
//		}
//		if (c != EOF)
//			ungetch(c);
//		s[i] = '\0';
//		return s[0];
//	}
//	else{
//		s[i] = c;
//		i++;
//		s[i] = '\0';
//		return s[0];
//	}
//}
char getword(char *s, int limit){
	char i, c;
	c = getch();

	if (isspace(c)){	//  获取连在一起的空白字符
		for (i = 0; i < limit - 1 && c != EOF && isspace(c) && c != '\n'; ++i,(c = getch()))
			s[i] = c;
		if (c == '\n')
			s[i++] = c;
		else if (c != EOF)
			ungetch(c);
		s[i] = '\0';
		return s[0];
	}else if (isalnum(c) || c == '_'){
		for (i = 0; i < limit - 1 && c != EOF && (isalnum(c) || c == '_'); ++i,(c = getch()))
			s[i] = c;
		if (c != EOF)
			ungetch(c);
		s[i] = '\0';
		return s[0];
	}else{
		i = 0;
		s[i++] = c;
		s[i] = '\0';
		return s[0];
	}
}

#define BUFSIZE 100
int buf[BUFSIZE];		//  暂存数组
int sp = 0;			//  暂存数字的角标

int getch(void){
	return sp ? buf[--sp]: getchar();
}
void ungetch(int c){
	if (sp == BUFSIZE)
		printf ("Error: buf too big\n");
	else
		buf[sp++] = c;
}
void ungetstr(char *word){
	int i = 0;
	while (word[i] != '\0')
		i++;
	while (i > 0){
		buf[sp++] = word[--i];
	}

}
