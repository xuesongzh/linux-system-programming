#include "apue.h"
#include <sys/wait.h>

#define	DEF_PAGER	"/bin/more"		/* Ĭ�ϵķ�ҳ�����ִ���ļ� */

int
main(int argc, char *argv[])
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	*pager, *argv0;
	char	line[MAXLINE];
	FILE	*fp;

    /* ���û�������������кϷ���� */
	if (argc != 2)
		err_quit("usage: a.out <pathname>");

    /* ��������ֻ����ʽ���û�ָ�����ļ� */
	if ((fp = fopen(argv[1], "r")) == NULL)
		err_sys("can't open %s", argv[1]);
    
	/* �����̴����ܵ� */
	if (pipe(fd) < 0)
		err_sys("pipe error");
    
	/* �����̴����ӽ��� */
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {								/* ������ */
		close(fd[0]);		/* �����̹رն��� */

		/* �����̰��ж�ȡ�ļ����ݣ�д��ܵ� */
		while (fgets(line, MAXLINE, fp) != NULL) {
			n = strlen(line);
			if (write(fd[1], line, n) != n)
				err_sys("write error to pipe");
		}
		if (ferror(fp))
			err_sys("fgets error");

		close(fd[1]);	/* Ϊ���˹رչܵ���д�� */ /* ˼�����������ô������ô���� */

		if (waitpid(pid, NULL, 0) < 0) /* �ȴ��ӽ��̽��� */
			err_sys("waitpid error");
		exit(0);
	} else {										/* �ӽ��� */
		close(fd[1]);	/* �ӽ��̹ر�д�� */ 
		if (fd[0] != STDIN_FILENO) {
            /* ����dup2, ʹ���׼�����Ϊ�ܵ��Ķ��ˣ���ִ�з�ҳ����ʱ����׼���뽫�ǹܵ��Ķ��� */
			/* ����dup2��˵�������Բο�ԭ��3.12С�� */
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) 
				err_sys("dup2 error to stdin");
			close(fd[0]);	/* ִ����dup2֮����Խ���ر� */
		}

		/* �ӻ���������ȡ��ҳ�������û���ҵ��Ļ���ʹ��Ĭ�ϳ��� */
		if ((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;		/* ȥ����ִ���ļ�·�����е����ұߵ�'/'���� */
		else
			argv0 = pager;	/* ��ִ���ļ�·������û��'/'���� */
        
		/* ִ�з�ҳ���� */
		if (execl(pager, argv0, (char *)0) < 0)
			err_sys("execl error for %s", pager);
	}
	exit(0);
}
