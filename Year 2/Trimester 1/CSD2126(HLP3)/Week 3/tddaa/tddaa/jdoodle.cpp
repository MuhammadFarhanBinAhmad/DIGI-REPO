#include <iostream>

using namespace std;



// Function to deallocate a 3D array
// void deallocate(int ***ppp)
// {
//     int f = 0;
//     while (ppp[f] != nullptr) 
//     {
//         //delete[] ppp[f];
//         f++;
//     }
//     std::cout << f;
//     delete[] ppp;
// }

int main() 
{
    int F = 3; // Number of frame
    int R = 4; // Number of row
    int C = 5; // Number of row
    
    // Allocate memory for the 2D array
    int*** myArray = new int**[F];
    for (int f = 0; f < F; f++) 
    {
        myArray[f] = new int*[R];
        for (int r = 0; r < R; r++)
        {
            myArray[f][r] = new int[C];
        }
    }

    int counter =1;
    for (int f = 0; f < F; f++) 
    {
        for (int r = 0; r < R; r++)
        {
            for (int c= 0; c < C;c++)
            {
                myArray[f][r][c] = counter++;
            }
        }
    }
    
    for (int f = 0; f < F; f++) 
    {
        for (int r = 0; r < R; r++)
        {
            for (int c= 0; c < C;c++)
            {
                std::cout << myArray[f][r][c] << " ";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    
    //std::cout << Fs << " " << Rs << " " << Cs << '\n';
    //deallocate(myArray);

    return 0;

}