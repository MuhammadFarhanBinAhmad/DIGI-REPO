#include <iostream>

//Insertion sort visualize
//https://www.youtube.com/watch?v=Q1JdRUh1_98
//Insertion sort explain
//https://www.youtube.com/watch?v=JU767SDMDvA

void InsertionSort(int arr[], int arrSize)
{
    // // iterate all element
    // for (int i = 0; i < arrSize; ++i)
    // {
    //     // set the current element as ref val
    //     int ref_Value = arr[i];

    //     // variable to shift the element to right position
    //     int j{};

    //     // iterate through the sorted elements
    //     // to insert the reference value
    //     for (j = i - 1; j >= 0; --j)
    //     {
    //         // if value of curr index is greater,move curr
    //         // value to the right side
    //         // else put the ref value in the current index
    //         if (arr[j] > ref_Value)
    //         {
    //             arr[j + 1] = arr[j];
    //         }
    //         //break so as not to replace the other value in the sorted list
    //         else
    //         break;

    //     }
    //     // line to put reference value in the current index
    //     // in the current index
    //     arr[j + 1] = ref_Value;
    //     // std::cout << "Ref value: " << ref_Value << '\n';
    // }

    for(int i =1; i < arrSize;i++)
    {
        int j = i;
        while(j >0 && arr[j-1] > arr[j])
        {
            std::swap(arr[j],arr[j-1]);
            j = j-1;
        }
    }

}

int main()
{
    std::cout << "Insertion Sort" << '\n';
    // Initialize a new array
    int arr[] = {43, 21, 26, 38, 17, 30};
    int arrSize = sizeof(arr) / sizeof(*arr);
    // Display the initial array
    std::cout << "Initial array: ";
    for (int i = 0; i < arrSize; ++i)
        std::cout << arr[i] << " ";
    std::cout << '\n';
    // Sort the array with InsertionSort algorithm
    InsertionSort(arr, arrSize);
    // Display the sorted array
    std::cout << "Sorted array : ";
    for (int i = 0; i < arrSize; ++i)
        std::cout << arr[i] << " ";
    std::cout << '\n';
    return 0;
}
