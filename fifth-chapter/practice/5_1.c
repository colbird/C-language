#include <stdio.h>

int getint(int *);


int main(){
	int i;
	int type;
	while ((type = getint(&i)) != EOF)
		if (type)
			printf ("%d\n", i);
	return 0;
}

#include <ctype.h>

int getch (void);
void ungetch (int);
void del (void);

int getint(int *pn){
	int c, temp, sign;

	while (isspace(c = getch()))	//跳过字符前的空白
			;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
		return 0;
	sign = (c == '-') ? -1 : 1;

	if (c == '-' || c == '+'){
		if (!isdigit(temp = getch())){
			if (temp == '\n'){
				del();
				return 0;
			}
			ungetch(c);
			return 0;
		}
		else
			c = temp;
	}

	for (*pn = 0.0; isdigit(c); c = getchar())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;

	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFMAX 10
int buf[BUFMAX];
int bufp = 0;

int getch (void){
	return (bufp) ? buf[--bufp] : getchar();
}
void ungetch(int n){
	if (bufp < BUFMAX)
		buf[bufp++] = n;
	else 
		printf("erorr: too many characters\n");
}
void del(void){
	bufp = 0;
}
