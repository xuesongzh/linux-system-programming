#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>

#define BUFLEN	128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

/* 在initsrv1.c文件中实现 */
extern int initserver(int, struct sockaddr *, socklen_t, int);

void
serve(int sockfd)
{
	int		clfd;
	FILE	*fp;
	char	buf[BUFLEN];

	for (;;) {
		clfd = accept(sockfd, NULL, NULL); /* 监听client发来的请求；一旦收到了请求，则执行accept的操作，生成一个可以用的通信套接字描述符 */ 
		if (clfd < 0) {
			syslog(LOG_ERR, "ruptimed: accept error: %s",
			  strerror(errno));
			exit(1);
		}
		if ((fp = popen("/usr/bin/uptime", "r")) == NULL) { /* pipe的方式实现server端内部的IPC，执行uptime command (利用popen函数实现, 参考第15章) */
			sprintf(buf, "error: %s\n", strerror(errno));
			send(clfd, buf, strlen(buf), 0);
		} else {
			while (fgets(buf, BUFLEN, fp) != NULL) /* 不断通过pipe获取uptime command执行结果，存入buf中 */
				send(clfd, buf, strlen(buf), 0); /* 把结果send回client端 */
			pclose(fp);
		}
		close(clfd); /* 处理完客户端的这次请求，关闭通信套接字描述符，继续等着其他客户端发送请求 */
	}
}

int
main(int argc, char *argv[])
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo	hint;
	int				sockfd, err, n;
	char			*host;

/* 如果启动命令不是ruptimed, 则提示用法 */
	if (argc != 1)
		err_quit("usage: ruptimed");

#ifdef _SC_HOST_NAME_MAX
	n = sysconf(_SC_HOST_NAME_MAX);
	if (n < 0)	/* best guess */
#endif
		n = HOST_NAME_MAX;
/* 分配一个足够长的存放host name的字符串 */
	host = malloc(n);
	if (host == NULL)
		err_sys("malloc error");
	if (gethostname(host, n) < 0)/* 获得hostname */
		err_sys("gethostname error");

/* 调用daemonize函数使自己成为守护进程，在后台运行 */
/* 为什么要调用daemonize让当前进程变成守护进程？*/
/* a. 什啥要让server端变成一个daemon？简单说，server端这个进程相当于一个纯粹的服务进程，不想受到任何terminal的影响（不会因为终端断了这个进程或者结束会话就挂了）*/
/* b. 要想实现daemon process需要一套流程，太多的细节就不解释了,大家可以参考第13章<守护进程>的讲解 */
	daemonize("ruptimed");

	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;

/* 获取所有这个'ruptime'服务的可用address（ip+port），返回ailist: linked list存放所有符合条件的addrinfo structure */
	if ((err = getaddrinfo("localhost"/*host*/, "ruptime", &hint, &ailist)) != 0) {
		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
		  gai_strerror(err));
		exit(1);
	}
	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr, /* 用这个地址以此执行socket bind listen操作(单独封装成一个initserver.c文件)，并返回一个被动的监听套接字描述符 */
		  aip->ai_addrlen, QLEN)) >= 0) {
			serve(sockfd); /* serve是一个无限循环 */
			exit(0);
		}
	}
	exit(1);
}
