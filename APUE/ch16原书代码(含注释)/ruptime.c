#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#define MAXADDRLEN	256
#define BUFLEN		128

extern int connect_retry(int, const struct sockaddr *, socklen_t);

void
print_uptime(int sockfd)
{
	int		n;
	char	buf[BUFLEN];

	while ((n = recv(sockfd, buf, BUFLEN, 0)) > 0) /* 从socket接收数据 直到全部收完为止 */
		write(STDOUT_FILENO, buf, n);
	if (n < 0)
		err_sys("recv error");
}

int
main(int argc, char *argv[])
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo	hint;
	int				sockfd, err;

/* 如果启动命令不是ruptime hostname, 则提示用法 */
	if (argc != 2)
		err_quit("usage: ruptime hostname");

	hint.ai_flags = 0;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;

/* 获取server端的IP和服务对应的port号 */
	if ((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0)
		err_quit("getaddrinfo error: %s", gai_strerror(err));

/* 用这个address执行socket和connect操作（如果一次不成功，就retry尝试connect）*/
	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((sockfd = socket(aip->ai_family, SOCK_STREAM, 0)) < 0)
			err = errno;
		if (connect_retry(sockfd, aip->ai_addr, aip->ai_addrlen) < 0) {
			err = errno;
		} else {
			print_uptime(sockfd);/* 在connect成功后，用recv接收从server端发来的数据，并输出到终端 */
			exit(0);
		}
	}
	fprintf(stderr, "can't connect to %s: %s\n", argv[1],
	  strerror(err));
	exit(1);
}
