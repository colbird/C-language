#include <stdio.h>
#include <string.h>

#define MAXLINES 5000		/*  进行排序的最大文本行数  */
#define MAXLEN 1000		/*  每个输入文本行的最大长度  */

char *lineptr[MAXLINES];		/*  指向文本行的指针数组  */

int readlines(char *lineptr[], char *works, int nlines);
void writelines(char *lienptr[], int nlines);

void nqsort(char *lineptr[], int left, int right);

/*  对输入的文本进行排序  */

int main(){
	int nlines;
	char works[MAXLINES*MAXLEN];
	if ((nlines = readlines(lineptr, works,  MAXLINES)) >= 0){
		nqsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input: input too big to sort\n");
		return 1;
	}
}


int ngetline(char *, int);

/*  readlines函数: 读取输入行  */
int readlines(char *lineptr[], char *works, int maxlines){
	char *maxp = works + maxlines * MAXLEN;
	int len, nlines;
	char *p, line[MAXLINES];
	nlines = 0;
	while ((len = ngetline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || !(works + len - maxp))
			return -1;
		else {
			p = works;
			works += len;
			line[len-1] = '\0';	/*  删除换行符  */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}
int ngetline(char *s, int manlen){
	int i = 0, c;
	while ((c = getchar()) != EOF && c != '\n')
		*(s + i++) = c;
	if (c == '\n')
		*(s + i++) = c;
	return i;
}

void writelines(char *lineptr[], int nlines){
	int i;

	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/*  nqsort函数: 按递增顺序对v[left]---v[right]进行排序  */
void nqsort(char *v[], int left, int right){
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[last]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	nqsort(v, left, last-1);
	nqsort(v, left+1, right);
}

/*  swap函数: 交换v[i]和v[j]  */
void swap(char *v[], int i, int j){
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
