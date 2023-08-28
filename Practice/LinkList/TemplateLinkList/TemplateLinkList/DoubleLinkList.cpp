//#include "DoubleLinkList.h"
//
//DLL::DLL() : head{ nullptr }, tail{ nullptr }, object_Counter{0}
//{
//}
//DLL::DLL(const DLL& ListToCopy):DLL()
//{
//	if (ListToCopy.Empty())
//	{
//		this->head = NewNode(0);
//		this->tail = this->head;
//	}
//	else
//	{
//		Node* temp_Head = ListToCopy.head;//temp now same as list we wish to copy
//		int count = 0;
//
//		while (temp_Head != nullptr)
//		{
//			PushBack(temp_Head->data);//copy data into list
//			temp_Head = temp_Head->next;
//		}
//		
//	}
//}
//DLL::DLL(std::initializer_list<int> ListToCopy) :DLL()
//{
//	for (int i : ListToCopy)
//	{
//		PushBack(i);
//	} 
//}
//DLL::~DLL()
//{
//	Clear();
//}
//
//DLL& DLL::operator=( DLL& rhs)
//{
//	Swap(rhs);
//
//	return *this;
//}
//
//DLL& DLL::operator=(std::initializer_list<int> rhs)
//{
//
//	DLL temp(rhs);
//	Swap(temp);
//
//	return *this;
//}
//int DLL::operator[](size_t index)
//{
//	Node* temp = this->head;
//	size_t counter = 0;
//
//	while (counter != index)
//	{
//		counter++;
//		temp = temp->next;
//	}
//
//	return temp->data;
//}
//const int DLL::operator[](size_t index) const
//{
//	Node* temp = this->head;
//	size_t counter = 0;
//
//	while (counter != index)
//	{
//		counter++;
//		temp = temp->next;
//	}
//
//	return temp->data;
//}
//
//int DLL::RetriveData(int index)
//{
//	int counter = 0;
//	Node *temp = this->head;
//
//	while (counter != index)
//	{
//		counter++;
//		temp = temp->next;
//	}
//
//	return temp->data;
//}
//void DLL::ChangeData(int index, int value)
//{
//	//By Front
//	Node* temp = this->head;
//	int counter = 0;
//
//	while (counter != index)
//	{
//		counter++;
//		temp = temp->next;
//	}
//
//
//	//By back
//	//Node* temp = this->tail;
//	//int counter = 5;
//	//while (counter != index)
//	//{
//	//	counter--;
//	//	temp = temp->prev;
//	//}
//
//	temp->data = value;
//}
//bool DLL::Empty() const
//{
//	return head == nullptr;
//}
//size_t DLL::Size()
//{
//	return object_Counter;
//}
//
//void DLL::PushFront(int value)
//{
//	//New node
//	Node* temp = NewNode(value);
//
//	//Set new node as the head.
//	temp->next = this->head;
//	this->head = temp;
//
//	//if tail is facing nothing
//	if (this->tail == nullptr)
//	{
//		this->tail = this->head;
//	}
//}
//void DLL::PushBack(int value)
//{
//	Node* temp = NewNode(value);
//
//	//If tail hold no node
//	if (this->tail == nullptr)
//	{
//		this->head = temp;
//		this->tail = temp;
//	}
//	else
//	{
//		this->tail->next = temp;//set next
//		temp->prev = this->tail;//set prev
//		this->tail = temp;
//	}
//}
//void DLL::RemoveFront()
//{
//	Node* temp = this->head;
//
//	if (head != nullptr)
//	{
//		head = temp->next;
//		delete temp;
//
//		object_Counter--;
//	}
//}
//void DLL::RemoveLast()
//{
//	Node* temp = this->tail;
//
//	if (tail != nullptr)
//	{
//		tail = temp->prev;
//		tail->next = nullptr;//need set next to null(dangling pointer)
//		delete temp;
//
//		object_Counter--;
//	}
//}
//void DLL::Remove(int index)
//{
//	if (index == 0)
//	{
//		RemoveFront();
//	}
//	else
//	{
//		int counter = 0;
//		Node* temp = this->head;
//
//		while (counter != index)
//		{
//			temp = temp->next;
//			counter++;
//		}
//		Node* prev = temp->prev;
//		Node* next = temp->next;
//		//set to new node
//		prev->next = temp->next;
//		next->prev = temp->prev;
//
//		delete temp;
//
//		object_Counter--;
//	}
//
//}
//void DLL::Add(int value, int index)
//{
//	int counter = 0;
//	Node* temp = this->head;
//
//	if (index == 0)
//	{
//		PushFront(value);
//	}
//	else
//	{
//		while (counter != index)
//		{
//			temp = temp->next;
//			counter++;
//		}
//
//		Node* New_Node = NewNode(value);
//		Node* Prev = temp->prev;
//
//		Prev->next = New_Node;
//		New_Node->next = temp;
//	}
//
//}
//void DLL::SwapValue(int currindex,int newindex)
//{
//	int lhscounter = 0;
//	int rhscounter = 0;
//	Node* lhs = this->head;
//	Node* rhs = this->head;
//
//	//Get both node position
//	while (lhscounter != currindex)
//	{
//		lhscounter++;
//		lhs = lhs->next;
//	}
//	while (rhscounter != newindex)
//	{
//		rhscounter++;
//		rhs = rhs->next;
//	}
//
//	int temp = lhs->data;
//
//	ChangeData(lhscounter, rhs->data);
//	ChangeData(rhscounter, temp);
//
//}
//DLL::Node* DLL::FindNode(int value)
//{
//	int counter = 0;
//	Node* temp = this->head;
//
//	while (temp->data != value && temp->next != nullptr)
//	{
//		temp = temp->next;
//		counter++;
//	}
//	if (temp->next == nullptr)
//	{
//		return nullptr;
//	}
//	else
//	return temp;
//}
//DLL::Node* DLL::NewNode(int data) 
//{ 
//	object_Counter++;
//	return new Node(data); 
//}
//
//
//void DLL::Clear()
//{
//	Node* temp = this->head;
//
//	//Delete all Node in between Head and Tail
//	while (temp != nullptr)
//	{
//		Node* NextNode = temp->next;
//		delete temp;
//		temp = NextNode;
//	}
//
//	//Reset where head and tail is pointing at(dangling pointer)
//	this->head = nullptr;
//	this->tail = nullptr;
//
//}
//
//void DLL::Swap(DLL& rhs)
//{
//	std::swap(this->head, rhs.head);
//	std::swap(this->tail, rhs.tail);
//}
//
//std::ostream& operator<<(std::ostream& os, const DLL& List)
//{
//	DLL::Node* temp = List.head;
//
//	while (temp !=0)
//	{
//		os << std::setw(4) << temp->data;
//		temp = temp->next;
//	}
//	os << std::endl;
//
//	return os;
//}
//
