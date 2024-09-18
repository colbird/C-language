#include <stdio.h>
#include <stdlib.h>

#define MAXOP	100
#define NUMBER	'0'
#define PRINT	'1'
#define COPY	'2'
#define SWAP	'3'
#define DELETE	'4'
#define HELP	'5'


int getop (char []);
void push (double);
double pop (void);
void valcom(int n);


int main(){
	int type, his, n;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case PRINT:
				valcom(type);
				break;
			case COPY:
				valcom(type);
				break;
			case SWAP:
				valcom(type);
				break;
			case DELETE:
				valcom(type);
				break;
			case HELP:
				if (n != HELP){
					printf ("  p\tprint\n");
					printf ("  c\tcopy\n");
					printf ("  s\tswap\n");
					printf ("  d\tdelete\n");
				}
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
				if (n < PRINT || n > HELP)
					printf("\t%.8g\n", pop());
				break;
			default:
				printf ("error: unknown command %s\n", s);
				break;
		}
		n = type;
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

void valcom(int n){
	switch (n){
		case PRINT:
			if (sp > 0)
				printf ("\t%.8g\n", val[sp-1]);
			else 
				printf ("error: stack empty\n");
			break;
		case COPY:
			if (sp > 0)
				val[sp++] = val[sp-1];
			else 
				printf ("error: stack empty\n");
			break;
		case SWAP:
			if (sp > 1){
				val[sp-1] *= val[sp-2];
				val[sp-2] /= val[sp-1];
				val[sp-1] /= val[sp-2];
			}
			else
				printf ("error: stack can't swap");
			break;
		case DELETE:
			sp = 0;
			break;
		default:
			printf ("彩蛋\n");
			break;
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[]){
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;	
	s[1] = '\0';
	if (!isalnum(c) && c != '.' && c != '-' && c != '+')
		return c;
	i = 0;
	if (c == '-' || c == '+'){
		if (!isdigit(s[++i] = c = getch())){
			ungetch(c);
			return s[0];
		}
	}
	if (isalpha(c)){
		switch (c){
			case 'p': case 'P':
				return PRINT;
				break;
			case 'c': case 'C':
				return COPY;
				break;
			case 's': case 'S':
				return SWAP;
				break;
			case 'd': case 'D':
				return DELETE;
				break;
			default:
				return HELP;
				break;
		}
	}
	else{
		if (isdigit(c))
			while (isdigit(s[++i] = c = getch()))
				;
		if (c == '.')
			while (isdigit(s[++i] = c = getch()))
				;
		s[i] = '\0';
		if (c != EOF)
			ungetch(c);
		return NUMBER;
	}
	}

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
