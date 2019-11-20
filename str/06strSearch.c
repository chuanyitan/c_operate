//
#include <stdio.h>
#include <string.h>

char *mystrchr(const char *s,int c);
char *mystrrchr(const char *s,int c);
char *mystrstr(const char *s,const char *child);

int main(void)
{
    char s[]={"hello uplooking how are you!"};
    char *t;

    printf("s:%s\n",s);

    //t=strchr(s,'l');
    t=mystrchr(s,'l');
    if(t==NULL){
        printf("strchr:Not Found.\n");
    }else{
        printf("strchr:%s\n",t);
    }

    ///////////////////////////////////
    //t=strrchr(s,'l');
    t=mystrrchr(s,'l');
    if(t==NULL){
        printf("strrchr:Not Found.\n");
    }else{
        printf("strrchr:%s\n",t);
    }


    //t=strstr(s,"look");
    t=mystrstr(s,"look");
    if(t==NULL){
        printf("strstr:Not Found.\n");
    }else{
        printf("strstr:%s\n",t);
    }
    return 0;
}
char *mystrchr(const char *s,int c)
{
    int i;
    for(i=0;s[i]!='\0';i++)
    {
        if(s[i]==c)
        {
           //return (char *)&s[i];
           return (char *)(s+i);;
        }
    }
    return NULL;
}
char *mystrrchr(const char *s,int c)
{
    int i;
    char *temp=NULL;
    for(i=0;s[i]!='\0';i++)
    {
        if(s[i]==c)
        {
           //temp=(char *)&s[i];
           temp=(char *)(s+i);
        }
    }
    return temp;
}
char *mystrstr(const char *s,const char *child)
{
     int i,j;

     for(i=0;s[i]!='\0';i++)
     {
        for(j=0;child[j];j++)
        {
           if(s[i+j]!=child[j])
              break;
        }
        if(child[j]=='\0')
        {
            return (char *)(s+i);
        }
     }
     return NULL;
}

