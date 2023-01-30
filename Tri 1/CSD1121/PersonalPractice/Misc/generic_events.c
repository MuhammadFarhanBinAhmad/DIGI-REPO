#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#pragma region EventSystem
// Each cell in the linkedlist
typedef struct { 
    void *func_pointer;
    void *prev;
    void *next;
} EventCell;

//Event Linkedlist start and end
typedef struct { 
    EventCell *start;
    EventCell *end;
} Event;

// Simple example: Doesn't free mem, only saves to start of Linkedlist
void SubscribeEvent(Event *event, void *function) { 
    event->start = malloc(sizeof(EventCell));
    event->start->func_pointer = function;
}

// Only works with int params for now
void InvokeEvent(Event const *event, int para_count, ...) { 
    va_list args;
    va_start(args, para_count);
    switch(para_count) {
        case 0:
        {
            void(*func)(void) = event->start->func_pointer;
            func();
        }
        break;
        case 1:
        {
            void(*func)(int) = event->start->func_pointer;
            func(va_arg(args, int));
        }
        break;
        case 2:
        {
            void(*func)(int, int) = event->start->func_pointer;
            int first = va_arg(args, int), second = va_arg(args, int);
            func(first, second);
        }
        break;
        case 3:
        {
            void(*func)(int, int, int) = event->start->func_pointer;
            int first = va_arg(args, int), second = va_arg(args, int), third = va_arg(args, int);
            func(first, second, third);
        }
        break;
    }
    va_end(args);
}
#pragma endregion

#pragma region main
Event test_event_0param; // Four events, each with different number of params
Event test_event_1param;
Event test_event_2param;
Event test_event_3param;

void test_0param(void) {
    printf("Printed nothing.\n");
}

void test_1param(int x) {
    printf("Printed 1 param: %d\n", x);
}
 
void test_2param(int x, int y) {
    printf("Printed 2 params: %d %d\n", x, y);
}

void test_3param(int x, int y, int z) {
    printf("Printed 3 params: %d %d %d\n", x, y, z);
}

int main(void) {
    // Subscribe and invoke 0 param event
    SubscribeEvent(&test_event_0param, test_0param);
    InvokeEvent(&test_event_0param, 0);
    
    // Subscribe and invoke 1 param event
    SubscribeEvent(&test_event_1param, test_1param);
    InvokeEvent(&test_event_1param, 1, 1);
    InvokeEvent(&test_event_1param, 1, 2);
    
    // Subscribe and invoke 2 param event
    SubscribeEvent(&test_event_2param, test_2param);
    InvokeEvent(&test_event_2param, 2, 3, 4);
    InvokeEvent(&test_event_2param, 2, 5, 6);
        
    // Subscribe and invoke 3 param event
    SubscribeEvent(&test_event_3param, test_3param);
    InvokeEvent(&test_event_3param, 3, 7, 8, 9);
    InvokeEvent(&test_event_3param, 3, 10, 11, 12);
}
#pragma endregion
 