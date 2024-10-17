#include <stdio.h>
#include <limits.h>
#include "fun.h"

#define LINEMAX 1000

int main(){
	//char str[LINEMAX];
	//int i;
	//while (newgetline(str, LINEMAX)){
	//	i = atoi(str);
	//	printf ("%s", str);
	//	itoa(i,str);
	//	printf ("%s", str);
	//}
	
	//char s1[20] = "xxxlookxxx";
	//char s2[20] = "look";
	//printf ("s1 %s\n", s1);
	//printf ("s2 %s\n", s2);
	//printf ("%d\n", strindex(s1,s2));
	
	char line[100];
	int type;
	while ((type = getop(line)) != EOF){
		printf ("%s\t", line);
		printf ("%d\n", type);
		printf ("------------\n");
	}
	return 0;
}
