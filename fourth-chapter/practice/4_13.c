#include <stdio.h>

void reverse(char []);

int main(){
	char name[20] = "dupengjun";
	reverse(name);
	printf ("%s\n", name);
	return 0;
}

#include <string.h>

void reverse(char s[]){
	void reverser(char [], int, int);
	reverser(s, 0, strlen(s));
}
void reverser(char s[], int i, int len){
	int j, c;
	j = len - (i + 1);
	if (i < j){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		reverser(s, ++i, len);
	}
}
