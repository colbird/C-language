#include <stdio.h>

char *pstrncpy(char *, char *, int);
char *pstrncat(char *, char *, int);
int pstrncmp(char *, char *, int);

int main(){
	char str[10] = "xxx";
	char *str2 = "xxxlook";
	int temp = pstrncmp(str,str2,4);
	printf ("%s\n", str);
	printf ("%s\n", str2);
	printf ("%d\n", temp);
	return 0;
}
/* strncpy函数: 将字符串t的前n个字符复制到s中,s以\0结尾 */
char *pstrncpy(char *s, char *t, int n){
	while (n-- && (*s++ = *t++))
		;
	if (!n)
		*s = '\0';
	return s;
}
/* strncat函数: 将字符串t的前n个字符放s的结尾后面, s以\0结尾 前提是s足够大 */
char *pstrncat(char *s, char *t, int n){
	while (*s)
		++s;
	while (n && (*s++ = *t++))
		n--;
	if (!n)
		*s = '\0';
	return s;
}
/* strncmp函数: 根据s前n个字符按照字典顺序小于、等于或大于t的结果分别返回负整数、0或正整数*/
int pstrncmp(char *s, char *t, int n){
	for ( ; n && *s == *t; ++s, ++t, --n)
		if (n == 1)
			return 0;
	return *s - *t;
}
