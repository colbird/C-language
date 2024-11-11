#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN	100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int tokentype;			/*  最后一个记号的类型  */
char token[MAXTOKEN];		/*  最后一个记号字符串  */
char name[MAXTOKEN];		/*  标记符名  */
char datatype[MAXTOKEN];	/*  数据类型为char, int 等  */
char out[1000];			/*  输出串  */

int main(){			/*  将声明转换为文字描述  */
	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF){	/*  该行的第一个记号是数据类型  */
		strcpy(out,  token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				sprintf(temp, "(*%s)", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf ("invalid input at %s\n", token);
		printf("%s\n");
	}
	return 0;
}

void dcl(void){
	int ns;

	for (ns = 0; gettoken() == '*'; )
		++ns;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer ot");
}
void dirdcl(void){
	int type;

	if (tokentype == '(') {
		dcl();
		if (tokentype != ')')
			printf ("error: missing  )\n");
	} else if (tokentype == NAME)
		strcpy(name, token);
	else
		printf ("error: expected name or (dcl)\n");
	while ((type=gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}
int gettoken(void){
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy (token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalpha(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

#define VALMAX 100
int bufp[VALMAX];
int sp = 0;

int getch(void){
	return sp > 0 ? bufp[--sp] : getchar();
}

void ungetch(int c){
	if (sp > VALMAX)
		printf ("error: bufp\n");
	else 
		bufp[sp++] = c;
}
