#include <stdio.h>
#include <string.h>

#define MAXLINES 5000			/*  待排序的最大行数  */
char *lineptr[MAXLINES];		/*  指向文本行的指针  */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void nqsort(void *lineptr[], int left, int right, int mod,
		int (*comp)(void *,void *));
int numcmp(char *, char *);

int main(int argc, char *argv[]){
	int nlines;			/*  读入的输入行数  */
	int numeric = 0;		/*  若进行数值排序, 则numeric为1  */
	int mod = 0;			/*  mod == 0 为默认的顺序(递增) mod == 1 为逆序(递减)  */

	while (argc-- > 1){
		if (*(++argv)[0] == '-')
			while (*++argv[0] != '\0'){
				switch (*argv[0]){
					case 'n':
						numeric = 1;
						break;
					case 'r':
						mod = 1;
						break;
					default:
						printf("error: illegal option %c\n", argv[0]);
						return 1;
						break;
				}
			}
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		nqsort((void **) lineptr, 0, nlines-1, mod,
			//(int (*)(void*,void*))(numeric ? numcmp : strcmp));
			(numeric ? (int (*)(void*,void*))numcmp : (int (*)(void*,void*))strcmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf ("input too big to sort\n");
		return 1;
	}
}
#include <stdlib.h>

#define MAXLEN 1000			/*  每个输入文本行的最大长度  */
int ngetline(char *, int);

int readlines(char *lineptr[], int maxlines){
	int len, nlines;
	char *p, line[MAXLEN];
	
	nlines = 0;
	while ((len = ngetline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

int ngetline (char *s, int maxlen){
	int i, c;
	for (i = 0; i < maxlen-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

void writelines (char *lineptr[], int nlines){
	int i;

	for (i = 0; i < nlines; i++){
		printf ("%s\n", lineptr[i]);
		//free (lineptr[i]);
	}
}

void nqsort(void *v[], int left, int right,int mod, int (*comp)(void *, void *)){
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;

	if (mod) {
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) > 0)
			swap(v, ++last, i);
	}
	else {
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	}
		swap(v, left, last);
	nqsort(v, left, last-1, mod, comp);
	nqsort(v, last+1, right, mod, comp);
}

int numcmp(char *s1, char *s2){
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j){
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
