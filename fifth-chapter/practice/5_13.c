#include <stdio.h>
#include <stdlib.h>
#define MAXLINE		100		//  最大长度100
#define LOSTLINE	10		//  没有参数默认显示最后10行

int ngetline (char*, int);
int natoi (char*);
void tail(char*[], char*, int, int);

int main(int argc, char *argv[]){
	char str[MAXLINE];
	int len;
	int nline = LOSTLINE;

	if (argc-- > 1){					//  获取参数n
		if (*(++argv)[0] == '-'){
			nline =  (natoi (++argv[0]));
		}
		else{
			printf ("error: tail -n\n");
			printf ("             ^\n");
			printf ("        number\n");
			return -1;
		}
	}
	char **val = malloc (nline * sizeof(char*));
	//char *val[10];
	while (len = ngetline(str, MAXLINE)){
		tail(val, str, len, nline);
	}
	int i;
	for (i = 0; i < nline; ++i)
		if (*val != NULL)
			printf ("%s", *val++);
	return 0;
}

int ngetline (char *s, int maxline){
	int i, c;
	for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		*s++ = c;
	if (c == '\n'){
		*s++ = c;
		++i;
	}
	*s = '\0';
	return i;
}

int natoi (char *s){
	int i = 0;
	while (*s)
		i = i * 10 + (*s++ - '0');
	return i;
}

#include <string.h>

void tail(char *val[], char *str, int len, int line){
	static int head = 0, status = 0;
	int i;
	char *t = malloc(len+1);
	strcpy(t,str);
	if (head == line){
		free(*val);			//  释放最先到的地址
		for (i = 1; i < line; ++i){
			*(val+i-1) = *(val+i);
		}
		*(val+head-1) = t;
	}
	else{
		*(val+head++) = t;
	}
}
