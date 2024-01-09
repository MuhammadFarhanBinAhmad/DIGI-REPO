//Selectionsort
//https://www.youtube.com/watch?v=g-PGLbMth_g

#include <iostream>

void SelectionSort(int *arr,int arrsize)
{
    int minIndex{};

    for (int i =0 ;i < arrsize -1;i++)
    {
        minIndex = i;

        for (int j = i+1;j < arrsize;j++)
        {
            if(arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        std::swap(arr[i],arr[minIndex]);
    }
}

int main()
{
 std::cout << "Selection Sort" << '\n';
 // Initialize a new array
 int arr[] = {43, 21, 56, 78, 97, 30};
 int arrSize = sizeof(arr)/sizeof(*arr);

 // Display the initial array
 std::cout << "Initial array: ";
 for (int i = 0; i < arrSize; ++i)
 std::cout << arr[i] << " ";

 std::cout << '\n';

  SelectionSort(arr, arrSize);
 // Display the sorted array
 std::cout << "Sorted array : ";
 for (int i = 0; i < arrSize; ++i)
 std::cout << arr[i] << " ";

 std::cout << '\n';
 return 0;
}

