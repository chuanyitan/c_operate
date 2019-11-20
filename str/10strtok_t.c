//“ctrl+\ 可强行退出该程序”
//不可重入函数:某函数不能再同一进程多点(信号函数 线程 中断)同时发生调用
#include <stdio.h>
#include <string.h>
#include <signal.h>


void sigFunc(int signo)
{
    char str[]="start,aa.bb?cc dd ee:ff gg,end";
    char *t;
    printf("=======a sig recv=====\n");
    t=strtok(str,",.\t! :;?");
    while(t!=NULL)
    {
        printf("%s\n",t);
        t=strtok(NULL,",.\t! :;?");
    }
    printf("======sig func end=====\n");
}

int main(void)
{
    char s[]="hello;king.how are;you";
    char *t;

    //发生SIGINT信号时 调用sigFunc函数  当按ctrl+c触发SIGINT信号
    signal(SIGINT,sigFunc);

    //分割时 分割点将改变为'\0'
    t=strtok(s,",?.; !");
    while(1)
    {
       if(t==NULL)   break;//分完
       printf("%s\n",t);//分出的部分串

       sleep(1);
       //NULL:继续接着分割
       t=strtok(NULL,",?.; !");
    }

    printf("==============main over==========\n");
    return 0;
}
