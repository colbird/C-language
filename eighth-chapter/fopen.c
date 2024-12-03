#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define PERMS 0666

static FILE *fopne(char *name, char *mode){
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;		/*  寻找一个空闲位  */
	if (fp >= _iob + OPEN_MAX)	/*  没有空闲的位置  */
		return NULL;
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_RDONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	}
	else 
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)		/*  不能访问名字  */
		return NULL;
	fp->fd  = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}
