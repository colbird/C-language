#ifndef	__DIRENT_H__
#define	__DIRENT_H__

#define NAME_MAX	14		/*  最长文件名: 由具体的系统决定  */


typedef struct {			/*  可移植的目录项  */
	long ino;			/*  inode(i节点)编号  */
	char name[NAME_MAX+1];		/*  文件名加结束符'\0'  */
} Dirent;

typedef struct {			/*  最小的Dir: 无缓冲等特征  */
	int fd;				/*  目录的文件描述符  */
	Dirent d;			/*  目录项  */
} Dir;

Dir *Opendir(char *dirname);
Dirent *Readdir(Dir *dfd);
void Closedir(Dir *dfd);

#endif
