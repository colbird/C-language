#include "fopen.h"

int main(int argc, char *argv[]){
	FILE *fp;
	if (argc != 1){
		if ((fp = fopen(argv[1], "r")) != NULL){
			putchar(getc(fp));
			fflush(stdout);
		}
	}
	return 0;
}

