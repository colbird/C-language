#include <stdio.h>

#define IN 1
#define OUT 0

int main(){
	char c, state;
	state = OUT;

	while ((c = getchar())!=EOF){
		if (c == ' ' || c == '\t' || c == '\n'){
			if (state == IN){
				state = OUT;
				printf("\n");
			}
		}
		else{
			state = IN;
			printf("%c", c);
		}
	}
	return 0;
}
