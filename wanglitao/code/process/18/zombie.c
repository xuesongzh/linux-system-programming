
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main (void)
{
	pid_t pid;
	pid = fork ();
	if (pid < 0)
	{
		perror ("fork");
		exit (-1);
	}
	else if (pid == 0)
	{
		printf ("child process, pid:%d ppid:%d\n", getpid (), getppid ());
		printf ("child process exit.\n");
		exit (0);
	}

	printf ("father process sleep 5 seconds\n");
	sleep (5);
	system ("ps -o pid,ppid,state,tty,command ");
	printf ("father process exited.\n");

	return 0;
}
