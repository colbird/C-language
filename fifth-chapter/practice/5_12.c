#include <stdio.h>
#define MAXLINE		1000
#define MTABDEFAULET	0		//  参数m的默认值为 0
#define NTABDEFAULET	8		//  参数n的默认值为 8

int ngetline (char *, int);
int atoi(char*);
void detab (char*, int, int, int);
void entab (char*, int, int, int);

int main(int argc, char* argv[]){
	char str[1000];
	int len = 0;
	int n,m;

	m = MTABDEFAULET;
	n = NTABDEFAULET;

	while (--argc > 0){
		if (*(++argv)[0] == '-'){
			m = atoi (++argv[0]);
		}
		else if (*(argv)[0] == '+'){
			n = atoi (++argv[0]);
		}
		else {
			printf ("error: %s\ncommand -m +n\n", *argv);
			return -1;
		}
	}
	while (len = ngetline(str, MAXLINE)){
		entab(str, len, m, n);
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

void detab (char *s, int len, int mtab, int ntab){
	int i, count;
	count = 0;
	for (i = 0; i < len; ++i){
		if (s[i] == '\t'){
			if (mtab) {
				int t = mtab-(count % mtab);
				while(t-- > 0)
					putchar(' ');
				count = 0;
				mtab = 0;
			}
			else {
				int t = ntab-(count % ntab);
				while(t-- > 0)
					putchar(' ');
				count = 0;
			}
		}
		else{
			putchar(s[i]);
			++count;
		}
	}
}

void entab (char *s, int len, int mtab, int ntab){
	int i, space, count, t;
	i = t = space = count = 0;
	while (i < len){
		if (mtab > 0){
			if (space > 1 && space + (count % mtab) == mtab){
				putchar('\t');
				t = space = count = 0;
				mtab = 0;
			}
		}
		else if (!mtab){
			if (space > 1 && space + (count % ntab) == ntab){
				putchar('\t');
				t = space = count = 0;
			}
		}
		if (s[i] == ' ') {
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
