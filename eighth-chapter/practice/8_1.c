#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void error(char *, ...);

int main(int argc, char *argv[]){
	void filecopy(int, int);
	int fd;
	if (argc == 1){
		filecopy(0, 1);
	} else {
		while (--argc > 0) {
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
				error("cat: can't open %s", *argv);
			else {
				filecopy(fd, 1);
				close(fd);
			}
		}
	}
	exit(0);
}
//  filecopy: 将文件ifd复制到文件ofd
void filecopy(int ifd, int ofd){
	char buf[BUFSIZ];
	int n;
	while ((n = read(ifd, buf, BUFSIZ)) > 0)
		if (write (ofd, buf, n) != n)
			error("cat: write error");
}

#include <stdarg.h>

void error(char *fmt, ...){
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}






//int main(int argc, char *argv[]){
//	FILE *fp;
//	void filecopy(FILE *, FILE *);
//	char *prog = argv[0];
//
//	if (argc == 1)
//		filecopy(stdin, stdout);
//	else
//		while (--argc > 0)
//			if ((fp = fopen(*++argv, "r")) == NULL) {
//				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
//				exit(1);
//			} else {
//				filecopy(fp, stdout);
//				fclose(fp);
//			}
//	if (ferror(stdout)) {
//		fprintf(stderr, "%s: error writing stdout\n", prog);
//		exit(2);
//	}
//	exit(0);
//}
//
//void filecopy(FILE *ifp, FILE *ofp){
//	int c;
//
//	while ((c = getc(ifp)) != EOF)
//		putc(c, ofp);
//}
