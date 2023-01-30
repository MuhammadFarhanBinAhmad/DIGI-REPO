#include <stdio.h>
#include <limits.h>
#include <float.h>


/*int foo(int const array[], unsigned long elem_cnt) {
  int val = array[0];
  for (unsigned long i = 1; i < elem_cnt; ++i) 
  {
    val = (array[i] > val) ? array[i] : val;
  }

  return val;
}*/
int main(void)
{
    int i, grades[] = {-10,20,-30,40,-50};
for (i = sizeof(grades)/sizeof(grades[0]); i >= 0; --i) {
  printf("%d%s", grades[i],(i==0?"":","));
}
}