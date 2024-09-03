// AlgorithmAnalysis_Ass1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>



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

    for (int i = 1; i < arrSize; i++)
    {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j])
        {
            std::swap(arr[j], arr[j - 1]);
            j = j - 1;
        }
    }

}
void Merge(int arr[], int startIndex, int middleIndex, int endIndex)
{
    // Total element present
    int totalElement = endIndex - startIndex + 1;

    // Temp array stored the merged array
    int* tempArray = new int[totalElement];

    // Index of left sub-array
    // arr[start -> middle]
    int leftIndex = startIndex;

    // Index of left sub-array
    // arr[middle=1 -> end]
    int rightIndex = middleIndex + 1;

    // Index of merged array
    int mergeIndex = 0;

    // Merge the 2 subarray
    while (leftIndex <= middleIndex && rightIndex <= endIndex)
    {
        if (arr[leftIndex] <= arr[rightIndex])
        {
            // Store left sub array's element if lower than right one
            tempArray[mergeIndex] = arr[leftIndex];

            // Go to next left subarray index
            leftIndex++;
        }
        else
        {
            // Store right sub array's element if lower than left one
            tempArray[mergeIndex] = arr[rightIndex];

            // Go to next right subarray index
            rightIndex++;
        }

        // Go to next merged array index
        mergeIndex++;
    }

    // If there're any remaining element in left subarray
    // that is not stored to merged array yet
    while (leftIndex <= middleIndex)
    {
        tempArray[mergeIndex] = arr[leftIndex];

        // go to next left subarray index
        leftIndex++;

        // Go to next merge array index
        mergeIndex++;
    }

    // If there're any remaining element in left rightarray
    // that is not stored to merged array yet
    while (rightIndex <= endIndex)
    {
        tempArray[mergeIndex] = arr[rightIndex];

        // go to next left subarray index
        rightIndex++;

        // Go to next merge array index
        mergeIndex++;
    }

    // Merged array are now sorted
    // Copy element to the original array
    for (int i = 0; i < totalElement; i++)
    {
        arr[startIndex + i] = tempArray[i];
    }

    delete[] tempArray;
}

void MergeSort(int arr[], int startIndex, int endIndex)
{
    // Only perform sort process if end index is hight than start index
    if (startIndex < endIndex)
    {
        // Find middle index
        int middleIndex = (startIndex + endIndex) / 2;

        // Sort left subarray
        // arr[start -> middle]
        MergeSort(arr, startIndex, middleIndex);

        // Sort right subarray
        // arr[middle+1 -> end]
        MergeSort(arr, middleIndex + 1, endIndex);

        // Merge left and right subarray together
        Merge(arr, startIndex, middleIndex, endIndex);
    }
}

std::vector<int> Merge(std::vector<int>& left, std::vector<int>& right)
{
    std::vector<int> temp;

    while (left.size() > 0 && right.size() > 0)
    {
        if (left[0] > right[0])
        {
            temp.push_back(right[0]);
            right.erase(right.begin());
        }
        else
        {
            temp.push_back(left[0]);
            left.erase(left.begin());
        }
    }

    //Left or right should be empty

    while (left.size() > 0)
    {
        temp.push_back(left[0]);
        left.erase(left.begin());
    }

    while (right.size() > 0)
    {
        temp.push_back(right[0]);
        right.erase(right.begin());
    }

    return temp;

}
std::vector<int> MergeSort(const std::vector<int>& a)
{

    if (a.size() <= 1)
        return a;

    size_t n = a.size();
    size_t middle = a.size() / 2;

    std::vector<int> left(a.begin(), a.begin() + middle);
    std::vector<int> right(a.begin() + middle, a.end());

    left = MergeSort(left);
    right = MergeSort(right);

    return Merge(left, right);

}
void SelectionSort(int* arr, int arrsize)
{
    int minIndex{};

    for (int i = 0; i < arrsize - 1; i++)
    {
        minIndex = i;

        for (int j = i + 1; j < arrsize; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        std::swap(arr[i], arr[minIndex]);
    }
}
int main()
{
    //std::vector<int> arr{ 7,1,5,9,3,6,8,2,9,2,3,4,1,2 };
    int arr[] = { 7,1,5,9,3,6,8,2,9,2,3,4,1,2 };
    int arrSize = sizeof(arr) / sizeof(*arr);
    short sortingAlgo = 0;
    std::cout << "Initial list\n";
    for (int a : arr)
    {
        std::cout << a << ' ';
    }
    std::cout << '\n';
    switch (sortingAlgo)
    {
        case 0:
        {
            MergeSort(arr, 0, arrSize - 1);
            break;
        }
        case 1:
        {
            InsertionSort(arr, arrSize);
            break;
        }
        case 2:
        {
            SelectionSort(arr, arrSize);
            break;
        }
    }
    //MergeSort(arr, 0, arrSize - 1 );
    //InsertionSort(arr, arrSize);
    //SelectionSort(arr, arrSize);
    std::cout << "Sorted list\n";
    for (int a : arr)
    {
        std::cout << a << ' ';
    }
    std::cout << '\n';


    return 0;
}