//“ctrl+\ 可强行退出该程序”
//不可重入函数:某函数不能再同一进程多点(信号函数 线程 中断)同时发生调用
#include <stdio.h>
#include <string.h>
#include <signal.h>


void sigFunc(int signo)
{
    char str[]="start,aa.bb?cc dd ee:ff gg,end";
    char *t,*temp=str;
    printf("=======a sig recv=====\n");
    while(1)
    {
        t=strsep(&temp,",.\t! :;?");
        if(t==NULL)  break;

        printf("%s\n",t);
    }
    printf("======sig func end=====\n");
}

int main(void)
{
    char s[]="hello;king.how are;you";
    char *t,*temp=s;

    //发生SIGINT信号时 调用sigFunc函数  当按ctrl+c触发SIGINT信号
    signal(SIGINT,sigFunc);

    while(1)
    {
       t=strsep(&temp,",?.; !");
       if(t==NULL)   break;//分完
       printf("%s\n",t);//分出的部分串
       sleep(1);
    }

    printf("==============main over==========\n");
    return 0;
}
