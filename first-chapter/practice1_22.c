#include <stdio.h>

#define MAXLINE 1000
#define MAXLEN  10

int newgetline(char line[], int MAX);

int main(){
	int i, status, pos, len;
	char line[MAXLINE];
	while (len = newgetline(line, MAXLINE)){
		pos = 0;	//字符计数
		status = 0;	//空白字符 第一个为1,否则为0
		for (i = 0; i < len; ++i){
			if(line[i] == ' ' || line[i] == '\t' || line[i] == '\n'){
				if (status == 1){
					printf("%c", '\n');
					status = pos = 0;
				}
			}
			else{
				if (pos == MAXLEN){
					printf("%c", '\n');
					pos = 0;
				}
				printf("%c", line[i]);
				status = 1;
				++pos;
			}
		}
	}
	return 0;
}

int newgetline(char line[], int max){
	int c, i;
	
	for (i = 0; i < max - 1 && (c=getchar())!=EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';

	return i;
}
