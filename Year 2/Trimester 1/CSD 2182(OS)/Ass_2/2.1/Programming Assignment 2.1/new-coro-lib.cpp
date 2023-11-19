/*!************************************************************************
\file   new-coro-lib.cpp
\author Muhammad Farhan Bin Ahmad(2200544)
\par    email: b.muhammadfarhan@digipen.edu
\par    Course: CSD 2182
\par    OS Part 2.1
\date   05-11-2023

\note   bless to my friend and senior psuedo code
        Also they say ucontext easier then asm. they lies. or maybe cause i suck

\brief 	To learn and understand context switching at some specific
        level using setcontext or inline assembly. The student who
        successfully completes this assignment will understand some
        analogy between the management of threads and the manaagement of processes
**************************************************************************/
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
    enum Thread_State : int
    {
        START,
        RUNNING,
        READY,
        WAITING,
        DONE
    };

    static ThreadID Counter = 0;

    struct ThreadControlBlock
    {
        ThreadID Target_Thread = 0;
        ThreadID Current_Thread = 0;

        Thread_State State;

        void *arg;
        void *ret;

        void *stack;
        void *base;

        void *(*funcpointer)(void *);

        ThreadControlBlock() : Current_Thread(Counter)
        {
            Counter++;
        }
    };
    
    
    // ALL SALAH
    //  int currentThreadID = 0;
    //  int nextThreadID = 1;
    //  bool initialized = false; // Added to track library initialization
    //  ucontext_t* currentContext = nullptr;
    //  std::vector<ThreadControlBlock> threadsList;
    //  ThreadControlBlock currThread;
    //  std::queue<int> readyQueue;
    //  std::mutex mutex;
    //  std::condition_variable cv;

    std::vector<ThreadControlBlock *> TCB_List;
    ThreadControlBlock *current_Thread;
    
    // Make queue for thread
    std::queue<ThreadControlBlock *> ready_Queue;
    // Make queue for new
    std::queue<ThreadControlBlock *> new_Queue;

    std::deque<void *> pp; // PushPull teehee

    //1. Initialization of the thread library:
    void thd_init()
    {
        // Create the initial main thread and set its context
        // ThreadControlBlock main_tcb;
        // std::thread t(thd_yield);
        // t.join();

        // Create new thread and place them in the list
        TCB_List.push_back(new ThreadControlBlock());
        // Allocate space for the thread
        TCB_List.back()->base = new char[ONE_MEGABYTE];
        // Need set stack pointet to point at the end of the base stack pointer
        TCB_List.back()->stack = (char *)(TCB_List.back()->base) + ONE_MEGABYTE;

        // Set thread 0 to the front and set it to running
        current_Thread = TCB_List.front();
        current_Thread->State = RUNNING;
    }

    //2. Creation of a user-level thread:
    ThreadID new_thd(void *(*thd_function_t)(void *), void *param)
    {
        // Lock mutex because below is a critical section
        // std::unique_lock<std::mutex> lock(mutex);

        // Need create the new THread with function point and param(argument)
        TCB_List.push_back(new ThreadControlBlock());
        TCB_List.back()->arg = param;
        TCB_List.back()->funcpointer = thd_function_t;

        // Same as before, need allocate space for stack
        TCB_List.back()->base = new char[ONE_MEGABYTE];
        TCB_List.back()->stack = (char *)(TCB_List.back()->base) + ONE_MEGABYTE;

        // add the therad to new queue
        new_Queue.push(TCB_List.back());

        // return to sender :)
        return TCB_List.back()->Current_Thread;
    }

    //3. Termination of a user-level thread:
    void thread_exit(void *ret_value)
    {
        // assign the return value to the TCB
        current_Thread->ret = ret_value;

        // change state to terminated
        current_Thread->State = DONE;

        for (auto &other : TCB_List)
        {
            // Need check if got any tread are waiting
            if (other->State == WAITING && other->Target_Thread == current_Thread->Current_Thread)
            {
                // if waiting, then need to set it to READY and then push it into the ready queue
                other->State = READY;
                ready_Queue.push(other);
            }
        }

        // yield CPU to next thread in the queue
        thd_yield();
    }

    int wait_thread(ThreadID id, void **value)
    {
        ThreadControlBlock *waiting_TCB{};

        for (unsigned int i = 0; i < TCB_List.size(); i++)
        {
            if (TCB_List[i]->Current_Thread == id)
            {
                // Need to set like the waiting_TCB
                waiting_TCB = TCB_List[i];
                break;
            }
        }

        // Need check if null
        if (waiting_TCB == NULL)
        {
            return NO_THREAD_FOUND;
        }

        if (waiting_TCB->State == DONE)
        {
            // If not null, then set value
            if (value != NULL)
            {
                *value = waiting_TCB->ret;
            }

            //loop through all the list ti check
            for (unsigned int i = 0; i < TCB_List.size(); i++)
            {
                if (TCB_List[i]->Current_Thread == id)
                {
                    // Need erase thread
                    TCB_List.erase(TCB_List.begin() + i);
                    break;
                }
            }

            return NO_THREAD_FOUND;
        }

        // need set the current thread to WAITING
        current_Thread->Target_Thread = id;

        // if not DONE, need set the current thread to waiting and call
        // then we yield it till its done
        while (waiting_TCB->State != DONE)
        {
            current_Thread->State = WAITING;
            // yield thread
            thd_yield();
        }

        // If no thread with id is found,
        if (value != NULL)
        {
            *value = waiting_TCB->ret;
        }

        return WAIT_SUCCESSFUL;
    }

    //rmb delete this if no need
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

    //TODO: dont use u_context or context switch
    //Getting seg fault dunno why. fed up
    //Should ask other how to do assembly. they say easier
    //too tired to think

    //4. Yield the processor:
    void thd_yield()
    {
        // Lock mutex because below is a critical section
        // std::unique_lock<std::mutex> lock(mutex);
        
        // int currentThread = currentThreadID;
        // readyQueue.push(currentThread);
        // threadsList[currentThread].state = READY;

        // schedule();
        
        // NOTE:Find way to use u_context. why seg faul always
        // I dont want to assembly

        // SAVING CONTEXT
        asm volatile
        (
            "push %%rax\n\t"
            "push %%rbx\n\t"
            "push %%rcx\n\t"
            "push %%rdx\n\t"
            "push %%rsi\n\t"
            "push %%rdi\n\t"
            "push %%r8\n\t"
            "push %%r9\n\t"
            "push %%r10\n\t"
            "push %%r11\n\t"
            "push %%r12\n\t"
            "push %%r13\n\t"
            "push %%r14\n\t"
            "push %%r15\n\t"
            "push %%rbp\n\t"
            "movq %%rsp, %0\n\t"
            : "=m"(current_Thread->stack)
            : : "memory"
        );

        // Pointer holding the next threaed to run
        ThreadControlBlock *next_TCB;

        // Need find thread from teh ready queue if empty
        if (ready_Queue.empty())
        {
            // need find thread from the new queue if its empty
            if (new_Queue.empty())
            {
                // restore context
                // inline asm code to restore stack pointer
                asm volatile
                (
                    "movq %0, %%rsp\n\t"
                    "pop %%rbp\n\t"
                    "pop %%r15\n\t"
                    "pop %%r14\n\t"
                    "pop %%r13\n\t"
                    "pop %%r12\n\t"
                    "pop %%r11\n\t"
                    "pop %%r10\n\t"
                    "pop %%r9\n\t"
                    "pop %%r8\n\t"
                    "pop %%rdi\n\t"
                    "pop %%rsi\n\t"
                    "pop %%rdx\n\t"
                    "pop %%rcx\n\t"
                    "pop %%rbx\n\t"
                    "pop %%rax\n\t"
                    : : "m"(current_Thread->stack)
                    : "memory"
                );
                return;
            }
            else
            {
                next_TCB = new_Queue.front();
                new_Queue.pop();
            }
        }
        else
        {
            next_TCB = ready_Queue.front();
            ready_Queue.pop();
        }

        // check if the current thread is RUNNING
        if (current_Thread->State == RUNNING)
        {
            current_Thread->State = READY;
            ready_Queue.push(current_Thread);
        }

        current_Thread = next_TCB;

        // Need check if the current thread is in running state and set to ready.If so, then we push it into the ready queue
        if (current_Thread->State == READY)
        {
            current_Thread->State = RUNNING;

            asm volatile
            (
                "movq %0, %%rsp\n\t"
                "pop %%rbp\n\t"
                "pop %%r15\n\t"
                "pop %%r14\n\t"
                "pop %%r13\n\t"
                "pop %%r12\n\t"
                "pop %%r11\n\t"
                "pop %%r10\n\t"
                "pop %%r9\n\t"
                "pop %%r8\n\t"
                "pop %%rdi\n\t"
                "pop %%rsi\n\t"
                "pop %%rdx\n\t"
                "pop %%rcx\n\t"
                "pop %%rbx\n\t"
                "pop %%rax\n\t"
                : : "m"(current_Thread->stack)
                : "memory"
            );
        }
        else
        {
            current_Thread->State = RUNNING;
            asm volatile
            (
                "mov %0, %%rsp \n\t"
                : "+m"(current_Thread->stack)
                :
                : "memory"
            );

            current_Thread->ret = next_TCB->funcpointer(next_TCB->arg);
            // exit thread
            thread_exit(current_Thread->ret);
        }
    }

    //Push and Pull
    void pull_value(void **pulled_value)
    {
        while (pp.empty())
        {
            thd_yield();
        }
        *pulled_value = pp.front();
        pp.pop_front();
    }
    void push_value(void *pushed_value)
    {
        // need push the value into the container for the pull and push values
        pp.emplace_back(pushed_value);
        thd_yield();
    }
}
