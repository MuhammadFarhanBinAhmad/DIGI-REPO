//Bubblesort explain
//https://www.youtube.com/watch?v=xli_FI7CuzA

#include <iostream>

void Bubblesort(int *arr,int arrsize)
{
    //Code 1:
    // bool isSwapped;

    // int unsortedElements = arrsize;

    // do
    // {
    //     isSwapped = false;

    //     for (int i = 0 ;  i < unsortedElements -1;i++)
    //     {
    //         if (arr[i] > arr [i+1])
    //         {
    //             std::swap(arr[i],arr[i+1]);
    //             isSwapped = true;
    //         }
    //     }
    //     --unsortedElements;
    // }

    // while(isSwapped);
    //Code 2:
    for (int i = 1 ; i < arrsize;i++)
    {
        for(int j = 0 ;j < arrsize-1;j++)
        {
            if (arr[j] > arr[j+1])
            {
                std::swap(arr[j],arr[j+1]);
            }
        }
    }
}

int main()
{
    std::cout << "BubbleSort\n";

    int arr[] = {43,21,26,38,17,30};
    int arrSize = sizeof(arr)/sizeof(*arr);

    std::cout << "InititalArray\n";
    for ( int i =0;i < arr[i];i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';

    Bubblesort(arr,arrSize);

    std::cout << "SortedArray\n";
    for ( int i =0;i < arr[i];i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}