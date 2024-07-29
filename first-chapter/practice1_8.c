#include <stdio.h>

int main(){
	int nb, nt, nl, c;
	nb = nt = nl = 0;

	while ((c = getchar())!=EOF)
		if (c == '\n')
			++nl;
		else if ( c == '\t')
			++nt;
		else if ( c == ' ')
			++nb;
	printf("nb=%d\nnt=%d\nnl=%d\n", nb, nt, nl);
	return 0;
}
