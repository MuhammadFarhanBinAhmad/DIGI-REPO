#include <iostream>

int main() {
    int a = 25;

    // Print the first term
    std::cout << "a1 = " << a << std::endl;

    for (int n = 1; n < 30; n++) 
    {
        if (a % 2 == 0) 
        {
            a = a / 2;
        } 
        else 
        {
            a = 3 * a + 1;
        }
        std::cout << "a" << n + 1 << " = " << a << std::endl;
    }

    return 0;
}