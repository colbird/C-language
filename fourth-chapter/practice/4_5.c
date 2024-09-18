#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP	100
enum status { NUMBER = '0', PRINT, COPY, SWAP, DELETE, HELP, FUNCTION };

int getop (char []);
void push (double);
double pop (void);
void valcom(int n);
double function(char []);

double op2, op3;

int main(){
	int type, his, n;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case PRINT: case COPY:
			case SWAP: case DELETE:
				valcom(type);
				break;
			case HELP:
				if (n != HELP){
					printf ("  P\tprint\n");
					printf ("  C\tcopy\n");
					printf ("  S\tswap\n");
					printf ("  D\tdelete\n");
					printf ("  s\tsin\n");
					printf ("  e\texp\n");
					printf ("  p\tpow\n");
				}
				break;
			case FUNCTION:
				push(function(s));
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
				if (n != PRINT && n != HELP)
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
				printf ("error: stack can't swap\n");
			break;
		case DELETE:
			sp = 0;
			break;
		default:
			printf ("彩蛋\n");
			break;
	}
}

double function(char s[]){
	switch(s[0]){
	case 's':
		return sin(pop());
		break;
	case 'e':
		return exp(pop());
		break;
	case 'p':
		op2 = pop();
		op3 = pop();
		if (op3 == 0 && op2 <= 0 || op3 < 0 && op2 - (int)op2 > 0)
			printf ("erorr: POW\n");
		else
			return pow(op3, op2);
		break;
	default:
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
			case 'P':
				return PRINT;
				break;
			case 'C':
				return COPY;
				break;
			case 'S':
				return SWAP;
				break;
			case 'D':
				return DELETE;
				break;
			case 's': case 'e': case 'p':
				return FUNCTION;
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
