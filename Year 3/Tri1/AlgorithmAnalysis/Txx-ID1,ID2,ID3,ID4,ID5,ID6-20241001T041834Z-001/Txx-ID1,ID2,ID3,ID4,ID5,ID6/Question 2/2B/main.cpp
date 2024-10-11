#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

class Timer
{
	using clock = std::chrono::high_resolution_clock;
	using timePoint = std::chrono::time_point<clock>;
	timePoint StartTime_{};
	timePoint EndTime_{};
    bool IsRunning_{ false };
public:
	Timer()
    : StartTime_{}, EndTime_{}, IsRunning_{ false } {}
	~Timer() = default;

	void StartTimer()
    {
        IsRunning_ = true;
        StartTime_ = clock::now();
    }
	void StopTimer()
    {
        EndTime_ = clock::now();
        IsRunning_ = false;
    }

    double GetNanoSeconds() const
    {
        timePoint TimeNow{ (IsRunning_ ? clock::now() : EndTime_) };
        return std::chrono::duration<double, std::nano>(TimeNow - StartTime_).count();
    }

    double GetMicroSeconds() const
    {
        timePoint TimeNow{ (IsRunning_ ? clock::now() : EndTime_) };
        return std::chrono::duration<double, std::micro>(TimeNow - StartTime_).count();
    }

	double GetMiliSeconds() const
    {
        timePoint TimeNow{ (IsRunning_ ? clock::now() : EndTime_) };
        return std::chrono::duration<double, std::milli>(TimeNow - StartTime_).count();
    }
	double GetSeconds() const
    {
        timePoint TimeNow{ (IsRunning_ ? clock::now() : EndTime_) };
        return std::chrono::duration<double>(TimeNow - StartTime_).count();
    }

};

int Fibonacci(int n) {
	if (n <= 1)
		return n;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

void RunFibonacci()
{
    std::ifstream file("Fibonacci.txt");
    int value{};
    file >> value;
    std::cout << "============================================================" << std::endl
              << "Fibonacci(" << value << ") = ";
    Timer timer;
    timer.StartTimer();
    int ret = Fibonacci(value);
    timer.StopTimer();
    std::cout << ret << std::endl 
              << "============================================================" << std::endl
              << "Time taken: " << timer.GetMicroSeconds() << " micro seconds" << std::endl << std::endl;
              
    file.close();
}

int GetTarget()
{
    std::ifstream file("Target.txt");
    int target{};
    file >> target;
    file.close();
    return target;
}

class A1
{
    public:
        A1() = default;
        ~A1() = default;
        size_t size() const { return data_.size(); }

        void PrintData() const
        {
            std::cout << "Current Data:" << std::endl
                      << "============================================================";
            for (size_t i{}; i < size(); ++i)
            {
                if (i % 10 == 0)
                    std::cout << std::endl;
                std::cout << "[" << data_[i] << "]";
                if (i+1 < size())
                    std::cout << ", ";
            }
            std::cout << std::endl << "============================================================" << std::endl;
        }

        void Parse(const std::string& filename)
        {
            if (!data_.empty())
                data_.clear();
            std::ifstream file(filename);
            int value{};
            while (file >> value)
            {
                data_.push_back(value);
            }
            file.close();
        }

        void Sort()
        {
            std::sort(data_.begin(), data_.end());
        }

        int GetFirstElement() const { return data_.front(); } //O(1)

        int BinarySearch(int target) const //O(log(n))
        {
            int left = 0, right = data_.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (data_[mid] == target)
                    return mid;
                else if (data_[mid] < target)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            return -1;
        }
        int FindElement(int target) const //O(n)
        {
            for (size_t i{}; i < data_.size(); ++i)
            {
                if (data_[i] == target)
                    return i;
            }
            return -1;
        }
        void QuickSort(int low, int high) //O(nlog(n))
        {
            if (low < high) {
                int pi = partition(low, high); // Partitioning index

                QuickSort(low, pi - 1);  // Sort elements before partition
                QuickSort(pi + 1, high); // Sort elements after partition
            }
        }

        void BubbleSort() //O(n^2)
        {
            int n = data_.size();
            for (int i = 0; i < n - 1; i++) {
                // Last i elements are already in place
                for (int j = 0; j < n - i - 1; j++) {
                    if (data_[j] > data_[j + 1]) {
                        std::swap(data_[j], data_[j + 1]); // Swap if the element is greater than the next element
                    }
                }
            }
        }

        void Permutations() //O(n!)
        {
            std::vector<int> arr{};

            std::ifstream file("PermutationSize.txt");
            int size{};
            file >> size;
            file.close();
            if (size > (int)data_.size())
                size = (int)data_.size();
            for (int i{}; i < size; i++) {
                arr.push_back(data_[i]);
            }
            std::cout << "Permutations:" << std::endl;
            std::cout << "============================================================" << std::endl;

            std::cout << "Permutation Data:" << std::endl
                      << "============================================================" << std::endl;
            for (size_t i{}; i < arr.size(); ++i)
            {
                std::cout << "[" << arr[i] << "]";
                if (i+1 < arr.size())
                    std::cout << ", ";
            }
            std::cout << std::endl << "============================================================" << std::endl;
            
            std::cout << "Generating Permutations:" << std::endl;
            Timer timer;
            timer.StartTimer();
            generatePermutations(arr, 0, size-1);
            timer.StopTimer();
            std::cout << "============================================================" << std::endl;
            std::cout << "Time taken: " << timer.GetMicroSeconds() << " micro seconds" << std::endl << std::endl;
        }

        void generatePermutations(std::vector<int>& arr, int start, int end) {
            if (start == end) 
            {
                for (int i : arr) {
                    std::cout << i << " ";
                }
                std::cout << std::endl;
            }
            else 
            {
                for (int i = start; i <= end; i++) {
                    std::swap(arr[start], arr[i]);
                    generatePermutations(arr, start + 1, end);
                    std::swap(arr[start], arr[i]); // Backtrack to restore the original array
                }
            }
        }

    private:
        int partition(int low, int high) {
            int pivot = data_[high]; // Choosing the last element as the pivot
            int i = low - 1;       // Index of smaller element

            for (int j = low; j < high; j++) {
                if (data_[j] <= pivot) {
                    i++;
                    std::swap(data_[i], data_[j]);
                }
            }
            std::swap(data_[i + 1], data_[high]);
            return i + 1;
        }

        std::vector<int> data_;
};


int main()
{
    A1 prog;
    Timer t;
    /////////////////////////////O(1)/////////////////////////////////////
    prog.Parse("input.txt");
    prog.PrintData();
    std::cout << "O(1)\n";
    std::cout << "============================================================" << std::endl;
    std::cout << "GetFirstElement: ";
    t.StartTimer();
    const auto &firstElement = prog.GetFirstElement();
    t.StopTimer();
    std::cout << firstElement << std::endl;
    std::cout << "Time taken: " << t.GetMicroSeconds() << " micro seconds" << std::endl;
    std::cout << "============================================================" << std::endl << std::endl;

    /////////////////////////////O(log(n))/////////////////////////////////////
    //sort the data for binary search
    std::cout << "O(log(n))\n";
    std::cout << "============================================================" << std::endl;
    prog.Sort();
    prog.PrintData();
    int target = GetTarget();
    std::cout << "BinarySearch Target: " << target << std::endl;
    std::cout << "BinarySearch: ";
    t.StartTimer();
    const auto &index = prog.BinarySearch(target);
    t.StopTimer();
    if (index == -1)
        std::cout << "Target not found" << std::endl;
    else
        std::cout << "Target found at index: " << index << std::endl;
    std::cout << "Time taken: " << t.GetMicroSeconds() << " micro seconds" << std::endl << std::endl;

    /////////////////////////////O(n)/////////////////////////////////////
    std::cout << "O(n)\n";
    std::cout << "============================================================" << std::endl;
    prog.Parse("input.txt");
    prog.PrintData();
    std::cout << "FindElement Target: " << target << std::endl;
    std::cout << "FindElement: ";
    t.StartTimer();
    const auto &index2 = prog.FindElement(target);
    t.StopTimer();
    if (index2 == -1)
        std::cout << "Target not found" << std::endl;
    else
        std::cout << "Target found at index: " << index2 << std::endl;
    std::cout << "Time taken: " << t.GetMicroSeconds() << " micro seconds" << std::endl << std::endl;


    /////////////////////////////O(nlog(n))/////////////////////////////////////
    std::cout << "O(nlog(n))\n";
    std::cout << "============================================================" << std::endl;
    prog.Parse("input.txt");
    prog.PrintData();
    std::cout << "QuickSort: ";
    t.StartTimer();
    prog.QuickSort(0, prog.size()-1);
    t.StopTimer();
    prog.PrintData();
    std::cout << "Time taken: " << t.GetMicroSeconds() << " micro seconds" << std::endl << std::endl;

    /////////////////////////////O(n^2)/////////////////////////////////////
    std::cout << "O(n^2)\n";
    std::cout << "============================================================" << std::endl;
    prog.Parse("input.txt");
    prog.PrintData();
    std::cout << "BubbleSort: ";
    t.StartTimer();
    prog.BubbleSort();
    t.StopTimer();
    prog.PrintData();
    std::cout << "Time taken: " << t.GetMicroSeconds() << " micro seconds" << std::endl << std::endl;

    /////////////////////////////O(k^n)/////////////////////////////////////
    std::cout << "O(k^n)\n";
    RunFibonacci();

    /////////////////////////////O(n!)/////////////////////////////////////
    prog.Parse("input.txt");
    prog.Permutations();
    
    return 0;
}