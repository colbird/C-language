#include <stdio.h>
#include <string.h>

char *alloc(int n);
void afree(char *);

int main(){
	char *name1;
	char *name2;
	name1 = alloc(strlen("dupengjun") + 1);
	name2 = alloc(strlen("dupengxi") + 1);
	name1 = "dupengjun";
	name2 = "dupengxi";
	printf ("%s\n", name1);
	printf ("%s\n", name2);
	afree(name1);
	return 0;
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n){
	if (allocbuf + ALLOCSIZE - allocp >= n){
		allocp += n;
		return allocp - n;
	}else
		return 0;
}

void afree(char *p){
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}
