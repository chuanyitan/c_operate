
#include <stdio.h>
#include <string.h>

char *mystrcpy(char *dest,const char *src);

int main(void)
{
    char buf[64],s[]="hello uplooking!";
    char *t;

    //buf=s;//error数组无法直接赋值

    t=strcpy(buf,s);
    printf("t:%p buf:%p\n",t,buf);
    printf("buf:%s\n",buf);

    
    //复制n个字符  如果少于用'\0'填补
    char s2[]="12345";

    strncpy(buf,s2,8);
    printf("buf:%s [6]:%d [7]:%d [8]:%c\n",buf,buf[6],buf[7],buf[8]);

    return 0;
}
char *mystrcpy(char *dest,const char *src)
{
    int i;
    for(i=0;src[i]!='\0';i++)
    {
         dest[i]=src[i];
    }
    dest[i]=src[i];//'\0'
    return dest;
}
