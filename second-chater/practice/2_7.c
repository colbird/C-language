#include <stdio.h>

unsigned int invert (unsigned x, int p, int n);

int main(){
	printf ("%u\n", invert(199, 5, 3));
	return 0;
}

unsigned int invert (unsigned x, int p, int n){
	return x ^ ~(~0 << n) << p + 1 - n;
}
