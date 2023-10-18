#include "new-coro-lib.h"
#include <iostream>
#include <pthread.h>
#include <queue>
#include <ucontext.h>
#include <unordered_map>
#include <mutex>
#include <cstdlib>
#include <thread>

namespace CORO
{

    struct ThreadControlBlock
    {
        ucontext_t context; // POSIX context to store thread
        ThreadState state;  // ID
        void *return_value;
        unsigned thread_id; // Store the thread's unique ID
    };

    // Main thread
    ThreadControlBlock *current_Thread = nullptr;

    // Store all created queue here
    std::queue<ThreadControlBlock *> created_queue;

    // Queue for all thread thats ready to run
    std::queue<ThreadControlBlock *> ready_Queue;

    std::queue<void *> pusher_Queue; // queue to holf pushed value
    // Queue for suspended thread
    std::queue<ThreadControlBlock *> suspended_Puller;

    // Define a data structure to store TCBs associated with thread IDs
    std::unordered_map<unsigned, ThreadControlBlock> tcb_map;
    std::mutex tcb_mutex;

    const int MAX_THREADS = 10000;
    int next_thread_id = 1;

    void thd_init()
    {
    }
    ThreadID new_thd(void *(*thd_function_t)(void *), void *param)
    {
        // emsure thread safety when creating new threads
        std::lock_guard<std::mutex> lock(tcb_mutex);

        if (next_thread_id >= MAX_THREADS)
        {
            next_thread_id = 1; // replace
        }

        ThreadControlBlock current_TCB;

        current_TCB.thread_id = next_thread_id; // Assign a unique thread ID

        // 2^20 = 1048576
        // Basically 1MB(malaysia boleh :))
        current_TCB.context.uc_stack.ss_sp = malloc(1 << 20); // allocate memory
        current_TCB.context.uc_stack.ss_size = 1 << 20;

        if (current_TCB.context.uc_stack.ss_sp == nullptr)
        {
            return -1;
        }

        // Set up execution contxt for new thread
        getcontext(&current_TCB.context);
        makecontext(&current_TCB.context, (void (*)())thd_function_t, 1, param);

        // add new TCB  into map
        tcb_map[current_TCB.thread_id] = current_TCB;

        // push into map
        ready_Queue.push(&(tcb_map[current_TCB.thread_id]));

        next_thread_id++;

        return current_TCB.thread_id;
    }
    void thread_exit(void *ret_value)
    {
        // Lock mutex for thread safety
        std::lock_guard<std::mutex> lock(tcb_mutex);

        current_Thread->return_value = ret_value;

        // current_Thread->state = ThreadState::TERMINATED;
    }
    //Continue on this
    int wait_thread(ThreadID id, void **value)
    {
        // Lock the mutex for thread safety
        std::lock_guard<std::mutex> lock(tcb_mutex);

        // Find the TCB of the thread with the given thread ID
        auto it = tcb_map.find(id);

        if (it != tcb_map.end())
        {
            ThreadControlBlock &tcb = it->second;

            //if (tcb.state == ThreadState::TERMINATED)
            {
                // The thread has already terminated
                *value = tcb.return_value;

                // Free up the data structures associated with the terminated thread
                tcb_map.erase(it);

                return WAIT_SUCCESSFUL;
            }
            {
                // The thread has not yet terminated, so you should suspend and wait
                // Implement the suspension and waiting logic here, and then retrieve the value
            }
        }
        else
        {
            // The thread to be waited for is no longer a valid thread
            return NO_THREAD_FOUND;
        }

        // Implement the suspension and waiting logic here
        // Make sure to resume and retrieve the value after the thread completes

        return WAIT_SUCCESSFUL; // Return WAIT_SUCCESSFUL when done
    }
// current thread to yield the CPU for another thread to be scheduled
// Logic:
/*
A)Save the context of the current thread. You will need to determine what would
be the “context” of a thread. An example of information contained in the TCB:
3
 Stack pointer: Points to thread’s stack in the process
 Program counter
 State of the thread (running, ready, waiting, start, done)
 register values for thread
B)Call the scheduler or perform scheduling task. More details on scheduling in the
next section. Depending on the scheduler, another thread might run as a result.
C)If execution reaches beyond the call to the scheduler, it means that we can simply
return from the thd yield() function.
*/
void thd_yield()
{
    std::lock_guard<std::mutex> lock(tcb_mutex);
    // Save current context
    if (current_Thread)
    {
        getcontext(&(current_Thread->context)); // initialize the structure pointerd at by the ucp to get current active context

        // Add ready thread to the ready queue(i'm ready)
        ready_Queue.push(current_Thread);
    }

    // Check if queue if got thread. If got thread, then switch to the next thread
    if (!ready_Queue.empty())
    {
        current_Thread = ready_Queue.front();
        ready_Queue.pop(); // remove oldest member in queue
        // HOW TO SET STATE?
        // current_Thread->state = ThreadState::RUNNING;

        setcontext(&(current_Thread->context));
    }
}
void push_value(void *pushed_value)
{
    // Lock mutext for thread safety
    std::lock_guard<std::mutex> lock(tcb_mutex);

    if (suspended_Puller.empty())
    {
        // No puller. Go push value
        pusher_Queue.push(pushed_value);
    }
    else
    {
        // Got suspender puller. Wake (the f... up samurai) it up and push value
        ThreadControlBlock *puller = suspended_Puller.front();
        suspended_Puller.pop();
        puller->return_value = pushed_value;
        ready_Queue.push(puller);
    }

    thd_yield();
}
void pull_value(void **pulled_value)
{
    // Lock mutext for thread safety
    std::lock_guard<std::mutex> lock(tcb_mutex);

    if (pusher_Queue.empty())
    {
        suspended_Puller.push(current_Thread);
        thd_yield();
    }

    *pulled_value = pusher_Queue.front();
    pusher_Queue.pop();
}
}
