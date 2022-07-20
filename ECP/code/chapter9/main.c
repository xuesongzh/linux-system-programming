#include <stdio.h>
#include <stdlib.h>

int (*paf())[20] {
    int(*pear)[20];
    pear = malloc(sizeof(int) * 20);
    if (!pear)
        return (int(*)[]) - 1; /* 强制类型转换 */
    return pear;
}

int main() {
    int intresting[4] = {1, 2, 3, 4};
    printf("intresting[2]=%d\n", intresting[2]);
    printf("2[intresting]=%d\n", 2 [intresting]); /* 也许这里让你吃惊，但是很少有人这么做 */

    int(*result)[20];
    result = paf(); /* 让函数返回一个指向数组的指针 */
    (*result)[3] = 12;
    return 0;
}
