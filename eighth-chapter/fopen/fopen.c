#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "fopen.h"
#define	PERMS	0666		/*  文件权限  */

FILE *fopen(char *name, char *mode){
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;			/*  寻找一个空闲位  */
	if (fp >= _iob + OPEN_MAX)
		return NULL;			/*  没有空闲位置  */

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if(*mode == 'a'){
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)				/*  不能访问名字  */
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

int fclose(FILE *fp){
	int rc;
	if ((rc = fflush(fp)) != EOF) {
		free(fp->base);
		fp->ptr = NULL;
		fp->base = NULL;
		fp->cnt = 0;
		fp->flag &= ~(_READ | _WRITE);
	}
	return rc;
}
int fflush(FILE *fp){
	int rc = 0;

	if (fp < _iob || fp >= _iob + OPEN_MAX)
		return EOF;
	if (fp->flag & _WRITE)
		rc = _flushbuf(0, fp);
	fp->ptr = fp->base;
	fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	return rc;
}
int fseek(FILE *fp, long offset, int origin){
	unsigned nc;
	long rc = 0;
	
	if (fp->flag & _READ) {
		if (origin == 1)
			offset -= fp->cnt;
		rc = lseek(fp->fd, offset, origin);
		fp->cnt = 0;
	} else if (fp->flag & _WRITE){
		if ((nc = fp->ptr - fp->base) > 0)
			if (write(fp->fd, fp->base, nc) != nc)
				rc = -1;
		if (rc != -1)
			rc = lseek(fp->fd, offset, origin);
	}
	return (rc == 1) ? -1 : 0;
}
