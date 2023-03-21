
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    signal(SIGTTOU, SIG_IGN);  // umask signal from terminal
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    umask(0);  // umask file mode inheriting from father process

    pid_t ret_id = fork();  // creat child process
    if (ret_id < 0) {
        perror("fork");
        exit(-1);
    } else if (ret_id > 0) {
        exit(0);  // father process exit
    }

    setsid();  // run child process in a new session

    signal(SIGCHLD, SIG_IGN);  // ignore SIGCHID from child process when exited

    ret_id = fork();  // fork again
    if (ret_id < 0) {
        perror("fork");
        exit(-1);
    } else if (ret_id > 0) {
        exit(0);  // forbidden reopen the terminal
    }

    if (chdir("/") < 0) {
        perror("chdir");
        exit(-1);
    }

    close(0);  // close the stdin file description
    close(1);  // close the stdout file description
    close(2);  // close the stderr file description

    while (1) {
        sleep(1);
    }

    return 0;
}
