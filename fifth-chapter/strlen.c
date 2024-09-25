#include <stdio.h>

int new_strlen(char *);

int main(){
	char s[10] = "dupengjun";
	int i;
	i = new_strlen(s);
	printf ("s = %s\n", s);
	printf ("i = %d\n", i);
	return 0;
}

int new_strlen(char *s){
	int i;
	for (i = 0; *s != '\0'; s++)
		i++;
	return i;
}
