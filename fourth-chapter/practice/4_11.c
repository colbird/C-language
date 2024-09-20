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
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push((int)pop() % (int)op2);
			else 
				printf("error: zore divisor\n");
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
#define BUFSIZE 100

int getch(void);

int getop(char s[]){
	int i, c;
	static int lastc = 0;
	if (!lastc)
		c = getch();
	else{
		c = lastc;
		lastc = 0;
	}

	while ((s[0] = c) == ' ' || c == '\t')
		c = getch();	
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-' && c != '+')
		return c;
	i = 0;
	if (c == '-' || c == '+'){
		if (!isdigit(s[++i] = c = getch())){
			lastc = c;
			return s[0];
		}
	}
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		lastc = c;
	return NUMBER;
}


int getch(void){
	return getchar();
}
