#include <stdio.h>

void itoa(int, char[]);

int main(){
	int i = -110;
	char s[10];
	itoa(i, s);
	printf ("%d\n", i);
	printf ("%s\n", s);
	return 0;
}

void itoa(int n, char s[]){
	static int i;
	if (n / 10)
		itoa(n / 10, s);
	else{
		i = 0;
		if (n < 0)
			s[i++] = '-';
	}
	if (n > 0)
		s[i++] = n % 10 + '0';
	else
		s[i++] = -n % 10 + '0';
	s[i] = '\0';
}
