#include <stdio.h>

int getint(int *);


int main(){
	int i;
	int type;
	while (type = getint(&i) && type != EOF)
		printf ("%d", i);
	return 0;
}

#include <ctype.h>

int getch (void);
void ungetch (int);

int getint(int *pn){
	int c, sign;

	while (isspace(c = getch()))	//跳过空白
			;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-'){
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+')
		c = getch();
	for (*pn = 0; isdigit(c); c = getchar())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFMAX 10
int buf[BUFMAX];
int bufp = 0;

int getch (){
	return (bufp) ? buf[--bufp] : getchar();
}
void ungetch(int n){
	if (bufp < BUFMAX)
		buf[bufp++] = n;
	else 
		printf("erorr: too many characters\n");
}
