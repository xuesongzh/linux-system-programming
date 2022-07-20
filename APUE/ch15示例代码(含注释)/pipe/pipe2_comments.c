#include "apue.h"
#include <sys/wait.h>

#define	DEF_PAGER	"/bin/more"		/* 默认的分页程序可执行文件 */

int
main(int argc, char *argv[])
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	*pager, *argv0;
	char	line[MAXLINE];
	FILE	*fp;

    /* 对用户的输入参数进行合法检查 */
	if (argc != 2)
		err_quit("usage: a.out <pathname>");

    /* 父进程以只读方式打开用户指定的文件 */
	if ((fp = fopen(argv[1], "r")) == NULL)
		err_sys("can't open %s", argv[1]);
    
	/* 父进程创建管道 */
	if (pipe(fd) < 0)
		err_sys("pipe error");
    
	/* 父进程创建子进程 */
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {								/* 父进程 */
		close(fd[0]);		/* 父进程关闭读端 */

		/* 父进程按行读取文件内容，写入管道 */
		while (fgets(line, MAXLINE, fp) != NULL) {
			n = strlen(line);
			if (write(fd[1], line, n) != n)
				err_sys("write error to pipe");
		}
		if (ferror(fp))
			err_sys("fgets error");

		close(fd[1]);	/* 为读端关闭管道的写端 */ /* 思考：如果不这么做会怎么样？ */

		if (waitpid(pid, NULL, 0) < 0) /* 等待子进程结束 */
			err_sys("waitpid error");
		exit(0);
	} else {										/* 子进程 */
		close(fd[1]);	/* 子进程关闭写端 */ 
		if (fd[0] != STDIN_FILENO) {
            /* 调用dup2, 使其标准输入成为管道的读端，即执行分页程序时，标准输入将是管道的读端 */
			/* 关于dup2的说明，可以参考原书3.12小节 */
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) 
				err_sys("dup2 error to stdin");
			close(fd[0]);	/* 执行完dup2之后可以将其关闭 */
		}

		/* 从环境变量获取分页程序，如果没有找到的话，使用默认程序 */
		if ((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;		/* 去掉可执行文件路径名中的最右边的'/'符号 */
		else
			argv0 = pager;	/* 可执行文件路径名中没有'/'符号 */
        
		/* 执行分页程序 */
		if (execl(pager, argv0, (char *)0) < 0)
			err_sys("execl error for %s", pager);
	}
	exit(0);
}
