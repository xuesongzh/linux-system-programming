#include <stdio.h>
#include <stdlib.h>

// pragma实例
//#pragma pack (1) 1字节对齐
typedef struct {
    char a;
    int b;
} own_type;
//#pragma pack ()

foo(const int *fp)  // const实例3：用const来限定形参
{
    //*fp = 30;
}

int main(int argc, char **argv) {
    // const int*，int const*，int* const
    // 第一种和第二种常量指针，第三种指针常量
    const int x = 10;
    const int y = 20;
    const int *p = &x;
    //*p = 30;                     const实例1：你不能修改p指向的内容
    // p = &y;                     const实例2：你可以修改p本身，使它指向其他变量
    printf("*p=%d\n", *p);

    // foo(&x);
    printf("x=%d\n", x);

    own_type my_data;
    printf("struct size is:%d", sizeof(my_data));  // 5

    return 0;
}
