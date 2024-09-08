#include <stdio.h>

char lower(char c);

int main(){
	char c = 'A';
	printf ("%c\n", lower(c));
	return 0;
}
char lower (char c){
	return (c >= 'A' && c <= 'z')? c += 'a' - 'A': c;
}
