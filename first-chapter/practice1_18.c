#include <stdio.h>

#define MAX 1000
#define IN 1
#define OUT 0

int ngetline (char line[], int max);
void print (char line[], int len);


int main(){
	int len = 0;
	char line[MAX];
	while (len = ngetline(line, MAX))
		print (line, len);
	return 0;
}
int ngetline (char s[], int max){
	int i;
	char c;
	for (i = 0; i < max -1 && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')	
		s[i++] = c;
	s[i] = '\0';
	return i;
}
void print (char line[], int len){
	int status, i, j;
	status = i = j = 0;
	
	for (i = 0; i < len; ++i){
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'){
			for (j = i + 1, status = IN; status == IN && j < len; ++j)
				if (line[j] != ' ' || line[j] != '\n' || line[j] != '\t')
					status = OUT;
			if(status == IN){
				if (i!=0)
					printf("%c", '\n');
				i = len;
			}
			else{
				while (i < j)
				printf("%c", line[i++]);
				printf("%c", line[i]);
			}
		}
		else
			printf("%c", line[i]);
			
	}
}
