#include <stdio.h>

#define NUMBER 1

int getype(char *s);
double atof(char *s);
void push(double);
double pop(void);

int main(int argc, char *argv[]){
	int type;
	double op2;
	if (!--argc){				/*  如果argc为1则返回-1  */
		printf ("error: expr 1 1 +\n");
		return -1;
	}
	while (argc-- > 0 && (type = getype(*++argv))){
		switch (type){
			case NUMBER:
				push (atof(*argv));
				break;
			case '+':
				push (pop() + pop());
				break;
			case '*':
				push (pop() * pop());
				break;
			case '/':
				op2 = pop();
				if (op2)
					push(pop() / op2);
				else
					printf ("error: zero divisor\n");
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			default:
				printf ("error: %s\n", *argv);
				break;
		}
	}
	op2 = pop();
	printf ("%.8g\n", op2);
	return (int)op2;
}

#include <ctype.h>

int getype(char *s){
	if (!isdigit(*s) && *s != '.'){
		if ((*s == '-' || *s == '+') && isdigit(*(s+1)))
			return NUMBER;
		return *s;
	}
	else
		return NUMBER;
}

double atof(char *s){
	int i, sign, power;
	double num = 0;
	sign =  power = 1;
	
	for (i = 0; isspace(*(s + i)); ++i)
		;
	sign = *(s + i) == '-'? -1: 1;
	if (*(s + i) == '-' || *(s + i) == '+')
		++i;
	while (isdigit(*(s + i)))
		num = num * 10 + (*(s + i++) - '0');
	if (*(s + i) == '.')
		while (isdigit(*(s + i))){
			power *= 10;
			num = num * 10 + (*(s + i++) - '0');
		}
	return num / power * sign;
}

#define NUMAX 100		/*  栈的容量  */

double numbers[NUMAX];
int sp = 0;

void push(double f){
	if (sp < NUMAX)
		numbers[sp++] = f;
	else
		printf ("error: stack full, can't push %g\n", f);
}
double pop(void){
	if (sp > 0)
		return numbers[--sp];
	else {
		printf ("error: stack empty\n");
		return 0.0;
	}
}
