#include <stdio.h>
/* 函数strend(s,t): 如果字符串t出现在字符串s的尾部，返回1，否则返回0*/
int strend(char *s, char *t);

int main(){
	char *str = "xxxlook";
	char *s = "look";
	printf("%d\n", strend(str, s));
	return 0;
}

int strend (char *s, char *t){
	while (*s){
		if (*s == *t){
			while(*s == *t){
				if (*t == '\0')
					return 1;
				else{
					++s;
					++t;
				}
			}
		}
		else
			++s;
	}
	return 0;
}
