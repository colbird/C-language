#include <stdio.h>

#define MAX 1000

int newgetline(char line[], int max);

int main(){
	int len, state;
	char line[MAX];
	len = state = 0;

	while ((len = newgetline(line, MAX)) > 0)
		if (len > 80){
			if (!state)
				printf ("长度大于80的输入行有:\n");
			printf("%s", line);
			++state;
		}
	if (!state)
		printf("没有长度大于80的输入行\n");
	return 0;
}
int newgetline(char s[], int max){
	int i, c;
	for (i = 0; i < max-1 && (c=getchar())!= EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
