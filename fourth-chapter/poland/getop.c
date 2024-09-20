#include <ctype.h>
#include "calc.h"

int getch(void);
void ungetch(int);

int getop(char s[]){
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;	
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-' && c != '+')
		return c;
	i = 0;
	if (c == '-' || c == '+'){
		if (!isdigit(s[++i] = c = getch())){
			ungetch(c);
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
		ungetch(c);
	return NUMBER;
}
