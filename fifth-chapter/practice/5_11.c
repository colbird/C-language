#include <stdio.h>
#define MAXLINE		1000
#define TABDEFAULET	8

int ngetline (char *, int);
int atoi(char*);
void detab (char*, int, int);
void entab (char*, int, int);

int main(int argc, char* limit[]){
	char str[1000];
	int len = 0;
	while (len = ngetline(str, MAXLINE)){
		if (argc == 2)
			entab (str, len, atoi(*(limit+1)));
		else
			entab (str, len, TABDEFAULET);
		int i = 0;
		while (i++ < 3){
			printf("11111118");
		}
		putchar('\n');
	}
	return 0;
}
int ngetline(char *s, int maxline){
	int i, c;
	for (i = 0; i < maxline-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		*s++ = c;
	if (c == '\n'){
		*s++ = c;
		++i;
	}
	*s = '\0';
	return i;
}

int atoi(char *s){
	int i, sum;
	i = sum = 0;
	while (s[i] != '\0'){
		sum = sum * 10 + (s[i++] - '0');
	}
	return sum;
}

void detab (char *s, int len, int tabsize){
	int i, count;
	count = 0;
	for (i = 0; i < len; ++i){
		if (s[i] == '\t'){
			int t = tabsize-(count % tabsize);
			while(t-- > 0)
				putchar(' ');
			count = 0;
		}
		else{
			putchar(s[i]);
			++count;
		}
	}
}

void entab (char *s, int len, int tabsize){
	int i, space, count, t;
	i = t = space = count = 0;
	while (i < len){
		if (space > 1 && space + (count % tabsize) == tabsize){
			putchar('\t');
			t = space = count = 0;
		}
		else if (s[i] == ' ') {
			space++;
			t = count + 1;
			i++;
		}
		else {
			++count;
			if (t && t == count){
				while (space){
					putchar(' ');
					++count;
					--space;
				}
				t = 0;
			}
			putchar(s[i]);
			++i;
		}
	}
}
