#include <stdio.h>

#define MAXLINE 1000 
int detab (char line[]);
int entab (char line[]);

int main(){
	int len;
	char line[MAXLINE];

	while (len = entab(line)){
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
int entab (char line[]){
	int i, n, c;
	
	i = n = 0;

	while (i < MAXLINE - 1 && (c=getchar())!=EOF && c != '\n'){
		if (c == ' '){
			++n;
			if (n/8){
				line[i++] = '\t';
				n = 0;
			}
		}
		else{
			while(i < MAXLINE - 1 && n){
				line[i++] = '*';
				--n;
			}
			line[i++] = c;
		}
	}
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;	
}
