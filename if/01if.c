
#include <stdio.h>

int main(void)
{
   int a=1;


#if 0
    printf("is a.\n");
    printf("is b.\n");
#elif 1
 #if 0
    printf("is c.\n");
 #else
    printf("is d.\n");
 #endif //
#else
    printf("is e.\n");
    printf("is f.\n");
#endif //

    return 0;
}
