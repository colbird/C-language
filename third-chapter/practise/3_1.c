#include <stdio.h>

int binsearch (int x, int v[], int n);

int main(){
	int n[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	printf ("%d\n", binsearch (4, n, 10));
	return 0;
}

/*
int binsearch (int x, int v[], int n){
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high){
		mid = (low+high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;	//没找到返回-1
}
*/
int binsearch (int x, int v[], int n){
	int low, mid, high;
	low = 0;
	high = n - 1;
	while (low <= high && v[mid] != x){
		mid = (low+high) / 2;
	
		if (v[mid] > x)
			high = mid - 1;
		else
			low = mid + 1;
	}
	if (v[mid] == x)
		return mid;
	return -1;
}
