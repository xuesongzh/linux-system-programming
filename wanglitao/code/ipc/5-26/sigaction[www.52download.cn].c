/************************************************
*      Filename: sigaction-demo.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: base usage of sigaction
*        Create: 2019-06-11 09:16:40
* Last Modified: 2019-07-24 12:12:57
*************************************************/
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void signal_handler (int signum)
{
    printf ("signal_handler\n");
    switch (signum)
    {
        case SIGHUP:
            printf ("get signal: SIGHUP\n");
            sleep (20);
            break;
        case SIGINT:
            printf ("get signal: SIGINT\n");
            break;
        case SIGQUIT:
            printf ("get signal: SIGQUIT\n");
            break;
        case SIGUSR1:
            printf ("get signal: SIGUSR1\n");
            break;
        default:
            printf ("undefined signal\n");
    }
}
void signal_sigaction (int signum, siginfo_t *parm, void *parm2)
{
    printf ("signal_sigaction\n");
    switch (signum)
    {
        case SIGHUP:
            printf ("get signal: SIGHUP\n");
            break;
        case SIGINT:
            printf ("get signal: SIGINT\n");
            break;
        case SIGQUIT:
            printf ("get signal: SIGQUIT\n");
            break;
        case SIGUSR1:
            printf ("get signal: SIGUSR1\n");
    }
    printf ("received data: %d\n", parm->si_value);
    printf ("sending signal process pid : %d\n", parm->si_pid);
}


int main (void)
{
	struct sigaction act, old_act;
    act.sa_sigaction = signal_sigaction;
	act.sa_handler = signal_handler;
	sigemptyset (&act.sa_mask);
	sigaddset (&act.sa_mask, SIGUSR1);
    act.sa_flags = 0;
        //sa_flags must be set,or it will cause core dump
        //set 0 may cause signal losing
        //act.sa_flags = SA_RESETHAND | SA_NODEFER;
        //SA_RESETHAND: restore signal action to DEF
        //SA_SIGINFO: use sa_sigaction as signal handler
        //SA_NODEFER: umask sa_mask

	sigaction (SIGHUP, &act, &old_act);
//	sigaction (SIGINT, &act, &old_act);
//	sigaction (SIGQUIT, &act, &old_act);
//	sigaction (SIGUSR1, &act, &old_act);
    while (1);
	return 0;
}
