#include <stdio.h>
#include <ctype.h>


#define MAX 12

int newgetline (char line[], int max);
unsigned int htoi (char s[]);

int main(){
	char s[MAX];
	while (newgetline(s, MAX))
		printf("%s%u\n", s, htoi(s));
	return 0;
}

unsigned int htoi(char s[]){
	unsigned int n, i;
	n = 0;
	
	for (i = 0; s[i] != EOF; i++)
		if (s[i] == '0' && (s[i+1] == 'X' || s[i+1] == 'x')){
			for (i+=2; s[i] != EOF; i++){
				if(isdigit(s[i]))
					n = 16 * n + (s[i] - '0');
				else if (islower(s[i]) && s[i] <= 'f')
					n = 16 * n + (s[i] - 'a' + 10);
				else if (isupper(s[i]) && s[i] <= 'F')
					n = 16 * n + (s[i] - 'A' + 10);
				else
					break;
			}
			break;
		}
	return n;
}
int newgetline (char line[], int max){
	int c, i;
	
	for (i = 0; i < max - 1 && (c=getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}
