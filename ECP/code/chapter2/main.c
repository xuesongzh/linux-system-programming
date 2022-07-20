#include <stdio.h>
#include <stdlib.h>

char *fetch_string() {
    char buffer[120];
    buffer[0] = 'a';
    buffer[1] = '\0';
    return buffer;
}

#if 0
/* Bug fix opt.1: ����һ��ָ���ַ���������ָ�� */
char * fetch_string()
{
    return "a";
}

/* Bug fix opt.2: ʹ�þ�̬���� */
char * fetch_string()
{
    static char buffer[120];
    buffer[0]='a';
    buffer[1]= '\0';
    return buffer;
}

/* Bug fix opt.3: ��̬���� */
void fetch_string(char* result, int size)
{
    strncpy(result, "a", size);
}
#endif

int main() {
    //  ����֮��(1): fall through
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

    // ����֮��(2): string combine
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

    // ����֮��(1):  ����һ��ָ��ֲ�������ָ��
    char *p = fetch_string();
    // printf("about to check content\n");
    printf("content:%s\n", p);
    // ����֮��(1):  �����߷����ڴ������溯���ķ���ֵ��Ϊ����߰�ȫ�ԣ�������ָ���������Ĵ�С
    // int size = 2;
    // char* buffer = (char*)malloc(sizeof(char)*size);
    // fetch_string(buffer, size);
    // printf("content:%s\n",buffer);
    // free(buffer);
    return 0;
}
