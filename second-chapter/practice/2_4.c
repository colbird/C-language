#include <stdio.h>

void squeeze (char s1[], char s2[]);

int main(){
	char name[20] = "dbupehngjuvnxl";
	char del[] = "bhvlx";
	squeeze (name, del);
	printf ("%s", name);
	return 0;
}
void squeeze (char s1[], char s2[]){
	int i, j;
	for (i = 0; s1[i] != '\0'; ++i){
		for (j = 0; s2[j] != '\0'; ++j){
			if (s1[i] == s2[j]){
				for (int tmp = i; (s1[tmp] = s1[tmp+1]) != '\0'; ++tmp)
					;
				i--;
				break;
			}
		}
	}
}
