#include <stdio.h>
#include <unistd.h>

#undef getchar



int getchar(void){
	char c;

	return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}

int main(){
	printf ("%c\n", getchar());
	return 0;
}
