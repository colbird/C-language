#include <unistd.h>
#include <stdio.h>

#undef getchar

int getchar(void){
	static char buf[BUFSIZ];
	static char *bufp = buf;
	static int n = 0;
	
	if (n == 0){	/*  缓冲区为空  */
		n = read(0, buf, sizeof buf);
		bufp = buf;
	}
	return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}

int main(){
	printf ("%c\n", getchar());
}
