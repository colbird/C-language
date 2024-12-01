#include <stdio.h>
#include <stdlib.h>

#define MAXOP	100
#define NUMBER	'0'

int getop (char []);
void push (double);
double pop (void);

int main(){
	int type;
	double op2;
	char s[MAXOP];
	
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (!op2)
				printf("error: zore divisor\n");
			else
				push(pop() / op2);
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf ("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

#define MAXVAL	100

int sp = 0;
double val[MAXVAL];

void push(double f){
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void){
	if (sp > 0)
		return val[--sp];
	else {
		printf ("error: stack empty\n");
		return 0.0;
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[]){
	int c, i, rc;
	static char lastc[] =" ";

	sscanf(lastc, "%c", &c);
	lastc[0] = ' ';		//  清除lastc
	while ((s[0] = c) == ' ' || c == '\t')
		if (scanf("%c", &c) == EOF)
			c = EOF;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;	//  不是数
	i = 0;
	if (isdigit(c)) //  收集整数部分
		do {	
			rc = scanf("%c", &c);
			if (!isdigit(s[++i] = c))
				break;
		} while (rc != EOF);
	if (c == '.')	//  收集小数部分
		do {
			rc = scanf("%c", &c);
			if (!isdigit(s[++i] = c))
				break;
		} while (rc != EOF);
	s[i] = '\0';
	if (rc != EOF)
		lastc[0] = c;
	return NUMBER;

}
//int getop(char s[]){
//	int i, c;
//
//	while ((s[0] = c = getch()) == ' ' || c == '\t')
//		;	
//	s[1] = '\0';
//	if (!isdigit(c) && c != '.')
//		return c;
//	i = 0;
//	if (isdigit(c))
//		while (isdigit(s[++i] = c = getch()))
//			;
//	if (c == '.')
//		while (isdigit(s[++i] = c = getch()))
//			;
//	s[i] = '\0';
//	if (c != EOF)
//		ungetch(c);
//	return NUMBER;
//}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c){
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
