#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAXLINE	100

int main(int argc, char *argv[]){
	FILE *f1, *f2;
	char *prog = *argv;	//  记下程序名
	void filecomp(FILE *fp1, FILE *fp2);
	
	if (argc == 3){
		if (((f1 = fopen(*++argv, "r")) == NULL) || ((f2 = fopen(*++argv, "r")) == NULL)){
			fprintf (stderr, "%s: can't open %s\n", prog, *argv);
			exit(2);
		} else{
			filecomp(f1, f2);
			fclose(f1);
			fclose(f2);
			exit(0);
		}
	} else{
		fprintf (stderr, "%s: need two files\n", prog);
		exit(1);
	}
	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(3);
	}
	exit(0);
}

void filecomp(FILE *fp1, FILE *fp2){
	char line1[MAXLINE], line2[MAXLINE];
	char *lp1, *lp2;

	do {
		lp1 = fgets(line1, MAXLINE, fp1);
		lp2 = fgets(line2, MAXLINE, fp2);
		if (lp1 == line1 && lp2 == line2) {
			if (strcmp(line1, line2) != 0) {
				printf ("first difference in line\n%s\n", line1);
				lp1 = lp2 = NULL;
			}
		} else if (lp1 != line1 && lp2 == line2)
			printf ("end of first file at line\n%s\n", line2);
		else if (lp1 == line1 && lp2 != line2)
			printf ("end of second file at line\n%s\n", line1);
	} while (lp1 == line1 && lp2 == line2);
}
