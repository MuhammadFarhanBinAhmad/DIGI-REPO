// Other than sllist.hpp, you really don't have to include any other files except when testing your code.
// When you're ready to submit, don't include either of the following two headers: <forward_list> and <list>

// Private functions must be declared and defined in an anonymous namespace!!!

// See the spec for structure and interface definitions!!!
#include <iostream>
#include "sllist.hpp"

hlp2::node* create_node(int value, hlp2::node *next = nullptr);

namespace hlp2
{

struct node{
    int value;
    node *next;
};
struct sllist 
{
    node *head;
};

int data(node const *p) { return p->value; }
void data(node *p, int newval) { p->value = newval; }
node* next(node *p) { return p->next; }
node const* next(node const *p) { return p->next; }
// return initialized sllist object allocated on free store
sllist* construct() {
return new sllist {nullptr};
}
// add element to front of linked list
void push_front(sllist *ptr_sll, int value) 
{
    ptr_sll->head = create_node(value, ptr_sll->head);
}
// return number of elements in linked list container
size_t size(sllist const *ptr_sll) 
{
size_t cnt {};
for (node *head = ptr_sll->head; head; head = next(head)) {
++cnt;
}
return cnt;
}
void destruct(sllist *ptr_sll)
{
    if (!ptr_sll->head)
    {
        delete(ptr_sll);
        return;
    }

    node *current = ptr_sll->head;

    while (current != nullptr)
    {
        node *temp {nullptr};
        temp = current;
        current = current->next;//point to next guy
        delete(temp);
    }
    delete(current);
    delete(ptr_sll);
}
bool empty(sllist const *ptr_sll)
{
    if (ptr_sll->head == nullptr)
    {
        return true;
    }
    return false;

}

void push_back(sllist *ptr_sll, int value)
{

    if(!ptr_sll->head)
    {
        ptr_sll->head = create_node(value,nullptr);
        return;
    }

    node *current = ptr_sll->head;

    while (current->next != nullptr)
    {
        current = current->next;//point to next guy
    }
    //Now current poiting to nullptr
    current->next =  create_node(value,nullptr);    
}
void remove_first(sllist *ptr_sll, int value)
{
    if (!ptr_sll->head)
    {
        return;
    }
    node *current = ptr_sll->head;//Check current guy
    node *temp {nullptr}; // Use store guy before

    if (current->value == value)
    {
        node* ptr = ptr_sll->head;
        ptr_sll->head = ptr_sll->head->next;
        delete(ptr);
        return;
    }

    // if (current->next == nullptr)
    // {
    //     if (current->value == value)
    //     {
    //         delete(current);
    //     }
    // }
    
    
        while (current != nullptr)
        {
            if (current->next != nullptr && current->next->value == value)
            {
                temp = current;
                current = current->next;
                temp->next = current->next;
                delete(current);
                break;
            }
            current = current->next;//current point to next guy
        }

        // if (current == nullptr)
        // {       
        //     return;
        // }
        // temp->next = current->next;

        // delete(current);
    
}
void insert(sllist *ptr_sll, int value, size_t index)
{
    if (!ptr_sll->head)
    {
        return;
    }

    node *current = ptr_sll->head;//Check current guy
    node *new_node = create_node(value,nullptr);//new node pointing to null_ptr
    node *old_guy {nullptr};

    if (index == 0)
    {
        new_node->next = current;
        ptr_sll->head = new_node;
        return;
    }

    for (size_t i= 0; i < index -1;i++)
    {
        if (current->next == nullptr)
        {
            break;
        }
        current = current->next;
    }
    old_guy = current->next;
    current->next = new_node;
    new_node->next = old_guy;
}
node* front(sllist *ptr_sll)
{
    if (ptr_sll->head)
    {
        return ptr_sll->head;
    }
    else
    return nullptr;
}
node const* front(sllist const *ptr_sll)
{
    if (ptr_sll->head)
    {
        return ptr_sll->head;
    }
    else
    return nullptr;
}
node* find(sllist const *ptr_sll, int value)
{
    node *current = ptr_sll->head;

    if (current !=nullptr)
    {
        
    while (current != nullptr)
    {
        if (current->value == value)
        {
            return current;
        }
        current = current->next;
    }
    }
    return current;
    
}
}
hlp2::node* create_node(int value, hlp2::node* next) {
return new hlp2::node {value, next};
}
