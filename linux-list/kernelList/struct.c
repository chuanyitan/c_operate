
#include <stdio.h>

//求type类型的结构体number成员的偏移量
#define     offset_t(type,number)    (unsigned long)&((type *)0)->number

//根据type类型结构的number成员地址ptr反推 该类型结构体的首地址
#define     container_of(ptr,type,number)  \
                 (type *)((char *)ptr-offset_t(type,number))

struct student{
    int    id;
    char   name[32];
    float  math;
    float  chinese;
    int    age;
};

int main(void)
{
     struct  student  one={.id=1,.name="king",.age=20,.math=55,.chinese=85.5};

     int  *ptr=&one.age;
     unsigned long offset;

     printf("ptr:%p  &one:%p\n",ptr,&one);

     //offset=(unsigned long)&((struct student *)0)->age;
     offset=offset_t(struct  student,age);
     printf("offset:%lu\n",offset);


     struct student *s;
     //s=(struct student *)((char *)ptr-offset);
     s=container_of(ptr,struct student,age);
     printf("s:%p &one:%p id:%d name:%s\n",s,&one,s->id,s->name);

     return 0;
}
