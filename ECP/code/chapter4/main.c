#include <stdio.h>
#include <stdlib.h>

#include "test.h"

// 将数组声明为指针
extern char* arr;
// 将指针声明为数组
extern char arr2[];

int checkSystem(void) {
    int i = 0x12345678;
    char* c = &i;
    return ((c[0] == 0x78) && (c[1] == 0x56) && (c[2] == 0x34) && (c[3] == 0x12));
}

int main() {
    if (checkSystem())
        printf("this is little endian\n");
    else
        printf("this is big endian\n");

    printf("%s", arr);  // crash
    printf("%s", &arr); /* workaround */

    printf("%s", arr2);
    printf("%s", (char*)(*(int*)arr2)); /* workaround */
    return 0;
}
