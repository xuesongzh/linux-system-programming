#include <stdio.h>
#include <stdlib.h>

// pragmaʵ��
//#pragma pack (1) 1�ֽڶ���
typedef struct {
    char a;
    int b;
} own_type;
//#pragma pack ()

foo(const int *fp)  // constʵ��3����const���޶��β�
{
    //*fp = 30;
}

int main(int argc, char **argv) {
    // const int*��int const*��int* const
    // ��һ�ֺ͵ڶ��ֳ���ָ�룬������ָ�볣��
    const int x = 10;
    const int y = 20;
    const int *p = &x;
    //*p = 30;                     constʵ��1���㲻���޸�pָ�������
    // p = &y;                     constʵ��2��������޸�p����ʹ��ָ����������
    printf("*p=%d\n", *p);

    // foo(&x);
    printf("x=%d\n", x);

    own_type my_data;
    printf("struct size is:%d", sizeof(my_data));  // 5

    return 0;
}
