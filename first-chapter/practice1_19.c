#include <stdio.h>

#define MAX 1000

int newgetline(char line[], int max);
void Preverse(char line[], int len);

int main(){
	char line[MAX];
	int len = 0;
	while (len = newgetline(line, MAX))
		Preverse(line, len);
	return 0;
}
int newgetline(char line[], int max){
	int i, c;
	for (i = 0; i < MAX -1 && (c=getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}
void Preverse(char line[], int len){
	int i;
	for (i = 0; i < (len -2)/2; ++i){
		line[i] ^= line[len-2-i];
		line[len-2-i] ^= line[i];
		line[i] ^= line[len-2-i];
	}
	printf("%s", line);
}
