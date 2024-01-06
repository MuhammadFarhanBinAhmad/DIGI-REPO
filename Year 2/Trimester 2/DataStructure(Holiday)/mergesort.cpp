//Merge sort explain
//https://www.youtube.com/watch?v=4VqmGXwpLqc

#include <iostream>
#include <vector>

void Merge(int arr[], int startIndex, int middleIndex, int endIndex)
{
    // Total element present
    int totalElement = endIndex - startIndex + 1;

    // Temp array stored the merged array
    int *tempArray = new int[totalElement];

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

std::vector<int> Merge(std::vector<int>& left ,std::vector<int>& right )
{
    std::vector<int> temp;

    while(left.size() > 0 && right.size() > 0)
    {
        if (left[0] >right[0])
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
    size_t middle = a.size()/2;

    std::vector<int> left(a.begin(), a.begin() +middle);
    std::vector<int> right(a.begin() +middle,a.end());

    left = MergeSort(left);
    right = MergeSort(right);

    return Merge(left,right);
    
}

int main()
{
    //Method 1
    // std::cout << "Merge Sort" << std::endl;
    // // Initialize a new array
    // int arr[] = {7, 1, 5, 9, 3, 6, 8, 2};
    // int arrSize = sizeof(arr) / sizeof(*arr);
    // // Display the initial array
    // std::cout << "Initial array: ";
    // for (int i = 0; i < arrSize; ++i)
    //     std::cout << arr[i] << " ";
    // std::cout << std::endl;
    // // Sort the array with MergeSort algorithm
    // //MergeSort(arr, 0, arrSize - 1);
    // // Display the sorted array
    // std::cout << "Sorted array : ";
    // for (int i = 0; i < arrSize; ++i)
    //     std::cout << arr[i] << " ";
    // std::cout << std::endl;

    //Method 2
    std::vector<int> arr {7,1,5,9,3,6,8,2};
    std::cout << "Initial list\n";
    for (int a: arr)
    {
        std::cout << a << ' ';
    }
    std::cout << '\n';
    arr = MergeSort(arr);
    std::cout << "Sorted list\n";
    for (int a: arr)
    {
        std::cout << a << ' ';
    }
    std::cout << '\n';


    return 0;
}