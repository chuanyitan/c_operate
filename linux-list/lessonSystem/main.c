/*
 * 用内核链表算法实现简单的修课系统模型(十字/交叉链表)
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"

#define     SIZE      32

enum key{
    UP,
    DOWN,
    ENTER,
    UNKNOW,
};
enum{
   EN_ADD_STU,
   EN_QUE_LES,
   EN_QUE_STU,
   EN_DEL_STU,
   EN_EXIT,
};

typedef struct{
     int   lesId,lesCount;//课程编号与被选修人数
     char  lesName[SIZE];

     Klist_t   lesNext;//课程链表
     Klist_t   selected;//课程被选修的链表头
}Lesson_t;

typedef struct{
     int   stuId,stuCount;//学号 与选修科目数
     char  stuName[SIZE];

     Klist_t   stuNext;//学生链表
     Klist_t   select; //学生选修课程链表头
}Student_t;
//关联学生与课程的公共节点
typedef struct{
     Student_t  *s;//指向学生节点的指针
     Lesson_t   *l;//指向课程节点的指针

     Klist_t    stuList;//学生选修课程链表
     Klist_t    lesList;//课程被选修链表
}Public_t;
//////////////////////////////////////////////
int isTrue(void);
void anyKey(void);
void showMenus(char *menus[],int idx);
int getInput(void);
int  getSelect(void);
//////////////////////////////////////////////
void initLessonInfo(Klist_t *LH);
int  addStudentInfo(Klist_t *SH,Klist_t *LH);
void selectLesson(Student_t *stup,Klist_t *LH);
//根据编号查询课程信息(编号唯一)
void queryLesson(Klist_t *LH);
//根据姓名查询学生(姓名非唯一)
void queryStudent(Klist_t *SH);
//根据姓名删除学生(姓名非唯一)
void deleteStudent(Klist_t *SH);
/////////////////////////////////////////////


int main(void)
{
     LIST_HEAD(lesHead);//初始化课程链表头
     LIST_HEAD(stuHead);//初始化学生链表头
     int  loop=1,type;

     system("clear");
     //初始化课程信息
     initLessonInfo(&lesHead);
     while(loop)
     {
         type=getSelect();//显示菜单 并获取选择
         switch(type){
            case EN_ADD_STU:addStudentInfo(&stuHead,&lesHead);break;
            case EN_QUE_LES:queryLesson(&lesHead);break;
            case EN_QUE_STU:queryStudent(&stuHead);break;
            case EN_DEL_STU:deleteStudent(&stuHead);break;
            case EN_EXIT   :loop=0;break;
         }
     }

     return 0;
}
int addStudentInfo(Klist_t *SH,Klist_t *LH)
{
     Student_t  *stup;
     char  buf[SIZE],*t;

     stup=malloc(sizeof(Student_t));
     if(stup==NULL)
     {
         printf("\033[31m[Add Student Info Failed,Try Again]\033[0m\n");
         anyKey();
         return -1;
     }
     printf("学号:");
     fgets(buf,SIZE,stdin);
     stup->stuId=atoi(buf);

     printf("姓名:");
     fgets(stup->stuName,SIZE,stdin);
     t=strchr(stup->stuName,'\n');
     if(t)  *t='\0';
    
     stup->stuCount=0;
     //初始化学生选修课程链表头
     INIT_LIST_HEAD(&stup->select);
     //将该学生节点加入到学生链表
     list_add_tail(&stup->stuNext,SH);

     //遍历课程询问是否选修
     selectLesson(stup,LH);
     return 0;
}
void selectLesson(Student_t *stup,Klist_t *LH)
{
     Klist_t  *i;
     Lesson_t *lp;
     Public_t *it;

     printf("\033[31m[是否选修y/n]\033[0m\n");
     list_for_each(i,LH)
     {
        lp=list_entry(i,Lesson_t,lesNext);
        //打印课程信息
        printf("%s:",lp->lesName);
        if(isTrue())
        {
            it=malloc(sizeof(Public_t));
            if(it==NULL)
            {
              printf("\033[1A%s:y \033[31m(Failed)\033[0m\n",lp->lesName);
            }
            else
            {
              printf("\033[1A%s:y \033[32m(Success)\033[0m\n",lp->lesName);
              it->s=stup;//学生指针指向该学生
              it->l=lp;  //课程指针指向该课程
              stup->stuCount++;
              lp->lesCount++;
              //将该接点加入学生选修链表
              list_add_tail(&it->stuList,&stup->select);
              //将该接点加入课程被选修链表
              list_add_tail(&it->lesList,&lp->selected);
            }
        }
     }
     anyKey();
}

void initLessonInfo(Klist_t *LH)
{
     int  idx;
     char *t,buf[SIZE];
     Lesson_t  *one;

     printf("[输入课程名,以NULL结束]\n");
     for(idx=1000;;idx++)
     {
         printf("%d:",idx);
         fgets(buf,SIZE,stdin);
         if(strncmp(buf,"NULL",4)==0)
         {
             break;
         }
         t=strchr(buf,'\n');
         if(t)  *t='\0';
         //建立课程节点
         one=malloc(sizeof(Lesson_t));
         assert(one!=NULL);
         //初始化基本信息
         one->lesId   =idx;
         one->lesCount=0;
         strcpy(one->lesName,buf);
         //初始化课程被选修链表头
         INIT_LIST_HEAD(&one->selected);
         //将该课程节点追加到课程链表
         list_add_tail(&one->lesNext,LH);
     }
}
//根据编号查询课程信息
void queryLesson(Klist_t *LH)
{
    char buf[SIZE];
    int  idx;
    Klist_t  *i,*j;
    Lesson_t *lp;


    if(list_empty(LH))
    {
        printf("\033[31m没有任何课程信息!!!!\033[0m\n");
        anyKey();
        return;
    }

    printf("课程编号:");
    fgets(buf,SIZE,stdin);
    idx=atoi(buf);

    list_for_each(i,LH)
    {
       lp=container_of(i,Lesson_t,lesNext);
       if(lp->lesId==idx)
       {
           printf("\033[35m编号:%d   名称:%s\033[0m\n",lp->lesId,lp->lesName);
           printf("\033[36m选修人数:%d\033[0m\n",lp->lesCount);
           if(!list_empty(&lp->selected))
           {
               Public_t  *it;
               //遍历被选修链表
               list_for_each(j,&lp->selected)
               {
                  it=container_of(j,Public_t,lesList);
                  printf("%s ",it->s->stuName);
               }
               putchar('\n');
           }
           break;
       }
    }
    if(i==LH)
    {
       printf("\033[31m没有编号[%d]课程信息!\033[0m\n",idx);
    }
    anyKey();
}
void queryStudent(Klist_t *SH)
{
    char name[SIZE],*t;
    Student_t  *sp;
    int  flag=0;

    if(list_empty(SH))
    {
        printf("\033[31m没有任何学生信息!!!!\033[0m\n");
        anyKey();
        return;
    }
    printf("学生姓名:");
    fgets(name,SIZE,stdin);
    t=strchr(name,'\n');
    if(t)  *t='\0';
    //遍历学生链表
    list_for_each_entry(sp,SH,stuNext)
    {
        if(strcmp(sp->stuName,name)==0)
        {
            flag=1;
            printf("\033[35m学号:%d   姓名:%s\033[0m\n",sp->stuId,sp->stuName);
            printf("\033[36m选修科目数:%d\033[0m\n",sp->stuCount);
            if(!list_empty(&sp->select))
            {
                Public_t  *it;
                list_for_each_entry(it,&sp->select,stuList)
                {
                   printf("%s ",it->l->lesName);
                }
                printf("\n----------------------\n");
            }
        }
    }
    if(flag==0)
    {
       printf("\033[31m没有姓名[%s]学生信息!\033[0m\n",name);
    }
    anyKey();
}

//根据姓名删除学生(姓名非唯一)
void deleteStudent(Klist_t *SH)
{
    char name[SIZE],*t;
    Student_t  *sp;
    int  flag=0;
    Klist_t  *i,*next;
    Public_t  *it;

    if(list_empty(SH))
    {
        printf("\033[31m没有任何学生信息!!!!\033[0m\n");
        anyKey();
        return;
    }
    printf("学生姓名:");
    fgets(name,SIZE,stdin);
    t=strchr(name,'\n');
    if(t)  *t='\0';
    //遍历学生链表
    list_for_each_safe(i,next,SH)
    {
       sp=container_of(i,Student_t,stuNext);
       if(strcmp(sp->stuName,name)==0)
       {
            flag=1;
            printf("\033[35m学号:%d   姓名:%s\033[0m\n",sp->stuId,sp->stuName);
            printf("\033[36m选修科目数:%d\033[0m\n",sp->stuCount);
            if(!list_empty(&sp->select))
            {
                list_for_each_entry(it,&sp->select,stuList)
                {
                   printf("%s ",it->l->lesName);
                }
                putchar('\n');
            }
            //////////////////////////////////////////////
            printf("\033[31m[是否删除y/n]:\033[0m");
            if(isTrue())
            {
                Klist_t *t,*n;
                //销毁该学生选修课程链表
                list_for_each_safe(t,n,&sp->select)
                {
                   it=container_of(t,Public_t,stuList);
                   //将该节点从课程被选修链表中删除
                   it->l->lesCount--;
                   list_del_init(&it->lesList);
                   free(it);
                }
                //将该学生节点从学生链表中删除
                list_del_init(i);
                free(sp);
            }
       }
    }
    if(flag==0)
    {
        printf("\033[31m没有姓名[%s]学生信息!\033[0m\n",name);
        anyKey();
    }
}

////////////////////////////////////////////////////////////////////
int getInput(void)
{
    char ch;
    ch=getchar();
    if(ch=='\033' && getchar()=='[')
    {
       switch(getchar()){
           case 'A':return UP;
           case 'B':return DOWN;
       }
    }
    else if(ch=='\n')   return ENTER;
    return UNKNOW;
}
int  getSelect(void)
{
    char *menus[]={"  注册学生  ","  查询课程  ","  查询学生  ","  删除学生  ","  退    出  ",NULL};
    int  loop=1,type;
    static int idx=0;//标识选中的选项

    system("stty -icanon");
    system("stty -echo");
    while(loop)
    {
        showMenus(menus,idx);
        type=getInput();
        switch(type){
           case UP   :if(idx>0)  idx--;break;
           case DOWN :if(menus[idx+1]!=NULL)  idx++;break;
           case ENTER:loop=0;break;
        }
    }
    system("stty echo");
    system("stty icanon");
    return idx;
}

void showMenus(char *menus[],int idx)
{
    int i;
    system("clear");

    for(i=0;menus[i];i++)
    {
        if(i==idx){
            printf("\033[44;37m%s\033[0m\n",menus[i]);
        }else{
            printf("\033[47;30m%s\033[0m\n",menus[i]);
        }
    }
}
void anyKey(void)
{
    system("stty -icanon");
    system("stty -echo");
    printf("\n\033[32m[Any Key Continue]\033[0m\n");
    getchar();
    system("stty echo");
    system("stty icanon");
}
int isTrue(void)
{
    char buf[SIZE];
    fgets(buf,SIZE,stdin);
    if(buf[0]=='y'||buf[0]=='Y')
       return 1;

    return 0;
}
