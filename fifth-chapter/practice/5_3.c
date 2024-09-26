#include <stdio.h>
/* strcar 函数: 将字符串t连接到字符串s的尾部; s必须有足够大的空间 */
void new_strcat (char *s, char *t);

int main(){
	char name1[10] = "xxx";
	char *name2 = "look";

	new_strcat(name1, name2);
	printf("%s\n", name1);
	return 0;
}
void new_strcat (char *s, char *t){
	while(*s)	// *s != '\0'
		s++;
	while(*s++ = *t++)
		;
}
