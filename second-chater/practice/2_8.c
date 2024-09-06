#include <stdio.h>

unsigned rightrot (unsigned int x, int n);

int main(){
	printf ("%u\n", rightrot((~0 << 1), 3));
	return 0;
}

unsigned rightrot (unsigned int x, int n){
	int i;
	i = n % (sizeof (x) * 8);
	return x << i | (x >> (sizeof(x) * 8) - i);
}
