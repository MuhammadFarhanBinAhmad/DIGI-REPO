#include "new-coro-lib.h"

#include <iostream>
#include <ucontext.h>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>

#define ONE_MEGABYTE 1048576

namespace CORO
{
    enum Thread_State
    {
        RUNNING,
        READY,
        WAITING,
        START,
        DONE
    };

    static ThreadID Counter  = 0;

    struct ThreadControlBlock
    {
        ThreadID Target_Thread = 0;
        ThreadID Current_Thread = 0;

        ThreadState State;

        void *arg;
        void* ret;

        void *stack;
        void *base;

        void *(*funcpointer)(void *);

        ThreadControlBlock():Current_Thread(Counter)
        {
            Counter++;
        }
    };

    int currentThreadID = 0;
    int nextThreadID = 1;
    bool initialized = false; // Added to track library initialization
    ucontext_t* currentContext = nullptr;
    std::vector<ThreadControlBlock> threadsList;
    ThreadControlBlock currThread;
    std::queue<int> readyQueue;
    std::mutex mutex;
    std::condition_variable cv;

    // void schedule()
    // {
    //     //got thread in list
    //     if (!readyQueue.empty())
    //     {
    //         int nextThreadID = readyQueue.front();
    //         readyQueue.pop();

    //         if (threadsList[nextThreadID].state != WAITING)
    //         {
    //             if (currentContext != nullptr)
    //             {
    //                 int currentThreadID = currentContext->uc_link == nullptr ? 0 : ((ThreadControlBlock*)currentContext->uc_link)->thread_id;
    //                 threadsList[currentThreadID].state = READY;
    //                 readyQueue.push(currentThreadID); // Re-add the current thread to the ready queue
    //             }

    //             currentContext = &threadsList[nextThreadID].context;
    //             threadsList[nextThreadID].state = RUNNING;
    //             swapcontext(&threadsList[0].context, &threadsList[nextThreadID].context);
    //         }
    //         else
    //         {
    //             currentContext = &threadsList[nextThreadID].context;
    //             threadsList[nextThreadID].state = RUNNING;
    //             setcontext(&threadsList[nextThreadID].context);
    //         }
    //     }
    //     else
    //     {
    //         // No threads in the ready-to-run queue, check if there are newly created threads
    //         if (currentThreadID != 0)
    //         {
    //             threadsList[currentThreadID].state = READY;
    //             readyQueue.push(currentThreadID); // Re-add the current thread to the ready queue
    //         }

    //         // Select the next newly created thread to run (FIFO)
    //         if (currentThreadID < nextThreadID)
    //         {
    //             currentThreadID++;
    //             threadsList[currentThreadID].state = RUNNING;
    //             swapcontext(&threadsList[0].context, &threadsList[currentThreadID].context); // Use swapcontext instead of setcontext
    //         }
    //     }
    // }

    void thd_init()
    {
        // Create the initial main thread and set its context
        // ThreadControlBlock main_tcb;
        // std::thread t(thd_yield);
        // t.join();
        threadsList.push_back(new ThreadControlBlock());
        threadsList.back().base = new char[ONE_MEGABYTE];

        threadsList.back().stack = (char*)(threadsList.back().base) + ONE_MEGABYTE;

        currThread = threadsList.front();

        currThread.State = RUNNING;
        
    }

    ThreadID new_thd(void *(*thd_function_t)(void *), void *param)
    {
        // Lock mutex because below is a critical section
        std::unique_lock<std::mutex> lock(mutex);

        threadsList.push_back(new ThreadControlBlock());
        threadsList.back().arg = param;
        threadsList.back().funcpointer = thd_function_t;


        threadsList.back().base = new char[ONE_MEGABYTE];
        threadsList.back().stack = new (char*)(threadsList.back().base) + ONE_MEGABYTE;

        


    }

    void thread_exit(void *ret_value)
    {
        threadsList[currentThreadID].return_value = ret_value;
        threadsList[currentThreadID].state = DONE;

        schedule(); // Yield control to another thread if available in the ready queue
    }

    int wait_thread(ThreadID id, void **value)
    {
        // check if ID is valid
        if (id <= 0 || id >= nextThreadID)
        {
            return NO_THREAD_FOUND;
        }

        // make ref to thread and check the status
        ThreadControlBlock &tcb = threadsList[id];
        if (tcb.state == DONE)
        {
            *value = tcb.return_value;
            return WAIT_SUCCESSFUL;
        }
        else
        {
            int current_Thread = currentThreadID;
            currentThreadID = id;
            tcb.state = READY;
            // swapcontext(&tcb.context,&threadsList[current_Thread].context);
            schedule();
            *value = tcb.return_value;
            return WAIT_SUCCESSFUL;
        }
    }

    void thd_yield()
    {
        int currentThread = currentThreadID;
        readyQueue.push(currentThread);
        threadsList[currentThread].state = READY;

        schedule();
    }

    // void push_value(void *pushed_value) {
    //     // Implement as needed
    // }

    // void pull_value(void **pulled_value) {
    //     // Implement as needed
    // }
}
