#include <stdio.h>

#define LINEMAX 1000

void Delan (char line[], int len);
int newgetline (char line[], int max);

int main(){
	char line[LINEMAX];
	int len;
	while (len = newgetline(line, LINEMAX)){
		Delan(line, len);
		printf("%s", line);
	}
	return 0;
}


int  newgetline (char line[], int max){
	int i, c;

	for (i = 0; i < max - 1 && (c=getchar())!=EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return i;
}


void Delan (char line[], int len){
	int i, j;
	
	for (i = j = 0; i < len + 1; ++i){
		if (line[i] == '/'){
			if(line[i+1] == '/'){			//test
				if (line[len-1] == '\n'){
					line[j++] = '\n';
					line[j] = '\0';
				}
				else
					line[j] = '\n';
				break;
			}
			else
				line[j++]=line[i];
		}
		else{
			line[j++]=line[i];
		}

	}
}
// test test
/* tset */
