#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAXOP	100
enum status { NUMBER = '0', PRINT, COPY, SWAP, DELETE, HELP, HISTORY, FUNCTION };

int getop (char []);
void push (double);
double pop (void);
void valcom(int n);
double function(char []);

double op2, op3;
int a;
double history[MAXOP];
void variable(char []);
double Var[26];
char var;

int main(){
	int type, his;
	int n;
	int status = 0;
	char s[MAXOP];

	for (int i = 0; i < 26; ++i)
		Var[i] = 0.0;

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				status = 0;
				push(atof(s));
				break;
			case PRINT: case COPY:
			case SWAP: case DELETE:
			case HISTORY:
				status = 1;
				valcom(type);
				break;
			case HELP:
				status = 1;
				if (n != HELP){
					printf ("  P\tprint\n");
					printf ("  C\tcopy\n");
					printf ("  S\tswap\n");
					printf ("  D\tdelete\n");
					printf ("  H\thistory\n");
					printf ("  s\tsin\n");
					printf ("  e\texp\n");
					printf ("  p\tpow\n");
				}
				break;
			case FUNCTION:
				status = 0;
				push(function(s));
				break;
			case '$':
				status = 0;
				variable(s);
				break;
			case '+':
				status = 0;
				push(pop() + pop());
				break;
			case '*':
				status = 0;
				push(pop() * pop());
				break;
			case '-':
				status = 0;
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				status = 0;
				op2 = pop();
				if (!op2)
					printf("error: zore divisor\n");
				else
					push(pop() / op2);
				break;
			case '%':
				status = 0;
				op2 = pop();
				if (op2 != 0.0)
					push((int)pop() % (int)op2);
				else 
					printf("error: zore divisor\n");
				break;
			case '=':
				status = 1;
				pop();
				if (islower(var))
					Var[var-'a'] = pop();
				else  if (isupper(var))
					Var[var-'A'] = pop();
				break;
			case '\n':
				if (!status){
					printf("\t%.8g\n", history[a] = pop());
					++a;
				}
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
void variable(char s[]){
	if (islower(s[0]))
		push(Var[s[0]-'a']);
	else if (isupper(s[0]))
		push(Var[s[0]-'A']);
	var = s[0];
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
		case HISTORY:

			if (a){
				int i;
				printf ("History\n");
				printf ("+-----------------------------------------\n");
				for (i = 0; i < a; ++i)
					printf ("|%3d\t%.8g\n", i + 1, history[i]);
				printf ("+-----------------------------------------\n");
			}
			else
				printf ("erorr: history empty\n");
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


#include <string.h>

int getch(void);
void ungetch(int);

int getop(char s[]){
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;	
	s[1] = '\0';
	if (c == '$'){
		s[0] = getch();
		return c;
	}
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
			case 'H':
				return HISTORY;
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

char buf = 0;

int getch(void){
	char c;
	if (buf)
	 	c = buf;
	else
		c = getchar();
	buf = 0;
	return c;
}
void ungetch(int c){
	if (!buf)
		buf = c;
	else 
		printf ("erorr: buf in null\n");
}
