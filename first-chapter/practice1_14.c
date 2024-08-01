#include <stdio.h>

int main(){
	int i, count[26], nc;
	char c;

	nc = 0;
	for (i = 0; i < 26; ++i)
		count[i] = 0;
	
	while ((c = getchar())!=EOF){
		if (c >= 'A' && c <= 'Z'){
			++count[c-'A'];
			++nc;
		}
		if (c >= 'a' && c <= 'z'){
			++count[c-'a'];
			++nc;
		}
	}
	c = 'A';
	for (i = 0; i < 26; ++i){
		if (count[i] == 0)
			printf("%c : %d\n", c++, count[i]);
		else{
			printf("%c : ", c++);
			int tmp;
			if (count[i] < 10)
				printf("+");
			for (tmp = 0; tmp < count[i] / 10; ++tmp)
				printf("*");
			printf(" %d\n", count[i]);
		}
	}
	return 0;
}
