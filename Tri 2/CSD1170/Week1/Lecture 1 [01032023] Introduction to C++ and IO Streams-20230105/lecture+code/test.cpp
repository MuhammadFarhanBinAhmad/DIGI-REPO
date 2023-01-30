#include <iostream>
#include <fstream>


int main()
{
    std::fstream infile("test.txt",std::ofstream::out);

    infile << "Your mother";

    infile.close();
}