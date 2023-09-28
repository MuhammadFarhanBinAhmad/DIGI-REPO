#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

const int BUFFER_SIZE = 5; // Size of the shared buffer

std::queue<int> buffer; // Shared buffer
std::mutex mtx; // Mutex to protect the buffer
std::condition_variable bufferEmpty; // Condition variable for buffer empty
std::condition_variable bufferFull; // Condition variable for buffer full

void producer() {
    for (int i = 1; i <= 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate some work
        {
            std::unique_lock<std::mutex> lock(mtx);
            while (buffer.size() == BUFFER_SIZE) {
                std::cout << "BUFFER FULL\n";
                bufferFull.wait(lock);//If not declare and place to protect,will this while will be called multiple time till condition is no longer met
                //Basically if full, will wait till no longer need to wait
            }
            buffer.push(i);
            std::cout << "Produced: " << i << std::endl;
        }
        bufferEmpty.notify_one();
    }
}

void consumer() {
    for (int i = 1; i <= 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(600)); // Simulate some work
        {
            //std::unique_lock<std::mutex> lock(mtx);
            while (buffer.empty()) {
                std::cout << "BUFFER EMPTY\n";
                bufferEmpty.wait(lock);
            }
            int item = buffer.front();
            buffer.pop();
            std::cout << "Consumed: " << item << std::endl;
        }
        bufferFull.notify_one();
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    // Waiting for the created thread to terminate
    producerThread.join();
    consumerThread.join();

    return 0;
}
