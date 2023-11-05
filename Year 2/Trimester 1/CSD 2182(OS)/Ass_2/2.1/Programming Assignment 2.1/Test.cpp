#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int turn = 1;

void thread1() {
    std::unique_lock<std::mutex> lock(mtx);
    for (int i = 0; i < 10; i++) {
        while (turn != 1) {
            cv.wait(lock);
        }
        std::cout << "SPIN1" << std::endl;
        turn = 2;
        cv.notify_all();
    }
}

void thread2() {
    std::unique_lock<std::mutex> lock(mtx);
    for (int i = 0; i < 10; i++) {
        while (turn != 2) {
            cv.wait(lock);
        }
        std::cout << "SPIN2" << std::endl;
        turn = 1;
        cv.notify_all();
    }
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    std::cout << "switching threads test DONE" << std::endl;

    return 0;
}
