#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <unistd.h>

#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

void print_signal(struct signalfd_siginfo *siginfo) {
    printf("read signal: %d\n", siginfo->ssi_signo);
    printf("sending process PID: %d\n", siginfo->ssi_pid);
}

int main(int argc, char *argv[]) {
    sigset_t mask;
    int signal_fd;
    struct signalfd_siginfo siginfo;
    ssize_t read_len;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);

    /* Block signals so that they aren't handled
     according to their default dispositions */

    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
        handle_error("sigprocmask");

    signal_fd = signalfd(-1, &mask, 0);
    if (signal_fd == -1)
        handle_error("signalfd");

    for (;;) {
        read_len = read(signal_fd, &siginfo, sizeof(struct signalfd_siginfo));
        if (read_len != sizeof(struct signalfd_siginfo))
            handle_error("read");

        if (siginfo.ssi_signo == SIGINT)
            print_signal(&siginfo);
        else if (siginfo.ssi_signo == SIGQUIT)
            print_signal(&siginfo);
        else if (siginfo.ssi_signo == SIGHUP)
            print_signal(&siginfo);
        else
            printf("Read unexpected signal\n");
        printf("for loop\n");
    }
}
