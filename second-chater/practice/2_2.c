#include <stdio.h>

#define LIM 100

int main(){
	int i, c;
	char s[LIM];

	for (i = 0; i < LIM - 1; ++i){
		if ((c = getchar()) == '\n')
			break;
		if (c == EOF)
			break;
		s[i] = c;
	}
	printf ("%s", s);
	return 0;
}
