// AlgorithmAnalysis_Ass1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <vector>

//Insertion Sort comparison
int I_comparisonCount = 0;
//Creates a sorted array by comparing current elemtn with the already sorted portion of the array
void InsertionSort(int arr[], int arrSize)
{
    int comparisonCount = 0; // Initialize a counter for comparisons
    // Outer loop iterates from the second element to the end of the array
    // The first element is considered sorted
    for (int i = 1; i < arrSize; i++)
    {
        int j = i;

        // Shift elements of the sorted portion to the right to make space for the current element
        while (j > 0)
        {
            comparisonCount++; // Increment the counter for each comparison

            if (arr[j - 1] > arr[j])
            {
                // Swap elements if they are in the wrong order
                std::swap(arr[j], arr[j - 1]);
            }
            else
            {
                // Break the loop early if no more swaps are needed
                break;
            }

            // Move one position to the left
            j = j - 1;
        }
    }

    // Print the number of comparisons made
    std::cout << "Total comparisons: " << comparisonCount << std::endl;

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
        I_comparisonCount++;

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
//Selection Sort works by repeatedly finding the minimum element from the unsorted part and putting it at the beginning. The algorithm makes comparisons to find the minimum element.
void SelectionSort(int* arr, int arrsize)
{
    int minIndex{};
    int comparisonCount = 0; // Initialize a counter for comparisons

    // Outer loop iterates through each element of the array except the last one
    for (int i = 0; i < arrsize - 1; i++)
    {
        minIndex = i;

        // Inner loop to find the smallest element in the unsorted portion of the array
        for (int j = i + 1; j < arrsize; j++)
        {
            comparisonCount++; // Increment the counter for each comparison

            // If a smaller element is found, update minIndex
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        // Swap the smallest element found with the current element
        std::swap(arr[i], arr[minIndex]);
    }

    // Print the number of comparisons made
    std::cout << "Total comparisons: " << comparisonCount << std::endl;
}
struct Item {
    int value;
    char label;
};

// Function for printing an array of Items
void PrintArray(Item arr[], int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        std::cout << "{" << arr[i].value << ", '" << arr[i].label << "'} ";
    }
    std::cout << std::endl;
}

// Stable Insertion Sort
void InsertionSortStable(Item arr[], int arrSize)
{
    int comparisonCount = 0;

    for (int i = 1; i < arrSize; i++)
    {
        Item key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].value > key.value)
        {
            comparisonCount++;
            arr[j + 1] = arr[j];
            j--;
        }
        comparisonCount++;
        arr[j + 1] = key;
    }

    std::cout << "Total comparisons (Stable Insertion Sort): " << comparisonCount << std::endl;
}

// Unstable Selection Sort
void SelectionSortUnstable(Item arr[], int arrSize)
{
    int comparisonCount = 0;

    for (int i = 0; i < arrSize - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < arrSize; j++)
        {
            comparisonCount++;
            if (arr[j].value < arr[minIndex].value)
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            std::swap(arr[i], arr[minIndex]);
        }
    }

    std::cout << "Total comparisons (Unstable Selection Sort): " << comparisonCount << std::endl;
}

int main()
{
    bool endAlgoCheck = false;
    bool endProgram = false;
    while (!endProgram)
    {
        int testToRun = 0;
        //0 = AlgorithmCheck
        //1 = StabilityCheck
        std::cout << "Pick test to run\n";
        std::cout << "0 - Algorithm check\n"
                  << "1 - Stable/Unstable check\n"
                  << "2 - EndProgram\n"
                  << "--------------------------------\n";
        std::cin >> testToRun;
        std::cout << "--------------------------------\n";
        switch (testToRun)
        {
        case 0:
            {
            while (!endAlgoCheck)
                {
                    //Comment out arr you wish to not test
                    //Sorted
                    //int arr[] = { 1,2,3,4,5,6 };
                    //Identical
                    //int arr[] = { 1,1,2,2,3,3 };
                    //Unsorted
                    int arr[] = { 2,6,4,1,3,5 };

                    int arrSize = sizeof(arr) / sizeof(*arr);
                    short sortingAlgo = 0;
                    std::cout << "Initial list\n";
                    for (int a : arr)
                    {
                        std::cout << a << ' ';
                    }
                    std::cout << '\n';

                    std::cout << "Select Sorting Algorithm\n";
                    std::cout << "0 - MergeSort\n";
                    std::cout << "1 - InsertionSort\n";
                    std::cout << "2 - SelectionSort\n";
                    std::cout << "--------------------------------\n";
                    std::cin >> sortingAlgo;
                    std::cout << "--------------------------------\n";

                    if (sortingAlgo < 0 || sortingAlgo > 2)
                    {
                        std::cout << "Invalid value\n";
                    }
                    else
                    {
                        switch (sortingAlgo)
                        {
                        case 0:
                            MergeSort(arr, 0, arrSize - 1);
                            std::cout << "Total comparisons: :" << I_comparisonCount << '\n';
                            I_comparisonCount = 0;//reset count
                            break;
                        case 1:
                            InsertionSort(arr, arrSize);
                            break;
                        case 2:
                            SelectionSort(arr, arrSize);
                            break;
                        default:
                            break;
                        }
                        std::cout << "--------------------------------\n";
                        std::cout << "Sorted list\n";
                        for (int a : arr)
                        {
                            std::cout << a << ' ';
                        }
                        std::cout << '\n';
                        std::cout << "--------------------------------\n";
                    }

                    char userChoice;
                    std::cout << "Do you want to rerun the algorithm check? (y/n): \n";
                    std::cout << "--------------------------------\n";
                    std::cin >> userChoice;
                    std::cout << "--------------------------------\n";
                    if (userChoice == 'n' || userChoice == 'N')
                    {
                        endAlgoCheck = true;
                    }
                }
            endAlgoCheck = false;
            break;
            }
        case 1:
            {
                Item arr1[] = { {4, 'a'}, {3, 'b'}, {4, 'c'}, {1, 'd'}, {2, 'e'}, {3, 'f'} };
                Item arr2[] = { {4, 'a'}, {3, 'b'}, {4, 'c'}, {1, 'd'}, {2, 'e'}, {3, 'f'} };

                int arrSize = sizeof(arr1) / sizeof(arr1[0]);

                // Print initial array
                std::cout << "Initial array:\n";
                PrintArray(arr1, arrSize);
                std::cout << "--------------------------------\n";
                // Run stable insertion sort
                std::cout << "\nRunning Stable Insertion Sort...\n";
                InsertionSortStable(arr1, arrSize);
                PrintArray(arr1, arrSize);  // Display sorted array

                // Print initial array again for Selection Sort
                std::cout << "\nReinitializing array for Unstable Selection Sort...\n";
                PrintArray(arr2, arrSize); // arr2 is a fresh copy

                // Run unstable selection sort
                std::cout << "\nRunning Unstable Selection Sort...\n";
                SelectionSortUnstable(arr2, arrSize);
                PrintArray(arr2, arrSize);  // Display sorted array
                std::cout << "\n--------------------------------\n";
                break;
            }
        case 2:
            {
                endProgram = true;
                break;
            }
        }
    }
    return 0;

}