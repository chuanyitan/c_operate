
//应用strchr函数将串中的字符o改为大写'O'
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[]="hello uplooking how are you ?";
    char *t;

    printf("s:%s\n",s);
    while((t=strchr(s,'o'))!=NULL)
    {
       *t='O';
    }
    printf("s:%s\n",s);
    return 0;
}
