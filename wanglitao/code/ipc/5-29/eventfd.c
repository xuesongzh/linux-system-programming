#include <stdint.h> /* Definition of uint64_t */
#include <stdio.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <unistd.h>

#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

int main(int argc, char *argv[]) {
    int fd_event, j;
    uint64_t u;
    ssize_t s;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num>...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd_event = eventfd(0, EFD_SEMAPHORE);
    if (fd_event == -1)
        handle_error("eventfd");

    switch (fork()) {
        case 0:
            sleep(1);
            for (j = 1; j < argc; j++) {
                printf("Child writing %s to fd_event\n", argv[j]);
                u = strtoull(argv[j], NULL, 0);
                /* strtoull() allows various bases */
                s = write(fd_event, &u, sizeof(uint64_t));
                if (s != sizeof(uint64_t))
                    handle_error("write");
            }
            printf("Child completed write loop\n");
            exit(EXIT_SUCCESS);

        default:
            //  sleep (2);

            printf("Parent about to read\n");
            s = read(fd_event, &u, sizeof(uint64_t));
            if (s != sizeof(uint64_t))
                handle_error("read");
            printf("Parent read %llu (0x%llx) from fd_event\n",
                   (unsigned long long)u, (unsigned long long)u);

            s = read(fd_event, &u, sizeof(uint64_t));
            if (s != sizeof(uint64_t))
                handle_error("read");
            printf("Parent read %llu (0x%llx) from fd_event\n",
                   (unsigned long long)u, (unsigned long long)u);

            s = read(fd_event, &u, sizeof(uint64_t));
            if (s != sizeof(uint64_t))
                handle_error("read");
            printf("Parent read %llu (0x%llx) from fd_event\n",
                   (unsigned long long)u, (unsigned long long)u);
            exit(EXIT_SUCCESS);

        case -1:
            handle_error("fork");
    }
}
// ./a.out 1 2 3 4 5 6 7 8 9
