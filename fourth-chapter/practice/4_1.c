#include <stdio.h>
#define MAXLINE 1000

int new_getline (char line[], int max);
int strrindex (char sourse[], char searchfor[]);

char pattern[] = "jun";
int main(){
	char line[MAXLINE];
	int found;

	while (new_getline(line, MAXLINE))
		if (strrindex(line, pattern) >= 0){
			printf ("%s", line);
			++found;
		}
	return found;
}

int new_getline(char s[], int mit){
	char c;
	int i = 0;
	while (mit-- > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
int strrindex(char s[], char t[]){
	int i, j, k;
	for (i = 0; s[i] != '\0'; ++i)
		;
	if (!i)
		return -1;
	i-=1;
	for (; i >= 0; --i){
		for (j = i, k = 0; t[k] != '\0' && s[j] ==  t[k]; ++j, ++k)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}
