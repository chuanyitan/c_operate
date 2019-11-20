
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s1[]="hi";
    char s2[]="hello";

    //比较字符串长短
#if 0
    //返回值为无符号类型 相减不可能小于0
    if(strlen(s1)-strlen(s2)>0)
    {
       printf("len s1>s2\n");
    }
    else if(strlen(s1)-strlen(s2)<0)
    {
       printf("len s1<s2\n");
    }
    else
    {
       printf("len s1==s2\n");
    }
#else
    if(strlen(s1)>strlen(s2))
    {
       printf("len s1>s2\n");
    }
    else if(strlen(s1)<strlen(s2))
    {
       printf("len s1<s2\n");
    }
    else
    {
       printf("len s1==s2\n");
    }

#endif //

    return 0;
}
