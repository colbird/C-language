#include <stdio.h>

int strcmp(char *s, char *t);

int main(){
	char *s = "xxx";
	char *t = "look";
	printf("%d\n", strcmp(s, t));
	return 0;
}

int strcmp(char *s, char *t){
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}
