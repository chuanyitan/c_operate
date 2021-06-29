
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct stduent{
     int    id;
     char   name[32];
     struct list_head   tt;
}Student_t;

int initStudent(Student_t *s);
void travelList(struct list_head *h);
void delByIdOne(struct list_head *h,int id);
void delById(struct list_head *h,int id);

int main(void)
{
     //struct list_head  head={&head,&head};
     //struct list_head  head=LIST_HEAD_INIT(head);
     LIST_HEAD(head);

     Student_t  *one;
     while(1)
     {
         one=malloc(sizeof(Student_t));
         assert(one!=NULL);
         if(initStudent(one)==-1)
               break;
         //list_add(&one->tt,&head);
         list_add_tail(&one->tt,&head);
     }
     //
     travelList(&head);

     printf("input del id:");
     int  id;
     scanf("%d",&id);
     //delByIdOne(&head,id);
     delById(&head,id);

     travelList(&head);

     return 0;
}
void delById(struct list_head *h,int id)
{
    struct list_head *i,*next;
    Student_t *s;

    list_for_each_safe(i,next,h)
    {
         s=list_entry(i,Student_t,tt);
         if(s->id==id)
         {
             list_del_init(i);
             free(s);
         }
    }
}
void delByIdOne(struct list_head *h,int id)
{
#if 0
     struct list_head *i;
     Student_t  *s;
     list_for_each(i,h)
     {
         s=list_entry(i,Student_t,tt);
         if(s->id==id)//del
         {
            list_del_init(i);
            free(s);
            break;
         }
     }
#else
     Student_t  *s;
     //list_for_each_entry(pos, head, member)
     list_for_each_entry(s,h,tt)
     {
         //printf("%d %s\n",s->id,s->name);
         if(s->id==id)
         {
             list_del_init(&s->tt);
             free(s);
              break;
         }
     }
#endif //

}
void travelList(struct list_head *h)
{
#if 0
     struct list_head *i;
     Student_t  *s;
     list_for_each(i,h)
     {
         s=list_entry(i,Student_t,tt);
         printf("%d %s\n",s->id,s->name);
     }
#else
     Student_t  *s;
     //list_for_each_entry(pos, head, member)
     list_for_each_entry(s,h,tt)
     {
         printf("%d %s\n",s->id,s->name);
     }
#endif //
}
///////////////////////////////////////////
int initStudent(Student_t *s)
{
      printf("id  :");
      scanf("%d",&s->id);
      if(s->id==-1)   return -1;

      printf("name:");
      scanf("%s",s->name);

      return 0;
}
