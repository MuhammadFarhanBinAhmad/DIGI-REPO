/*!************************************************************************
\file sllist.tpp
\author Muhammad Farhan Bin Ahmad
\par email: b.muhammadfarhan@digipen.edu
\par Course: CSD 1171
\par Assignment 7 - Single link-list template(AKA COPY FOR FUN. PRAISE FUCKY)
\date 16-03-2023
\brief This script contains:
      1 Class:
      sllist
        This class contain:
        1 Struct
        Node
          This Node contain:
            Node *next{nullptr}; // pointer to next Node
            Node(T const &);     // conversion ctor to initialize Node object
            ~Node();             // dtor
            static size_type node_counter; // declaration
            Node *new_node( const_reference) const;//Create new node
            Node *head{nullptr};//DECLARE HEAD
            Node *tail{nullptr};//DECLARE TAIL
            //End of Node
        sllist();//def Constructor
        sllist(sllist const &rhs);//Copy Assignment
        sllist(std::initializer_list<T> const &);//Copy initializer
        sllist(const_pointer begin, const_pointer end);//Non default Copy constructor
        ~sllist();//Destructor

        int data(Node const *p);        // accessor to node's data
        void data(Node *p, int newval); // mutator to node's data
        Node *next(Node *p);            // pointer to successor node
        Node *next(Node const *p) const;// pointer to successor node
        bool empty() const;// Check if sllist is empty
        size_t size() const;// return size sllist
        void push_front(value_type const &ptr_sll);//Add a node in the front of the list
        void push_back(value_type const &ptr_sll);//Add a node in the back of the list
        void remove_first(int value);//Remove first element in the list
        void clear();//Clear sllist
        void swap(sllist<T> &rhs);//Swap sllist
        reference front();//Return fist element in the list
        const_reference front() const;//Return fist element in the list
        void pop_front();//Return value of the first node and destory it

        //OPERATOR
        sllist<value_type> &operator+=(sllist const &);//sllist += sllist
        sllist<value_type> &operator+=(std::initializer_list<value_type> const &);sllist += initializer_list
        sllist &operator=(sllist const &rhs);// sllist = sllist
        sllist &operator=(std::initializer_list<value_type> const &_list);// sllist = initializer_list

        reference operator[](size_type);sllist[]
        const_reference operator[](size_type) const;sllist[]

        static size_t node_count();//Count total node
        static size_t object_count();//Coun total object(sllist)

        template <typename U>
        friend std::ostream &operator<<(std::ostream &os, const sllist<U> &rhs);
    };
    NON MEMBER FUNCTION
    template <typename T>
    void swap(sllist<T> &lhs, sllist<T> &rhs);
    template <typename T>
    sllist<T> operator+(const std::initializer_list<T> &lhs, const sllist<T> &rhs);
    template <typename T>
    sllist<T> operator+(const sllist<T> &lhs, const std::initializer_list<T> &rhs);
    template <typename T>
    sllist<T> operator+(const sllist<T> &lhs, const sllist<T> &rhs);

\brief
This source file implements functions for a template singly-linked list.
**************************************************************************/
#include "sllist.hpp"

namespace hlp2
{
  //def constructor
  template <typename T>
  sllist<T>::sllist()
  {
    object_counter++;
  }

  //copy constructor
  template <typename T>
  sllist<T>::sllist(sllist const &rhs) : sllist()
  {
    Node *temp = rhs.head;
    while (temp != nullptr)
    {
      push_back(temp->data);
      temp = temp->next;
    }
  }

  //copy constructor intitalizer list
  template <typename T>
  sllist<T>::sllist(const std::initializer_list<T> &rhs) : sllist()
  {
    for (const T &s : rhs)
    {
      push_back(s);
    }
  }

  //non defaultcopy assignment
  template <typename T>
  sllist<T>::sllist(const_pointer begin, const_pointer end) : sllist()
  {
    const_pointer temp = begin;

    while (temp < end)
    {
      push_back(*temp);
      temp++;
    }
  }

  //destructor
  template <typename T>
  sllist<T>::~sllist()
  {
    object_counter--;
    clear();
  }

  //Node constructor
  template <typename T>
  sllist<T>::sllist::Node::Node(T const &val) : data{val}
  {
    node_counter++;
  }

  //Create new node and return newly created node
  template <typename T>
  typename sllist<T>::Node *sllist<T>::new_node(sllist<T>::const_reference value) const
  {
    return new Node(value);
  }

  //Node destructor
  template <typename T>
  sllist<T>::sllist::Node::~Node()
  {
    node_counter--;
  }

  //Return data of Node
  template <typename T>
  int sllist<T>::data(sllist<T>::Node const *p) { return p->data; }
  template <typename T>
  void sllist<T>::data(sllist<T>::Node *p, int newval) { return p->data; }

  //Return next element of a Node
  template <typename T>
  typename sllist<T>::Node *sllist<T>::next(sllist<T>::Node *p) { return p->next; }
  template <typename T>
  typename sllist<T>::Node *sllist<T>::next(sllist<T>::Node const *p) const { return p->next; }

  //return true/false if sllist is empty or not
  template <typename T>
  bool sllist<T>::empty() const
  {
    if (head == nullptr)
    {
      return true;
    }
    return false;
  }

  //Return size value of sllist
  template <typename T>
  size_t sllist<T>::size() const
  {
    size_t cnt{};
    for (Node *head = this->head; head; head = next(head))
    {
      ++cnt;
    }
    return cnt;
  }

  //Add a new element in the front of the list
  template <typename T>
  void sllist<T>::push_front(value_type const &val)
  {
    Node *temp_head = new_node(val);
    temp_head->next = this->head;
    head = temp_head;

    if (this->tail == nullptr)
    {
      this->tail = this->head;
    }
  }

  //Add new element in the back of the list
  template <typename T>
  void sllist<T>::push_back(value_type const &value)
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

  //Remove the first element in the list
  template <typename T>
  void sllist<T>::remove_first(int value)
  {
    if (!this->head)
    {
      sllist<T>::Node::node_counter--;
      return;
    }
    Node *current = this->head; // Check current guy
    Node *temp{nullptr};        // Use store guy before

    //Check if value is the same to delete
    if (current->value == value)
    {
      Node *ptr = this->head;
      this->head = this->head->next;
      sllist<T>::Node::node_counter--;
      delete (ptr);
      return;
    }
  }

  //Return node to the first node
  template <typename T>
  typename sllist<T>::reference sllist<T>::front()
  {
    return this->head->data;
  }

  //Return node to the first node
  template <typename T>
  typename sllist<T>::const_reference sllist<T>::front() const
  {
    return this->head->data;
  }

  //Clear sllist
  template <typename T>
  void sllist<T>::clear()
  {

    Node *temp = head;

    while (temp != nullptr)
    {
      Node *current = temp->next;
      delete temp;
      temp = current;
    }

    this->head = nullptr;
    this->tail = nullptr;
  }

  //Swap sllist
  template <typename T>
  void sllist<T>::swap(sllist<T> &rhs)
  {

    Node *temp_Head = head;
    Node *temp_Tail = tail;

    head = rhs.head;
    tail = rhs.tail;

    rhs.head = temp_Head;
    rhs.tail = temp_Tail;

    size_t temp = counter;
    counter = rhs.counter;
    rhs.counter = temp;
  }

  //Return value first node in the list and deletes it
  template <typename T>
  void sllist<T>::pop_front()
  {
    if (this->head == nullptr)
    {
      throw std::out_of_range("pop_front on empty ListInt");
    }

    Node *old_Head = this->head;
    this->head = this->head->next;
    delete old_Head;

    if (this->head == nullptr)
    {
      this->tail = nullptr;
    }
  }

  //Return object count value
  template <typename T>
  size_t sllist<T>::object_count()
  {
    return object_counter;
  }

  template <typename T>
  sllist<T> &sllist<T>::operator+=(const sllist<value_type> &rhs)
  {

    sllist<T> temp = *this;

    for (size_t i = 0; i < rhs.size(); i++)
    {
      this->push_back(rhs[i]);
    }
    return *this;
  }
  template <typename T>
  sllist<T> &sllist<T>::operator+=(const std::initializer_list<T> &rhs)
  {
    sllist<T> temp = *this;

    for (T const &i : rhs)
    {
      this->push_back(i);
    }
    return *this;
  }
  template <typename T>
  sllist<T> &sllist<T>::operator=(const sllist &rhs)
  {
    sllist<T> temp(rhs);
    swap(temp);
    return *this;
  }
  template <typename T>
  sllist<T> &sllist<T>::operator=(std::initializer_list<value_type> const &rhs)
  {
    sllist<T> temp(rhs);
    swap(temp);
    return *this;
  }
  template <typename T>
  T &sllist<T>::operator[](size_type val)
  {
    Node *temp = this->head;
    for (size_type i = 0; i < val; i++)
    {
      temp = temp->next;
    }
    return temp->data;
  }
  template <typename T>
  const T &sllist<T>::operator[](size_type val) const
  {
    Node *temp = this->head;
    for (size_type i = 0; i < val; i++)
    {
      temp = temp->next;
    }
    return temp->data;
  }
  template <typename T>
  sllist<T> operator+(const std::initializer_list<T> &lhs, const sllist<T> &rhs)
  {
    sllist<T> fucky{lhs};
    sllist<T> new_list{};

    for (const T &s : lhs)
    {
      new_list.push_back(s);
    }
    typename sllist<T>::Node *temp_rhs = rhs.head;
    while (temp_rhs != nullptr)
    {
      new_list.push_back(temp_rhs->data);
      temp_rhs = temp_rhs->next;
    }

    return new_list;
  }
  template <typename T>
  sllist<T> operator+(const sllist<T> &lhs, const std::initializer_list<T> &rhs)
  {
    sllist<T> fucky{lhs};
    sllist<T> new_list{lhs};

    for (const T &s : rhs)
    {
      new_list.push_back(s);
    }

    return new_list;
  }
  template <typename T>
  sllist<T> operator+(const sllist<T> &lhs, const sllist<T> &rhs)
  {
    sllist<T> fucky{lhs};
    sllist<T> new_list{};
    typename sllist<T>::Node *temp_rhs = rhs.head;
    typename sllist<T>::Node *temp_lhs = lhs.head;
    while (temp_lhs != nullptr)
    {
      new_list.push_back(temp_lhs->data);
      temp_lhs = temp_lhs->next;
    }
    while (temp_rhs != nullptr)
    {
      new_list.push_back(temp_rhs->data);
      temp_rhs = temp_rhs->next;
    }
    return new_list;
  }

  //Retur total node in the sllist
  template <typename T>
  typename sllist<T>::size_type sllist<T>::node_count()
  {
    return sllist<T>::Node::node_counter;
  }
  template <typename T>
  T operator+(const T lhs, const T rhs)
  {
    return lhs + rhs;
  }

  //Swap sllist
  template <typename T>
  void swap(sllist<T> &lhs, sllist<T> &rhs)
  {
    sllist<T> temp(lhs);
    lhs = rhs;
    rhs = temp;
  }
  template <typename T>
  std::ostream &operator<<(std::ostream &os, sllist<T> const &list)
  {
    // start at the first node ...
    typename sllist<T>::size_type ls_sz = list.size();

    // uses overloaded subscript operator for class sllist ...
    for (typename sllist<T>::size_type i = 0; i < ls_sz; ++i)
    {
      os << list[i] << std::setw(4);
    }
    os << "\n"; // extra newline for readability
    return os;
  }
}
