#include <stdio.h>

int bitcount (unsigned int x);

int main(){
	int n = bitcount (29);
	printf("%d\n", n);
	return 0;
}
int bitcount (unsigned int x){
	int count;
	for (count = 0; x; ++count)
		x &= x - 1;
	return count;
}
