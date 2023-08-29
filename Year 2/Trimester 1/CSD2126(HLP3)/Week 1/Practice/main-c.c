#include <stdio.h>
#include "drawline.hpp"
#include "calc.h"

int real_main(void)
{
    int x = 10, y =20;

      printf("%d | %d | %d | %d | %d \n", draw_line(x, y), add(x, y), mul(x, y),divi(x,y),sub(x,y));

      return 0;

}