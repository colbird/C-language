#include <stdio.h>
#include <string.h>

#define MAX 100

void itob (int n, char s[], int b);
void reverse(char s[]);


int main(){
	int num;
	char str[MAX];
	int b;
	scanf("%d",&num);
	scanf("%d",&b);
	itob(num, str, b);
	printf("%s\n", str);
	return 0;
}

void itob (int n, char s[], int b){
	int i, sign;
	unsigned int num;
	if ((sign = n) < 0)
		num = ~n + 1;
	else
		num = n;
	i = 0;
	do{
		if ((num % b) < 10)
			s[i++] = (num % b) + '0';
		else
			s[i++] = (num % b) - 10 + 'A';
	}while ((num /= b)!= 0);
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
