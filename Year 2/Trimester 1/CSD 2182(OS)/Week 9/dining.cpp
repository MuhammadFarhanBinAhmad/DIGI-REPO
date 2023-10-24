#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <vector>
#include <chrono>
#include <sstream>
#include <memory>
 
class Philosopher
{
public:
    static int NTotal;
	  
    Philosopher()   {}
 
    Philosopher(int n, std::mutex *left, std::mutex *right) :
        number(n), leftF(left), rightF(right) { NTotal++; }
 
    void think()
    {
        action("think");
    }
 
    void eat()
    {
        if (leftF && rightF)
        {
            // lock_guard always hold the lock from the time 
            // it is locked(construction) to its destruction
            // unique_lock can be created without immediately locking, 
            // can unlock at any point in its existence, 
            // and can transfer ownership of the lock from one instance to another
            // create unique_locks, but don't lock yet
            std::unique_lock<std::mutex> left(*leftF, std::defer_lock);
            std::unique_lock<std::mutex> right(*rightF, std::defer_lock);
 
#if 0		
            //Locks the given Lockable objects lock1, lock2, ..., lockn 
            //using a deadlock avoidance algorithm to avoid deadlock	
            // lock both without a deadlock
            std::lock(left, right);
#else
            // You can implement the deadlock free version 
            // shown on the lecture slides.
            if ((number + 1) % NTotal > number ) {
			    left.lock();
			    right.lock();
            }
            else{
			    right.lock();
			    left.lock();
            }
#endif	
            action("eat");
 
            // unclock
            left.unlock();
            right.unlock();
        }
    }
 
    void action(std::string actionName)
    {
        std::cout << "Philosopher" << number << " starts action: " << actionName << std::endl;
 
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
 
        std::cout << "Philosopher" << number << " finished action: " << actionName << std::endl;
    }
 
    // run actions
    void run()
    {
        if (leftF && rightF)
        {
            for (int i = 0; i<2; i++)
            {
                think();
                eat();
            }
        }
    }
 
private:
    int number; 
    std::mutex *leftF;
    std::mutex *rightF;
};

int Philosopher::NTotal = 0; 

int main()
{
    int count = 5;
 
    std::vector< std::shared_ptr<std::mutex> > forks;
    for (int i = 0; i<count; i++) {
        forks.push_back(std::make_shared<std::mutex>());
    }
 
    std::vector< std::shared_ptr<Philosopher> > philosophers;
    for (int i = 0; i<count; i++) {
        // Each philosopher 2 forks 
        philosophers.push_back(
            std::make_shared<Philosopher>(
                i,
                forks[i].get(),
                forks[(i + 1) % count].get()
            )
        );
    }
 
    // running threads
    std::vector<std::thread> th;
    for (int i = 0; i < count; ++i) {
        th.push_back(std::thread(&Philosopher::run, philosophers[i]));
    }
 
    for (auto &t : th){
        t.join();
    }
 
    return 0;
}