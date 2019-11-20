
#include <stdio.h>
#include <string.h>

char *mystrtok(char *s,const char *delim);

int main(void)
{
    char s[]="hello,,.,.;king.        how are;you";

    char *t;

    //分割时 分割点将改变为'\0'
    //t=strtok(s,",?.; !");
    t=mystrtok(s,",?.; !");
    while(1)
    {
       if(t==NULL)   break;//分完
       printf("%s\n",t);//分出的部分串

       //NULL:继续接着分割
       //t=strtok(NULL,",?.; !");
       t=mystrtok(NULL,",?.; !");
    }

    return 0;
}
char *mystrtok(char *s,const char *delim)
{
    static char *flag=NULL;
    char   *temp;
    int i,j,x,k;
    //
    if(s!=NULL)
    {
       flag=s;
    }

    if(flag==NULL)   return NULL;//分完
    //找分割点
    temp=flag;
    for(i=0;flag[i]!='\0';i++)
    {
        for(j=0;delim[j]!='\0';j++)
        {
            if(flag[i]==delim[j])//分割点
            {
                flag[i]='\0';
                //处理连续分割符号
                for(x=i+1;flag[x]!='\0';x++)
                {
                    for(k=0;delim[k]!='\0';k++)
                    {
                        if(flag[x]==delim[k])
                        {
                           flag[x]='\0';
                           break;
                        }
                    }
                    if(delim[k]=='\0')
                    {
                        flag=flag+x;
                        break;
                    }
                }
                return temp;
            }
        }
    }
    if(temp==flag)//没分割
    {
       flag=NULL;//标识分完
       return temp;
    }
}
