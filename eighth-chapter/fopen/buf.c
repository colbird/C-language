#include <stdlib.h>
#include <unistd.h>
#include "fopen.h"

FILE _iob[OPEN_MAX] = {		/*  stdin, stdout, stderr  */
	{ 0, (char *) 0, (char *) 0, _READ, 0},
	{ 0, (char *) 0, (char *) 0, _WRITE, 1},
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};

int _fillbuf(FILE *fp){
	int bufsize;

	if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)	/*  只允许fp->flag = _READ  */
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL)				/*  还未分配缓冲区  */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;			/*  不能分配缓冲区  */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0){
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int _flushbuf(int x, FILE *fp){
	unsigned nc;
	int bufsize;
	
	if (fp < _iob || fp >= _iob + OPEN_MAX)
		return EOF;
	if ((fp->flag&(_WRITE|_ERR)) != _WRITE)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if(fp->base == NULL) {				/*  还未分配缓冲区  */
		if ((fp->base = (char *) malloc(bufsize)) == NULL){
			fp->flag |= _ERR;		/*  不能分配缓冲区  */
			return EOF;
		}
	} else {
		nc = fp->ptr - fp->base;
		if (write(fp->fd, fp->base, nc) != nc){
			fp->flag |= _ERR;
			return EOF;
		}
	}
	fp->ptr = fp->base;
	*fp->ptr++ = (char) x;
	fp->cnt = bufsize - 1;
	return x;
}
