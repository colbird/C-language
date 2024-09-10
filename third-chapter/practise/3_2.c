#include <stdio.h>
#define MAX 100

void escape (char s[], char t[]);
void epacse (char s[], char t[]);

int main(){
	char str[MAX];
	char to[MAX] = "dup	ngjun";
	escape(str, to);
	epacse(to, str);
	printf ("%s", str);
	printf ("\n");
	printf ("%s", to);
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
void epacse (char s[], char t[]){
	int i, j;
	for (i = j = 0; t[i] != '\0'; i++){
		switch (t[i]){
		case '\\' :
			switch (t[i+1]){
			case 't' :
				++i;
				s[j++] = '\t';
				break;
			case 'n' :
				++i;
				s[j++] = '\n';
				break;
			case '0' :
				++i;
				s[j++] = '\0';
				break;
			default :
				s[j++] = t[i++];
				s[j++] = t[i];
				break;
			}
			break;
		default :
			s[j++] = t[i];
			break;
		}
	}
	s[j] = '\0';
}
