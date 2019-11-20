
#include <stdio.h>
#include <string.h>

char *mystrsep(char **ptr,const char *delim);

int main(void)
{
    char s[]="hello king,how.are?you";
    char *t,*temp;

    temp=s;
    while(1)
    {
       printf("temp>>>%s\n",temp);//temp指向每次的分割点

       //t=strsep(&temp,", .?;!");
       t=mystrsep(&temp,", .?;!");
       if(t==NULL)   break;

       printf("%s\n",t);
    }

    return 0;
}
char *mystrsep(char **ptr,const char *delim)
{
    char *tmp;
    int  i,j;

    if(*ptr==NULL)   return NULL;//分完

    tmp=*ptr;
    for(i=0;(*ptr)[i]!='\0';i++)
    {
        for(j=0;delim[j]!='\0';j++)
        {
            if((*ptr)[i]==delim[j])//分割点
            {
                (*ptr)[i]='\0';
                *ptr=*ptr+i+1;//记录下一次的分割起点
                return tmp;
            }
        }
    }
    if(tmp==*ptr)//最后不刻再分部分
    {
         *ptr=NULL;//标识分完
        return tmp;
    }
}
