#include <stdio.h>

int main(){
	char c;
	while ((c = getchar())!=EOF){
		if (c == ' '){
			printf(" ");
			while((c = getchar())!=EOF && c == ' ')
				;
		}
		if(c == EOF)
			break;
		printf("%c", c);
	}
	return 0;
}
