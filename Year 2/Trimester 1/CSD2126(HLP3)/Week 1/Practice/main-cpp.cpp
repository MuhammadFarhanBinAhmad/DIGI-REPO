#include <iostream>
#include "drawline.hpp"
#include "calc.h"

extern "C"
int real_main(void);

int main()
{
    real_main();

    int x{100},y{200};
    std::cout << draw_line(x,y) << " | " << add(x,y) << " | " << mul(x,y) << " | " << divi(x,y) << " | " << sub(x,y) << "\n";
}