#include <stdio.h>

int newgetline (char *str,const int MAX){
	int i, c;
	for (i = 0; i < MAX-1 && (c = getchar()) != EOF && c != '\n'; ++i, ++str)
		*str = c;
	if (c == '\n')
		*str++ = c;
	*str = '\0';
	return i;
}

#include <ctype.h>

int natoi (char *str){
	int sign;
	int num = 0;
	sign = (*str == '-')? -1 : 1;
	if (*str ==  '-' || *str == '+')
		str++;
	while (isdigit(*str))
		num = num * 10 + (*str++ - '0');
	num = sign * num;
	return num;
}

void reverse (char *str){
	char *temp = str;
	while (*temp != '\n' && *temp != '\0')
		temp++;
	temp--;
	for (; str < temp; ++str, --temp){
		int t = *str;
		*str = *temp;
		*temp = t;
	}
}

void itoa (int num, char *str){
	char *s = str;
	int sign = 0;
	unsigned int i = num;
	if(num < 0){
		i = ~num + 1;
		sign = 1;
	}
	while (i){
		*str++ = i % 10 + '0';
		i /= 10;
	}
	if (sign)
		*str++ = '-';
	*str = '\0';
	reverse (s);
}


int strindex (char *s, char *t){
	int i, j, e;
	for (i = 0; *(s + i) != EOF; ++i){
		for (j = 0, e = i; *(s + e) == *(t + j); ++j, ++e)
			;
		if (!*(t + j))
			return i;
	}
	return -1;
}


#include <stdlib.h>
#define BUFZISE 100
int *buf;
int bufp = 0;

int getch (void);
void ungetch (int);

int getop(char *s){
	if (!bufp)
		buf = malloc(400);
	int i, c;
	
	while ((*s = c = getch()) == ' ' || c == '\t')
		;
	*(s + 1) = '\0';
	if (!isdigit(c) && c != '.')
		return c;
	i = 0;
	if (isdigit(c))
		while (isdigit(*(s + ++i) = c = getch()))
			;
	if (c == '.')
		while (isdigit(*(s + ++i) = c = getch()))
			;
	*(s + i) = '\0';
	if (c != EOF)
		ungetch(c);
	return 1;
}


int getch(void){
	return bufp ? *(buf + --bufp) : getchar();
}
void ungetch(int c){
	if (bufp >= BUFZISE)
		printf ("ungetch: too many characters\n");
	else
		*(buf + bufp++) = c;
}
