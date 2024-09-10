#include <stdio.h>
#include <ctype.h>

#define MAX 1000

void expand (char s1[], char s2[]);

int main(){
	char s1[MAX] = "-a-z0-9A-Z-";
	char s2[MAX];
	expand (s1, s2);
	printf ("%s", s1);
	putchar('\n');
	printf ("%s", s2);
	putchar('\n');
	return 0;
}

void expand (char s1[], char s2[]){
	int i, j, y;
	for (i = j = 0; s1[i] != '\0'; i++){
		if (s1[i] == '-'){
			if((isdigit(s1[i-1]) && isdigit(s1[i+1])) ||
			   (islower(s1[i-1]) && islower(s1[i+1])) ||
			   (isupper(s1[i-1]) && isupper(s1[i+1])) ){
				for (y = 0; y < (s1[i+1] - s1[i-1]); ++y)
					s2[j++] = s2[j-1]+1;
				i++;
			}
			else
				s2[j++] = s1[i];
		}
		else
			s2[j++] = s1[i];
	}
	s2[j] = '\0';
}

