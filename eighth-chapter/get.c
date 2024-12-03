#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int get(int fd, long pos, char *buf, int n);

int main(int argc, char *argv[]){
	char buf[BUFSIZ];
	int fd;
	if (argc != 1){
		while (--argc > 0)
			if ((fd = open(*++argv, O_RDONLY, 0)) != -1){
				get(fd, 2, buf, 4);
				close(fd);
				printf ("%s", buf);
			}
			else{
				printf ("error: can't open %s", *argv);
				return 1;
			}
	}
	else{
		printf ("%s: error\n", *argv);
	}
	return 0;
}

int get(int fd, long pos, char *buf, int n){
	if (lseek(fd, pos, 0) >= 0)
		return read(fd, buf, n);
	else
		return -1;
}
