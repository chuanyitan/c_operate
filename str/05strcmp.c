
#include <stdio.h>
#include <string.h>

int mystrcmp(const char *s1,const char *s2);

int main(void)
{
    char s1[]="hello";
    char *s2 ="hello";
    int  ret;

    ret=strcmp(s1,s2);
    //ret=mystrcmp(s1,s2);
    printf("ret:%d\n",ret);

    char name[64];
    printf("input user name:");
    scanf("%s",name);
    if(strcmp(name,"root")==0){
       printf("超级用户.\n");
    }else{
       printf("普通用户.\n");
    }
    return 0;
}
int mystrcmp(const char *s1,const char *s2)
{
    int i;
    for(i=0;s1[i]!='\0';i++)
    {
         if(s1[i]!=s2[i])
            break;
    }
    return s1[i]-s2[i];
}
