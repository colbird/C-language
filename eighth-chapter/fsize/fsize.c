#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>			/*  读写标志  */
#include <sys/types.h>			/*  类型定义  */
#include <sys/stat.h>			/*  stat返回的结构  */
#include "dirent.h"

void fsize(char *);

 
/*  打印文件长度  */
int main(int argc, char **argv){
	if (argc == 1)			/*  默认为当前目录  */
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

//int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

/*  fsize函数: 打印文件name的长度  */
void fsize(char *name){
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	printf("%8ld %s\n", stbuf.st_size, name);
}

#define MAX_PATH	1024

/*  dirwalk函数: 对dir中的所有文件调用函数fcn  */
void dirwalk(char *dir, void (*fcn)(char *)){
	char name[MAX_PATH];
	Dirent *dp;
	Dir *dfd;

	if ((dfd = Opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n",dir);
		return;
	}
	while ((dp = Readdir(dfd)) != NULL){
		 if (strcmp(dp->name, ".") == 0
		 || strcmp(dp->name, "..") == 0)
			 continue;	/*  跳过自身和父目录  */
		 if (strlen(dir)+strlen(dp->name)+2 > sizeof(name))
			 fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
		 else {
			 sprintf(name, "%s/%s", dir, dp->name);
			 (*fcn)(name);
		 }
	}
	Closedir(dfd);
}

#include <stdlib.h>
//int fstat(int fd, struct stat *);

/*  Opendir函数: 打开目录供Readdir使用  */
Dir *Opendir(char *dirname){
	int fd;
	struct stat stbuf;
	Dir *dp;
	
	if ((fd = open(dirname, O_RDONLY, 0)) == -1
	|| fstat(fd, &stbuf) == -1
	|| (stbuf.st_mode & S_IFMT) != S_IFDIR
	|| (dp = (Dir *) malloc(sizeof(Dir))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}


/*  Closedir函数: 关闭Opendir打开的目录  */
void Closedir(Dir *dp){
	if (dp){
		close(dp->fd);
		free(dp);
	}
}

#include <sys/dir.h>			/*  本地目录结构  */

#define DIRSIZ	14

/*  Readdir函数: 按顺序读取目录项  */
Dirent *Readdir(Dir *dp){
	struct direct dirbuf;		/*  本地目录结构  */
	static Dirent d;		/*  返回: 可移植的结构  */

	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
		if (dirbuf.d_ino == 0)			/*  目录位置未使用  */
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0';		/*  添加终止符  */
		return &d;
	}
	return NULL;
}
