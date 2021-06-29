
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//求type类型的结构体number成员的偏移量
#define     offset_t(type,number)    (unsigned long)&((type *)0)->number

//根据type类型结构的number成员地址ptr反推 该类型结构体的首地址
#define     container_of(ptr,type,number)  \
                 (type *)((char *)ptr-offset_t(type,number))

#define     travelList(h,pos)      \
               for(pos=h->next;pos!=h;pos=pos->next)


struct list_head{
     struct list_head  *prev,*next;
};

typedef struct student{
    int    id;
    char   name[32];
    struct list_head   list;
}Student_t;

int initStudent(Student_t *s);
//
void appendListHead(struct list_head *h,struct list_head *new);
void delListNode(struct list_head *it);


void mytravelList(struct list_head *h);
void delListById(struct list_head  *h,int id);

int main(void)
{
     struct list_head  head={.prev=&head,.next=&head};
     Student_t *one;
     
     while(1)
     {
        one=malloc(sizeof(Student_t));
        assert(one!=NULL);
        if(initStudent(one)==-1)
        {
            free(one);
            break;
        }

        appendListHead(&head,&one->list);
     }

     mytravelList(&head);

     printf("-------------------del----------------------\n");
     delListById(&head,2);

     mytravelList(&head);
     return 0;
}

void appendListHead(struct list_head *h,struct list_head *new)
{
     new->next=h->next;
     new->prev=h;
     new->next->prev=new;
     new->prev->next=new;
}
void mytravelList(struct list_head *h)
{
     struct list_head *i;
     Student_t  *s;
     travelList(h,i)
     {
        s=container_of(i,Student_t,list);
        printf("%d %s\n",s->id,s->name);
     }
}
void delListById(struct list_head  *h,int id)
{
     struct list_head *i;
     Student_t  *s;
     travelList(h,i)
     {
        s=container_of(i,Student_t,list);
        if(s->id==id)
        {
            delListNode(i);
            free(s);
            break;
        }
     }
}

void delListNode(struct list_head *it)
{
     it->next->prev=it->prev;
     it->prev->next=it->next;
     
     //
     it->next=it;
     it->prev=it;
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
