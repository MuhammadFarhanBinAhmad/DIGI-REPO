// Visualization
// https://www.youtube.com/watch?v=WprjBK0p6rw
// QuickSort explain
// https://www.youtube.com/watch?v=Hoixgm4-P4M

#include <iostream>

int Partition(int arr[], int startIndex, int endIndex)
{
    // Set first item as pivot(can use RO3 but we use first for this one)
    int pivot = arr[startIndex];

    // left and right sublist are initially empty
    int middleIndex = startIndex;

    // Iterrate through arr[]
    for (int i = startIndex + 1; i <= endIndex; i++)
    {
        if (arr[i] < pivot)
        {
            // current item on left sublist prepare a
            middleIndex++;

            // arr[middleindex] is the member of right sublist
            // swap it to current item which is member of left list
            std::swap(arr[i], arr[middleIndex]);
        }
    }

    // The arr[middleIndex] item is member of left sublist
    // We can swap it with the pivot so that its in the correct position(between left and right sublist)
    std::swap(arr[startIndex], arr[middleIndex]);

    // return middle index to be use for the next quicksort
    return middleIndex;
}

void QuickSort(int arr[], int startIndex, int endIndex)
{
    // Only perform sort if end index > start index
    if (startIndex < endIndex)
    {
        // Retrive pivor position from Partition()
        // pivotIndex is the index of element that is already in correct position
        int pivotIndex = Partition(arr, startIndex, endIndex);

        // Sort left sublist
        QuickSort(arr, startIndex, pivotIndex - 1);

        // Sort right sublist
        QuickSort(arr, pivotIndex + 1, endIndex);
    }
}

int main()
{
    std::cout << "Quick Sort" << std::endl;
    // Initialize a new array
    int arr[] = {25, 21, 12, 40, 37, 43, 14, 28};
    int arrSize = sizeof(arr) / sizeof(*arr);
    // Display the initial array
    std::cout << "Initial array: ";
    for (int i = 0; i < arrSize; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    // Sort the array with QuickSort algorithm
    QuickSort(arr, 0, arrSize - 1);
    // Display the sorted array
    std::cout << "Sorted array : ";
    for (int i = 0; i < arrSize; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    return 0;
}
