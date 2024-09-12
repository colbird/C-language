#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000

//int getline(char line[], int max);
//double atof (char str[]);

int main(){
	double sum, atof(char []);
	char line[MAXLINE];
	int new_getline(char line[], int max);

	sum = 0;
	while (new_getline(line, MAXLINE) > 0)
		printf ("\t%g\n", sum += atof(line));
	return 0;
}

int new_getline(char s[], int lim){
	int i = 0;
	char c;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
double atof (char s[]){
	double val, power;
	int i, sign;

	for (i = 0; isspace(s[i]); ++i)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		++i;
	for (val = 0.0; isdigit(s[i]); ++i)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		++i;
	for (power = 1.0; isdigit(s[i]); ++i){
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	return sign * val / power;
}
