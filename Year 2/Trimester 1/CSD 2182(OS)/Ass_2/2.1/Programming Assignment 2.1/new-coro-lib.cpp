#include "new-coro-lib.h"
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <iostream>

namespace CORO
{

    void thd_init()
    {
        std::thread t(thd_yield);
        t.join();
    }
    // ThreadID new_thd(void *(*thd_function_t)(void *), void *param)
    // {
    // }
    // void thread_exit(void *ret_value)
    // {
    // }
    // // Continue on this
    // int wait_thread(ThreadID id, void **value)
    // {
    // }
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
        std::this_thread::yield();
    }
    void push_value(void *pushed_value)
    {
    }
    void pull_value(void **pulled_value)
    {
    }
}
