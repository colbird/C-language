#include <stdio.h>

void qsort (int [], int, int);

int main(){
	int v[10] = { 9, 7, 5, 3, 1, 0, 8, 6, 4, 2 };
	qsort(v,0,9);
	int i = 10;
	while (i){
		printf ("  %d", v[10 - i]);
		--i;
	}
	return 0;
}

void qsort (int v[], int left, int right){
	int i, last;
	void swap (int v[], int i, int j);
	
	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (v[i] < v[left])
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);

}

void swap (int v[], int i, int j){
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;

}
