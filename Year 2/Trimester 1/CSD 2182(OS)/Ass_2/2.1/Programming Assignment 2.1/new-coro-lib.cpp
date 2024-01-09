/*!************************************************************************
\file   new-coro-lib.cpp
\author Muhammad Farhan Bin Ahmad(2200544)
\par    email: b.muhammadfarhan@digipen.edu
\par    Course: CSD 2182
\par    OS Part 2.1
\date   30-11-2023

\brief 	To learn and understand context switching at some specific
        level using setcontext or inline assembly. The student who
        successfully completes this assignment will understand some
        analogy between the management of threads and the manaagement of processes
**************************************************************************/
#include "new-coro-lib.h"

#include <iostream>
#include <ucontext.h>
#include <deque>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <cstdlib>
#include <list>

#define ONE_MEGABYTE 1048576

namespace CORO
{
    enum Thread_State : short
    {
        START,
        RUNNING,
        READY,
        WAITING,
        DONE
    };

    static ThreadID Counter{};

    struct ThreadControlBlock
    {
        void *(*funcpointer)(void *);
        void *arg;
        ThreadID Target_Thread{};
        void *ret;
        ThreadID Current_Thread{};
        void *stack;
        Thread_State State;
        void *base;

        ThreadControlBlock()
        {
            Current_Thread = Counter;
            ++Counter;
        }
    };

    std::deque<ThreadControlBlock *> TCB_List;
    
    ThreadControlBlock *current_Thread;

    std::list<ThreadControlBlock *> ready_Queue;
    std::list<ThreadControlBlock *> new_Queue;

    std::deque<void *> pp; // PushPull teehee

    void pull_value(void **pulled_value)
    {
        do
        {
            thd_yield();
        } 
        while (pp.empty());

        *pulled_value = pp.front();
        pp.pop_front();
    }

    void push_value(void *pushed_value)
    {
        // need push the value into the container for the pull and push values
        pp.emplace_back(pushed_value);
        thd_yield();
    }

    void thd_init()
    {
        // Create new thread and place them in the list
        TCB_List.push_back(new ThreadControlBlock());

        // Allocate space for the thread using malloc
        TCB_List.back()->base = std::malloc(ONE_MEGABYTE);
        TCB_List.back()->stack = (char *)(TCB_List.back()->base) + ONE_MEGABYTE;

        current_Thread = TCB_List.front();
        current_Thread->State = RUNNING;
    }

    ThreadID new_thd(void *(*thd_function_t)(void *), void *param)
    {

        // Need create the new THread with function point and param(argument)
        TCB_List.push_back(new ThreadControlBlock());
        TCB_List.back()->arg = param;
        TCB_List.back()->funcpointer = thd_function_t;

        // Same as before, need allocate space for stack
        TCB_List.back()->base = std::malloc(ONE_MEGABYTE);
        TCB_List.back()->stack = (char *)(TCB_List.back()->base) + ONE_MEGABYTE;

        // add the thread to new list
        new_Queue.push_back(TCB_List.back());

        // return to sender :)
        return TCB_List.back()->Current_Thread;
    }

    int wait_thread(ThreadID id, void **value)
    {
        auto findWaitingThread = [id]() -> CORO::ThreadControlBlock *
        {
            for (auto tcb : CORO::TCB_List)
            {
                if (tcb->Current_Thread == id)
                {
                    return tcb;
                }
            }
            return nullptr;
        };

        auto switchToWaitingThread = []()
        {
            CORO::current_Thread->State = CORO::WAITING;
            CORO::thd_yield();
        };

        CORO::ThreadControlBlock *waiting_TCB = findWaitingThread();

        if (waiting_TCB == nullptr)
        {
            return CORO::NO_THREAD_FOUND;
        }

        if (waiting_TCB->State == CORO::DONE)
        {
            if (value != nullptr)
            {
                *value = waiting_TCB->ret;
            }

            for (auto it = CORO::TCB_List.begin(); it != CORO::TCB_List.end();)
            {
                if ((*it)->Current_Thread == id)
                {
                    it = CORO::TCB_List.erase(it);
                    break;
                }
                else
                {
                    ++it;
                }
            }

            return CORO::NO_THREAD_FOUND;
        }

        CORO::current_Thread->Target_Thread = id;

        do
        {
            switchToWaitingThread();
        } 
        while (waiting_TCB->State != CORO::DONE);

        if (value != nullptr)
        {
            *value = waiting_TCB->ret;
        }

        return CORO::WAIT_SUCCESSFUL;
    }

    void thd_yield()
    {
        asm volatile(
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
            : : "memory");

        // Pointer holding the next thread to run
        ThreadControlBlock *next_TCB;

        // Need find thread from the ready list if empty
        if (ready_Queue.empty())
        {
            // need find thread from the new list if it's empty
            if (new_Queue.empty())
            {
                // restore context
                // inline asm code to restore stack pointer
                asm volatile(
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
                    : "memory");
                return;
            }
            else
            {
                next_TCB = new_Queue.front();
                new_Queue.pop_front();
            }
        }
        else
        {
            next_TCB = ready_Queue.front();
            ready_Queue.pop_front();
        }

        // check if the current thread is RUNNING
        if (current_Thread->State == RUNNING)
        {
            current_Thread->State = READY;
            ready_Queue.push_back(current_Thread);
        }

        current_Thread = next_TCB;

        // Need check if the current thread is in running state and set to ready. If so, then we push it into the ready list
        if (current_Thread->State == READY)
        {
            current_Thread->State = RUNNING;

            asm volatile(
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
                : "memory");
        }
        else
        {
            current_Thread->State = RUNNING;
            asm volatile(
                "mov %0, %%rsp \n\t"
                : "+m"(current_Thread->stack)
                :
                : "memory");

            current_Thread->ret = next_TCB->funcpointer(next_TCB->arg);
            // exit thread
            thread_exit(current_Thread->ret);
        }
    }
    void thread_exit(void *ret_value)
    {

        for (auto &other : TCB_List)
        {
            // Need check if got any thread are waiting
            if (other->State == WAITING && other->Target_Thread == current_Thread->Current_Thread)
            {
                // if waiting, then need to set it to READY and then push it into the ready list
                other->State = READY;
                ready_Queue.push_back(other);
            }
        }
        // assign the return value to the TCB
        current_Thread->ret = ret_value;

        // change state to terminated
        current_Thread->State = DONE;
        // yield CPU to next thread in the list
        thd_yield();
    }
}
