#include <stdio.h>
#include <string.h>
#include <limits.h>


void itoa (int n, char s[]);
void reverse(char s[]);

int main(){
	int num = INT_MIN;
	char str[100];
	itoa(num, str);
	printf ("%d\n", num);
	printf ("%s", str);
	return 0;
}

void itoa (int n, char s[]){
	int i, sign;
	unsigned int num;
	if ((sign = n) < 0){
		num = ~n + 1;
	else
		num = n;
	}
	i = 0;
	do{
		s[i++] = num % 10 + '0';
	}while (num /= 10);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
void reverse(char s[]){
	int i, j;
	for (i = 0, j = strlen(s) - 1; i < j; ++i, --j){
		s[i] ^= s[j];
		s[j] ^= s[i];
		s[i] ^= s[j];
	}
}
