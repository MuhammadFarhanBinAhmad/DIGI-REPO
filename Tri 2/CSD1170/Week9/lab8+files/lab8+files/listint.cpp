// File header documentation is required!!!


#include "listint.hpp"
#include <stdexcept>
#include <utility>
#include <iomanip>
namespace hlp2
{
  ListInt::size_type ListInt::object_counter{0};

  ListInt::size_type ListInt::object_count()
  {
    return object_counter;
  }

  ListInt::ListInt(): head(nullptr),tail(nullptr)
  {
    object_counter++;
  }
  ListInt::ListInt(const ListInt& rhs) : ListInt()
  {
    if (rhs.empty())
    {
      this->head = new_node(0);
      this->tail = head;
    }
    else
    {
      Node* temp = rhs.head;
      while (temp != nullptr)
      {
        push_back(temp->data);
        temp = temp->next;
      }
    }
  }
  ListInt::ListInt(std::initializer_list<value_type>rhs) : ListInt()
  {
    for (value_type vt : rhs)
    {
      push_back(vt);
    }
  }
  ListInt::~ListInt()
  {
    clear();
    object_counter--;
  }

  ListInt& ListInt::operator=(ListInt rhs)
  {
    swap(rhs);

    return *this;
    
  }
  ListInt& ListInt::operator=(const std::initializer_list<value_type> rhs)
  {
    ListInt temp(rhs);
    swap(temp);
    return *this;
  }

  ListInt& ListInt::operator+=(const ListInt& rhs)
  {
    Node* temp_head = rhs.head;
    while(temp_head != nullptr)
    {
      push_back(temp_head->data);
      temp_head = temp_head->next;
    }

    return *this;
  }
  ListInt &ListInt::operator+=(ListInt &&rhs)
  { 
    if (rhs.head != nullptr)
    {
        if (this->tail == nullptr)
        {
          head = rhs.head;
          tail = rhs.tail;
        }
        else
        {
          this->tail->next = rhs.head;
          this->tail = rhs.tail;
        }
        object_counter += rhs.object_counter;
        rhs.head = nullptr;
        rhs.tail = nullptr;
        object_counter++;
    }

    return *this;
  }
  ListInt::value_type& ListInt::operator[](ListInt::size_type val)
  {
      Node* temp = this->head;

      for (size_type i=0; i < val;i++)
      {
        temp = temp->next;
      }
      return temp->data;
      
  }
  const ListInt::value_type& ListInt::operator[](ListInt::size_type val) const
  {
      Node* temp = this->head;

      for (size_type i=0; i < val;i++)
      {
        temp = temp->next;
      }
      return temp->data;
  }
  ListInt ListInt::operator+(const ListInt& rhs) const
  {
    ListInt temp_List(*this);
    Node* temp_Node = rhs.head;

    while (temp_Node !=nullptr)
    {
      temp_List.push_back(temp_Node->data);
      temp_Node = temp_Node->next;
    }
    return  temp_List;
  }
  ListInt ListInt::operator+(const std::initializer_list<ListInt::value_type>& rhs) const
  {
    ListInt temp_List(*this);
    for (value_type vt:rhs)
    {
      temp_List.push_back(vt);
    }
    return temp_List;

  }
  ListInt operator+(std::initializer_list<ListInt::value_type> other_list,const ListInt& rhs)
  {
    ListInt temp_List(other_list);
    temp_List += rhs;
    return temp_List;
  }
  ListInt::Node* ListInt::new_node(ListInt::value_type value) const
  {
    return new Node(value);
  }
  void ListInt::push_front(ListInt::value_type value)
  {
    Node* temp_head = new_node(value);
    temp_head->next = this->head;
    head = temp_head;

    if (this->tail == nullptr)
    {
      this->tail = this->head;
    }
  }
  
  void ListInt::push_back(ListInt::value_type value)
  {

    Node *temp_tail = new_node(value);
    if (this->tail == nullptr)
    {
      this->head = temp_tail;
      this->tail = temp_tail;
    }
    else
    {
      this->tail->next = temp_tail;
      this->tail = temp_tail;
    }

  }

  ListInt::value_type ListInt::pop_front()
  {
    if (this->head == nullptr)
    {
      throw std::out_of_range("pop_front on empty ListInt");
    }
    ListInt::value_type value = head->data;
    
    Node *old_Head = this->head;
    this->head = this->head->next;
    delete old_Head;

    if (this->head == nullptr)
    {
      this->tail = nullptr;
    }
    
    return value;
  }

  void ListInt::clear()
  {
    Node* temp = head;

    while (temp !=nullptr)
    {
      Node * current = temp->next;
      delete temp;
      temp = current;
    }

    this->head = nullptr;
    this->tail = nullptr;
  }

  void ListInt::swap(ListInt& other_list)
  {
    std::swap(this->head,other_list.head);
    std::swap(this->tail,other_list.tail);
  }

  ListInt::size_type ListInt::size()
  {
    size_type counter =0;
    Node *temp = this->head;
    while (temp !=nullptr)
    {
      counter++;
      temp = temp->next;
    }

    return counter;
  }

  bool ListInt::empty() const
  {
    return head==nullptr;
  }

  std::ostream& operator<<(std::ostream& os, const ListInt& rhs) 
  {
  // Start at the first node
  ListInt::Node *pnode = rhs.head;

  // Until we reach the end of the list
  while (pnode != 0) {
    os << std::setw(4) << pnode->data; // print the data in this node
    pnode = pnode->next;               // move to the next node
  }
  
  os << std::endl; // extra newline for readability
  return os;
  }
}
