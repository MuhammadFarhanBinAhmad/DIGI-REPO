#include <iostream>
#include <vector>
#include <chrono>

std::vector<int> Recursion(std::vector<int> arr)
{
    int n = arr.size();
    if (n <= 1)
        return arr;

    int halfArr = n / 2;
    std::vector<int> left(arr.begin(), arr.begin() + halfArr);
    std::vector<int> right(arr.begin() + halfArr, arr.end());

    std::vector<int> result1 = Recursion(left);
    std::vector<int> result2 = Recursion(right);
    std::vector<int> result3 = Recursion(right);

    std::vector<int> combinedResult = result1;
    combinedResult.insert(combinedResult.end(), result2.begin(), result2.end());
    combinedResult.insert(combinedResult.end(), result3.begin(), result3.end());

    return combinedResult;
}

int main()
{
    std::vector<int> arr{};
    std::cout << "Enter the size of the array: ";
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
        arr.push_back(i);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::vector<int> result = Recursion(arr);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds" << std::endl;
}