#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    char buf[64];
    int i;

    printf("read process pid: %d\n", getpid());
    int fd = open("data.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    int len = 0;
    int last_len = 0;
    while (1) {
        if ((len = read(fd, buf, 64)) < 0) {
            perror("read");
            close(fd);
            return -2;
        }
        printf("%s", buf);
        lseek(fd, SEEK_SET, 0);
        sleep(5);
    }
    close(fd);
    return 0;
}
