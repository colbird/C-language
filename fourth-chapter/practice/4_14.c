#include <stdio.h>

#define swap(t,x,y) {   t _z;	\
			_z = x;	\
			x = y;	\
			y = _z;	}

int main(){
	int t,x,y;
	x = 1;
	y = 0;
	swap(int,x,y);
	printf("%d\n", x);
	printf("%d\n", y);
	return 0;
}
