
#include <stdio.h>
#include <string.h>

char *mystrcat(char *dest,const char *src);

int main(void)
{
    char buf[64],s[]="hello uplooking!";
    char *t;

#if 1
    strcpy(buf,"abcde");//
    printf("buf:%s\n",buf);

    //append
    t=strcat(buf,s);
    printf("t:%p buf:%p\n",t,buf);
    printf("buf:%s\n",buf);
#else
    //strcat strcpy返回的作用:可实现函数参数表达式
    strcat(strcat(strcpy(buf,"abcde"),s),"112233");
    printf("buf:%s\n",buf);
    printf("buf:%s\n",buf);
#endif //

    return 0;
}
char *mystrcat(char *dest,const char *src)
{
    int i,j;
    //找dest '\0'
    for(i=0;dest[i]!='\0';i++)
    {
        ;//empty
    }
    //
    for(j=0;src[j]!='\0';j++)
    {
       dest[i+j]=src[j];
    }
    dest[i+j]=src[j];//'\0'

    return dest;
}
