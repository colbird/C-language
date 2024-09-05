#include <stdio.h>
#include <limits.h>
#include <float.h>


int main(){
	printf ("signed short int MAX:%d\n", SHRT_MAX);
	printf ("signed short int MIN:%d\n", SHRT_MIN);
	printf ("unsigned short int MAX:%d\n", USHRT_MAX);
	printf ("signed int MAX:%d\n", INT_MAX);
	printf ("signed int MIN:%d\n", INT_MIN);
	printf ("unsigned int MAX:%u\n", UINT_MAX);
	printf ("signed long max:%ld\n", LONG_MAX);
	printf ("signed long min%ld\n", LONG_MIN);
	printf ("unsigned long max%lu\n", ULONG_MAX);
	
	return 0;
}
