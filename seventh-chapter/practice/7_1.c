#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]){
	int c;
	printf ("%s\n", argv[0]);
	if (!strcmp(argv[0], "lower"))		//  atgv[0] == lower 转换为 小写
		while ((c = getchar()) != EOF)
			putchar(tolower(c));
	else					//  反之 转换为 大写
		while ((c = getchar()) != EOF)
			putchar(toupper(c));
	return 0;
}
