#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

//���ӵ�����
char* const* (*next)();

char s[] = "hello world\n";

char* const* example_fun() {
    return (char* const*)s;
}

/* �����ķ���ֵ������һ������ָ�� */
int fp() {
    return 1;
}

int (*fun())() {
    return fp;
}

/* �����ķ���ֵ������һ��ָ�������ָ�� */
int array[4] = {1, 2, 3, 4};

int (*fun1())[] {
    return array;
}
/* �������������к���ָ�� */
int fa() {
}

int fb() {
}

/* signal����ʹ�þ��� */
void signal_handler_fun(int signum) {
    printf("catch signal %d\n", signum);
}

int main() {
    // ���ӵ�����
    next = example_fun;
    printf("%s", next());

    /* �����ķ���ֵ������һ������ָ�� */
    int (*fp)() = fun();
    printf("fp()=%d\n", fp());

    /* �����ķ���ֵ������һ��ָ�������ָ�� */
    int(*ap)[4] = fun1();
    printf("ap[3]=%d\n", (*ap)[3]);

    /* �������������к���ָ�� */
    int (*fun2[])() = {fa, fb};

    /* ���������������������� */
    int aa[2][2];

    /* signal����ʹ�þ��� */
    signal(SIGINT, signal_handler_fun);
    while (1)
        ;

    return 0;
}
