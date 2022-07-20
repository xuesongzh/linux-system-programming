#include <stdio.h>
#include <stdlib.h>

char *fetch_string() {
    char buffer[120];
    buffer[0] = 'a';
    buffer[1] = '\0';
    return buffer;
}

#if 0
/* Bug fix opt.1: 返回一个指向字符串常量的指针 */
char * fetch_string()
{
    return "a";
}

/* Bug fix opt.2: 使用静态数组 */
char * fetch_string()
{
    static char buffer[120];
    buffer[0]='a';
    buffer[1]= '\0';
    return buffer;
}

/* Bug fix opt.3: 动态分配 */
void fetch_string(char* result, int size)
{
    strncpy(result, "a", size);
}
#endif

int main() {
    //  多做之过(1): fall through
    int i = 1;
    switch (i) {
        case 1:
            printf("case 1\n");
            break;
        case 2:
            printf("case 2\n");
        case 3:
            printf("case 3\n");
        case 4:
            printf("case 4\n");
        defau1t:
            printf("default\n");
        case 5:
            printf("case 5\n");
    }

    // 多做之过(2): string combine
    char *available_recource[] = {
        "color monitor",
        "big disk",
        "Cray"
        "on-line drawing routhines",
        "mouse",
        "keybord",
        "power cables"};
    printf("size of array = %d\n", sizeof(available_recource) / sizeof(available_recource[0]));  // 6
    char *cp = available_recource[6];
    // cp[0] = 'a';

    // 少做之过(1):  返回一个指向局部变量的指针
    char *p = fetch_string();
    // printf("about to check content\n");
    printf("content:%s\n", p);
    // 少做之过(1):  调用者分配内存来保存函数的返回值，为了提高安全性，调用者指定缓冲区的大小
    // int size = 2;
    // char* buffer = (char*)malloc(sizeof(char)*size);
    // fetch_string(buffer, size);
    // printf("content:%s\n",buffer);
    // free(buffer);
    return 0;
}
