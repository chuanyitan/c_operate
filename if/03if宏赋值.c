//条件编译实现不同版本的选择
#include <stdio.h>

//编译时开启宏 该宏的值默认为1   gcc 03if.c -D BIT_64 
//也可以指定值 gcc 03if.c -D BIT_64=100
//#define    BIT_64

int main(void)
{
     printf("公共代码...\n");
     printf("公共代码...\n");
#ifndef   BIT_64
     printf("32bit平台代码\n");
#else
     printf("64bit平台代码\n");
#endif //
     printf("公共代码...\n");
     printf("公共代码...\n");
     printf("公共代码...\n");

     printf("公共代码...\n");
     printf("公共代码...\n");
#ifndef   BIT_64
     printf("32bit平台代码\n");
#else
     printf("64bit平台代码\n");
#endif //
     printf("公共代码...\n");
     printf("公共代码...\n");

     return 0;
}
