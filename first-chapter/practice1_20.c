#include <stdio.h>

#define MAXLINE 1000 
int detab (char line[]);
//一个制表符最大为八个空格

int main(){
	int len;
	char line[MAXLINE];

	while (len = detab(line)){
		printf("%s", line);
	}
	return 0;
}
int detab (char line[]){
	int c, i;
	for (i = 0; i < MAXLINE - 1 && (c=getchar())!=EOF &&  c != '\n'; ++i){
		if (c == '\t'){
			int n = i % 8;
			while (n < 8){
				line[i++] = ' ';
				++n;
			}
			i--;
		}
		else
			line[i] = c;
	}
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}
