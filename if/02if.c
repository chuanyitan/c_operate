//#ifdef  #ifndef判断某符号是否定义  不关心符号的值
#include <stdio.h>

#define    NR       0

int main(void)
{

//如果没有定义NR则成立
#ifndef   NR
    printf("is a.\n");
#else
    printf("is b.\n");
#endif //NR

#ifdef   NR
    printf("is c.\n");
    printf("is d.\n");
#else
    printf("is e.\n");
    printf("is f.\n");
#endif //
    return 0;
}
