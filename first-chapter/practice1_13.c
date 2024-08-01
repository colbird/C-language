#include <stdio.h>

#define MAX 1000
#define IN 1
#define OUT 0

int main(){
	int wlen[MAX], i;
	char c, state;

	state = OUT;
	for (i = 0; i < MAX; ++i)
		wlen[i] = 0;
	i = 0;
	while ((c = getchar())!=EOF)
		if(c == ' ' || c == '\n' || c == '\t') {
			if (state == IN)
				++i;
			state = OUT;
		}
		else {
			state = IN;
			++wlen[i];
		}
	int j;
	for (j = 0; j < i; ++j){
		int x;
		for (x = 0; x < wlen[j]; ++x)
			printf("*");
		printf("\n");
	}
	return 0;
}
