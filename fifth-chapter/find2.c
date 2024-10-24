#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int ngetline(char *line, int max);

int main(int argc, char *argv[]){
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;

	printf ("%d\n", argc);

	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c){
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf ("find: illegal option %c\n", c);
				argc = 0;
				found = -1;
				break;
			}
	printf ("%d\n", argc);
	if (argc != 1)
		printf ("Usage: find -x -n pattern\n");
	else
		while (ngetline(line, MAXLINE) > 0) {
			++lineno;
			if ((strstr(line, *argv) != NULL) != except){
				if (number)
					printf ("%ld:", lineno);
				printf ("%s", line);
				++found;
			}
		}
	return found;
}
int ngetline(char *line, int max){
	int i, c;
	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		*line++ = c;
	if (c == '\n')
		*line++ = c;
	*line = '\0';
	return i;
}
