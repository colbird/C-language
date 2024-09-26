#include <stdio.h>

void new_strcpy(char *s, char *t);

int main(){
	char *s;
	new_strcpy(s, "xxxlook");
	printf("%s\n", s);
	return 0;
}

void new_strcpy(char *s, char *t){
	while (*s++ = *t++)
		;
}
