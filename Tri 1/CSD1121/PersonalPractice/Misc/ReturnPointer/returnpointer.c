#include <stdio.h>
//return address if highest value
int* max_ptr_cmp(int*x,int*y)
{
    return *x > *y?x:y;//compare value of x and y. The highest value address will be return
}
int main(void)
{
    int x= 30,y=20,*p_i = NULL;
    p_i = max_ptr_cmp(&x,&y);//p_i will point to the address with the highest value
    printf("%d\n",*p_i);
    if(p_i == &y)
    {
        printf("p_i is pointing to address of y");
    }
    if(p_i == &x)
    {
        printf("p_i is pointing to address of x");
    }
}