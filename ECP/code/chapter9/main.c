#include <stdio.h>
#include <stdlib.h>

int (*paf())[20] {
    int(*pear)[20];
    pear = malloc(sizeof(int) * 20);
    if (!pear)
        return (int(*)[]) - 1; /* ǿ������ת�� */
    return pear;
}

int main() {
    int intresting[4] = {1, 2, 3, 4};
    printf("intresting[2]=%d\n", intresting[2]);
    printf("2[intresting]=%d\n", 2 [intresting]); /* Ҳ����������Ծ������Ǻ���������ô�� */

    int(*result)[20];
    result = paf(); /* �ú�������һ��ָ�������ָ�� */
    (*result)[3] = 12;
    return 0;
}
