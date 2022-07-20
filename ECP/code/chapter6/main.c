#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

// setjmp&longjmp example
jmp_buf buf;

int *p = NULL;

void handler() {
    //����longjmp������buf����setjmp����������Ķ�ջ��������ʹsetjmp�ķ���ֵΪ1
    longjmp(buf, 1);
    //���´��벻��ִ��
    printf("never reach here\n");
}

int main() {
    // setjmp�����û�����envbuf����ϵͳ��ջ�����ݣ��Ա������longjmp����ʹ�á�setjmp������������ʱ����0ֵ
    if (setjmp(buf)) {
        printf("back in main\n");
    } else {
        printf("first time through\n");
        handler();
    }
    // segment fault : ������һ����ָ��
    //*p = 30;

    char *mystr = "Hello"; /* ��ָ���Hello�ǳ��ַ����������޸�(���ǲ���д����)*/
    // mystr[0] = 'w';

    char mystr2[] = "World"; /* �ַ���Hello���ǳ��ַ����������޸� */
    // mystr2[0] = 'h';
    return 0;
}
