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

/* ��initsrv1.c�ļ���ʵ�� */
extern int initserver(int, struct sockaddr *, socklen_t, int);

void
serve(int sockfd)
{
	int		clfd;
	FILE	*fp;
	char	buf[BUFLEN];

	for (;;) {
		clfd = accept(sockfd, NULL, NULL); /* ����client����������һ���յ���������ִ��accept�Ĳ���������һ�������õ�ͨ���׽��������� */ 
		if (clfd < 0) {
			syslog(LOG_ERR, "ruptimed: accept error: %s",
			  strerror(errno));
			exit(1);
		}
		if ((fp = popen("/usr/bin/uptime", "r")) == NULL) { /* pipe�ķ�ʽʵ��server���ڲ���IPC��ִ��uptime command (����popen����ʵ��, �ο���15��) */
			sprintf(buf, "error: %s\n", strerror(errno));
			send(clfd, buf, strlen(buf), 0);
		} else {
			while (fgets(buf, BUFLEN, fp) != NULL) /* ����ͨ��pipe��ȡuptime commandִ�н��������buf�� */
				send(clfd, buf, strlen(buf), 0); /* �ѽ��send��client�� */
			pclose(fp);
		}
		close(clfd); /* ������ͻ��˵�������󣬹ر�ͨ���׽������������������������ͻ��˷������� */
	}
}

int
main(int argc, char *argv[])
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo	hint;
	int				sockfd, err, n;
	char			*host;

/* ������������ruptimed, ����ʾ�÷� */
	if (argc != 1)
		err_quit("usage: ruptimed");

#ifdef _SC_HOST_NAME_MAX
	n = sysconf(_SC_HOST_NAME_MAX);
	if (n < 0)	/* best guess */
#endif
		n = HOST_NAME_MAX;
/* ����һ���㹻���Ĵ��host name���ַ��� */
	host = malloc(n);
	if (host == NULL)
		err_sys("malloc error");
	if (gethostname(host, n) < 0)/* ���hostname */
		err_sys("gethostname error");

/* ����daemonize����ʹ�Լ���Ϊ�ػ����̣��ں�̨���� */
/* ΪʲôҪ����daemonize�õ�ǰ���̱���ػ����̣�*/
/* a. ʲɶҪ��server�˱��һ��daemon����˵��server����������൱��һ������ķ�����̣������ܵ��κ�terminal��Ӱ�죨������Ϊ�ն˶���������̻��߽����Ự�͹��ˣ�*/
/* b. Ҫ��ʵ��daemon process��Ҫһ�����̣�̫���ϸ�ھͲ�������,��ҿ��Բο���13��<�ػ�����>�Ľ��� */
	daemonize("ruptimed");

	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;

/* ��ȡ�������'ruptime'����Ŀ���address��ip+port��������ailist: linked list������з���������addrinfo structure */
	if ((err = getaddrinfo("localhost"/*host*/, "ruptime", &hint, &ailist)) != 0) {
		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
		  gai_strerror(err));
		exit(1);
	}
	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr, /* �������ַ�Դ�ִ��socket bind listen����(������װ��һ��initserver.c�ļ�)��������һ�������ļ����׽��������� */
		  aip->ai_addrlen, QLEN)) >= 0) {
			serve(sockfd); /* serve��һ������ѭ�� */
			exit(0);
		}
	}
	exit(1);
}
