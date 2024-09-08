#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned int y);

int main(){
	printf("%u\n", setbits(227, 4, 3, 224));
	return 0;
}

// 1110 0011
// 1110	0000
unsigned setbits(unsigned x, int p, int n, unsigned int y){
	return (x >> (p + 1 - n) | y >> (p + 1)) << (p + 1 - n) | (~(~0 << (p + 1 - n)) & x );
}
