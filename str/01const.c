
#include <stdio.h>

void showArray(const int *ar)
{
    int i;
    for(i=0;i<5;i++)
    {
       printf("%d ",ar[i]);
    }
    //ar[0]=11111;//错误：向只读位置‘*ar’赋值
    putchar('\n');
}

int main(void)
{
    int ar[5]={1,2,3,4,5};
    int a=10,b=20;
    //通过该指针不可改变所指空间
    const int *ptr=&a;//int const *ptr=&a;

    a=100;
    printf("a:%d b:%d ptr:%p *ptr:%d\n",a,b,ptr,*ptr);
    //*ptr=1000;//错误：向只读位置‘*ptr’赋值
    
    ptr=&b;
    printf("a:%d b:%d ptr:%p *ptr:%d\n",a,b,ptr,*ptr);
    //*ptr=200;//错误：向只读位置‘*ptr’赋值

    showArray(ar);

    ///////////////////////////////////////////////////////
    //限定指针变量本身不可改变
    int *const tt=&a;
    printf("a:%d b:%d tt:%p *tt:%d\n",a,b,tt,*tt);
    *tt=7788;
    printf("a:%d b:%d tt:%p *tt:%d\n",a,b,tt,*tt);

    //tt=&b;//错误：向只读变量‘tt’赋值

    return 0;
}
