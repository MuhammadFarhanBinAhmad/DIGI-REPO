#include "DoubleLinkList.h"
#include <iostream>

DLL::DLL() : head{ nullptr }, tail{ nullptr }, object_Counter{0}
{
}
DLL::DLL(const DLL& ListToCopy):DLL()
{
	if (ListToCopy.Empty())
	{
		this->head = NewNode(0);
		this->tail = this->head;
	}
	else
	{
		Node* temp_Head = ListToCopy.head;//temp now same as list we wish to copy
		int count = 0;

		while (temp_Head != nullptr)
		{
			PushBack(temp_Head->data);//copy data into list
			temp_Head = temp_Head->next;
		}
		
	}
}
DLL::DLL(std::initializer_list<int> ListToCopy) :DLL()
{
	for (int i : ListToCopy)
	{
		PushBack(i);
	}
}
DLL::~DLL()
{

}

int DLL::RetriveData(int index)
{
	int counter = 0;
	Node *temp = this->head;

	while (counter != index)
	{
		counter++;
		temp = temp->next;
	}

	return temp->data;
}
void DLL::ChangeData(int index, int value)
{
	//By Front
	Node* temp = this->head;
	int counter = 0;

	while (counter != index)
	{
		counter++;
		temp = temp->next;
	}


	//By back
	//Node* temp = this->tail;
	//int counter = 5;
	//while (counter != index)
	//{
	//	counter--;
	//	temp = temp->prev;
	//}

	temp->data = value;
}
bool DLL::Empty() const
{
	return head == nullptr;
}
size_t DLL::Size()
{
	return object_Counter;
}

void DLL::PushFront(int value)
{
	//New node
	Node* temp = NewNode(value);

	//Set new node as the head.
	temp->next = this->head;
	this->head = temp;

	//if tail is facing nothing
	if (this->tail == nullptr)
	{
		this->tail = this->head;
	}
}
void DLL::PushBack(int value)
{
	Node* temp = NewNode(value);

	//If tail hold no node
	if (this->tail == nullptr)
	{
		this->head = temp;
		this->tail = temp;
	}
	else
	{
		this->tail->next = temp;//set next
		temp->prev = this->tail;//set prev
		this->tail = temp;
	}
}
void DLL::RemoveFront()
{
	Node* temp = this->head;

	if (head != nullptr)
	{
		head = temp->next;
		delete temp;

		object_Counter--;
	}
}
void DLL::RemoveLast()
{
	Node* temp = this->tail;

	if (tail != nullptr)
	{
		tail = temp->prev;
		tail->next = nullptr;//need set next to null(dangling pointer)
		delete temp;

		object_Counter--;
	}
}
void DLL::Remove(int index)
{
	if (index == 0)
	{
		RemoveFront();
	}
	else
	{
		int counter = 0;
		Node* temp = this->head;

		while (counter != index)
		{
			temp = temp->next;
			counter++;
		}
		Node* prev = temp->prev;
		Node* next = temp->next;
		//set to new node
		prev->next = temp->next;
		next->prev = temp->prev;

		delete temp;

		object_Counter--;
	}

}
void DLL::Add(int value, int index)
{
	//Node* NewN = NewNode(value);
	//Node* temp = this->head;
	//int counter = 0;

	//while (counter != index)
	//{
	//	counter++;
	//	temp = temp->next;
	//}



	//temp->next = NewN;
	
}
void DLL::Move(int index)
{

}
//DLL::Node* DLL::FindNode(int value)
//{
//
//}
void DLL::Display()
{

}
DLL::Node* DLL::NewNode(int data) 
{ 
	object_Counter++;
	return new Node(data); 
}

void DLL::Clear()
{
	Node* temp = this->head;

	//Delete all Node in between Head and Tail
	while (temp != nullptr)
	{
		Node* NextNode = temp->next;
		delete temp;
		temp = NextNode;
	}

	//Reset where head and tail is pointing at(dangling pointer)
	this->head = nullptr;
	this->tail = nullptr;

}
