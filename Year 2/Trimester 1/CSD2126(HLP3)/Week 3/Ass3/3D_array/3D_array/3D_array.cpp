// 3D_array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void deallocate(int*** ppp)
{
    delete[] **ppp;
    delete[] *ppp;
    delete[] ppp;

}

int main()
{
    int F = 5;
    int R = 5;
    int C = 5;

    int* col = new int [F*R*C];
    int** row = new int* [F * R];
    int*** fra = new int** [F];

    for (int i = 0; i < F * R; i++)
    {
        row[i] = &col[i * C];
    }

    for (int i = 0; i < F ; i++)
    {
        fra[i] = &row[i * R];
    }


    //for (int f = 0; f < F; f++)
    //{
    //    arr[f] = new int* [R];
    //    for (int r = 0; r < R; r++)
    //    {
    //        arr[f][r] = new int[C];
    //    }
    //}

    int counter = 1;
    for (int f = 0; f < F; f++)
    {
        for (int r = 0; r < R; r++)
        {
            for (int c = 0; c < C; c++)
            {
                fra[f][r][c] = counter++;
            }
        }
    }

    for (int f = 0; f < F; f++)
    {
        for (int r = 0; r < R; r++)
        {
            for (int c = 0; c < C; c++)
            {
                std::cout << fra[f][r][c] << " ";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    deallocate(fra);

    #if defined(DEBUG) | defined(_DEBUG)
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
