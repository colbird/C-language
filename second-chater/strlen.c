#include <stdio.h>

int newstrlen (char s[]);

int main(){
	char test[20] = "dupengjun";
	printf ("%d\n", newstrlen(test));
	return 0;
}

int newstrlen (char s[]){
	int i;
	i = 0;

	while (s[i] != '\0')
		++i;

	return i;
}
