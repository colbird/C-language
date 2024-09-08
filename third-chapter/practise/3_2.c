#include <stdio.h>
#define MAX 100

void escape (char s[], char t[]);
void epacse (char s[], char t[]);

int main(){
	char str[MAX];
	char to[MAX] = "dup	ngjun";
	escape(str, to);
	printf ("%s", str);
	return 0;
}

void escape (char s[], char t[]){
	int i, j;
	for (i = j = 0; t[i] != '\0'; ++i)
		switch (t[i]){
		case '\t' :
			s[j++] = '\\';
			s[j++] = 't';
			break;
		case '\n' :
			s[j++] = '\\';
			s[j++] = 'n';
			break;
		default :
			s[j++] = t[i];
			break;
		}
	s[j++] = '\\';
	s[j++] = '0';
	s[j] = '\0';
}
