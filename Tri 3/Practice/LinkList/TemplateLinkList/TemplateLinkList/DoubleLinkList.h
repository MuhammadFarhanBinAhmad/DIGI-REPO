#pragma once
#include <cstddef>
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <iomanip>
/*****************************************************************//**
 * \file   DoubleLinkList.h
 * \brief
 *
 * \author Farhan
 * \date   April 2020
***********************************************************************/
template<typename T>
class DLL
{
private:
	struct Node
	{
		Node* prev;
		Node* next;
		T data;
		Node(T val) :data(val), prev(nullptr), next(nullptr) {}//Constructor to create new Node
	};
public:
	Node *head{nullptr};
	Node *tail{nullptr};
	size_t object_Counter;
	DLL();//Constructor
	DLL(const DLL&);//Copy Constructor
	DLL(std::initializer_list<T>);//Will replace this with template
	~DLL();

	//Operators
	template<typename T>

	friend std::ostream& operator<<(std::ostream& os,const DLL<T>& List);
	DLL& operator=( DLL<T>& rhs);
	DLL& operator=(std::initializer_list<T> rhs);

	T operator[](size_t index);
	const T operator[](size_t index) const;

	DLL<T>& operator+=(const DLL<T> & right);
	DLL<T>& operator+=(const std::initializer_list<T> & right);

	/*!***********************************************************************
	* \brief
	* Change value of data of selected Node
	* \param[in] Node
	* Give which Node which data you wish to change
	* \param[in] value
	* What value you wish to change to
	*************************************************************************/
	void ChangeData(int index, T value);
	/*!***********************************************************************
	* \brief
	* Check if list is empty
	* \param[in] DLlist
	* List you wish to check if its empty
	* \param[out] bool
	* Return bool state if list is empty or not
	*************************************************************************/
	bool Empty() const;
	/*!***********************************************************************
	* \brief
	* Check the size of Linklist
	* \param[in] DLlist
	* List you wish to check
	* \param[out] size_t
	* Return the size of list
	 */
	size_t Size();
	/*!***********************************************************************
	//* \brief
	//* Add new node at the front of the list
	//* \param[in] DLlist
	//* List you wish to add new node
	//* \param[in] int
	//* Value of new node
	*************************************************************************/

	void PushFront(T value);
	/*!***********************************************************************
	* \brief
	* Add new node at the back of the list
	* \param[in] DLlist
	* List you wish to add new node
	* \param[in] int
	* Value of new node
	*************************************************************************/
	void PushBack(T value);
	/*!***********************************************************************
	* \brief
	* Remove first node in the list
	* \param[in] DLlist
	* List you wish to remove the node
	*************************************************************************/
	void RemoveFront();
	/*!***********************************************************************
	* \brief
	* Remove last node in the list
	* \param[in] DLlist
	* List you wish to remove the node
	*************************************************************************/
	void RemoveLast();
	/*!***********************************************************************
	* \brief
	* Remove a desired node in the list
	* \param[in] DLlist
	* List you wish to remove the node
	* \param[in] int
	* The element index you wish to remove
	*************************************************************************/
	void Remove(int index);
	/*!***********************************************************************
	* \brief
	* Add a desired node in the list
	* \param[in] DLlist
	* List you wish to add a node
	* \param[in] int
	* The value you wish to add
	* \param[in] int
	* The element index position
	*************************************************************************/
	void Add(T value, int index);
	/*!***********************************************************************
	* \brief
	* Swap 2 node position
	* \param[in] DLlist
	* List you wish to check
	* \param[in] int
	* Index position you wish to place it in the list
 * \param index
	*************************************************************************/
	void SwapValue(int currindex, int newindex);

	/*!***********************************************************************
	* \brief
	* Find and return specific node in the list
	* \param[in] DLlist
	* List you wish to check
	* \param[in] int
	* Value you wish to find
	* \param[out] Node*
	* Return node containing the value you desire
	*************************************************************************/
	Node* FindNode(T value);


	 /*!***********************************************************************
	 * \brief
	 * Create a new Node
	 * \param[in] int
	 * Data for the new node
	 * \param[out] Node*
	 * Return the pointer of the newly created Node
	 * *************************************************************************/
	Node* NewNode(T data);


	/*!***********************************************************************
	* \brief
	*  Delete the entire list
	* *************************************************************************/
	void Clear();


	void Swap(DLL<T>& rhs);
	void ReverseList();

};

template<typename T>
DLL<T>::DLL() : head{ nullptr }, tail{ nullptr }, object_Counter{ 0 }
{
}
template<typename T>
DLL<T>::DLL(const DLL& ListToCopy) :DLL()
{
	if (ListToCopy.Empty())
	{
		this->head = NewNode(NULL);
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
template<typename T>
DLL<T>::DLL(std::initializer_list<T> ListToCopy) :DLL()
{
	for (T i : ListToCopy)
	{
		PushBack(i);
	}
}
template<typename T>
DLL<T>::~DLL()
{
	Clear();
}

template<typename T>
DLL<T>& DLL<T>::operator=(DLL<T>& rhs)
{
	Swap(rhs);

	return *this;
}

template<typename T>
DLL<T>& DLL<T>::operator=(std::initializer_list<T> rhs)
{

	DLL temp(rhs);
	Swap(temp);

	return *this;
}
template<typename T>
T DLL<T>::operator[](size_t index)
{
	Node* temp = this->head;
	size_t counter = 0;

	while (counter != index)
	{
		counter++;
		temp = temp->next;
	}

	return temp->data;
}
template<typename T>
const T DLL<T>::operator[](size_t index) const
{
	Node* temp = this->head;
	size_t counter = 0;

	while (counter != index)
	{
		counter++;
		temp = temp->next;
	}

	return temp->data;
}
template<typename T>
DLL<T>& DLL<T>::operator+=(const DLL<T> & right)
{
	Node* temp = right.head;

	while (temp != nullptr)
	{
		this->PushBack(temp->data);
		temp = temp->next;
	}

	return *this;
}
template<typename T>
DLL<T>& DLL<T>::operator+=(const std::initializer_list<T> const& right)
{
	for (size_t i = 0; i < right.size(); i++)
	{
		this->PushBack(right[i]);
	}

	return *this;
}
template<typename T>
void DLL<T>::ChangeData(int index, T value)
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
template<typename T>
bool DLL<T>::Empty() const
{
	return head == nullptr;
}
template<typename T>
size_t DLL<T>::Size()
{
	size_t counter = 0;
	Node* temp = this->head;

	while (temp != nullptr)
	{
		temp = temp->next;
		counter++;
	}
	
	return counter;
}
template<typename T>
void DLL<T>::PushFront(T value)
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
template<typename T>
void DLL<T>::PushBack(T value)
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
template<typename T>
void DLL<T>::RemoveFront()
{
	Node* temp = this->head;

	if (head != nullptr)
	{
		head = temp->next;
		delete temp;

		object_Counter--;
	}
}
template<typename T>
void DLL<T>::RemoveLast()
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
template<typename T>
void DLL<T>::Remove(int index)
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
template<typename T>
void DLL<T>::Add(T value, int index)
{
	int counter = 0;
	Node* temp = this->head;

	if (index == 0)
	{
		PushFront(value);
	}
	else
	{
		while (counter != index)
		{
			temp = temp->next;
			counter++;
		}

		Node* New_Node = NewNode(value);
		Node* Prev = temp->prev;

		Prev->next = New_Node;
		New_Node->next = temp;
	}

}
template<typename T>
void DLL<T>::SwapValue(int currindex, int newindex)
{
	int lhscounter = 0;
	int rhscounter = 0;
	Node* lhs = this->head;
	Node* rhs = this->head;

	//Get both node position
	while (lhscounter != currindex)
	{
		lhscounter++;
		lhs = lhs->next;
	}
	while (rhscounter != newindex)
	{
		rhscounter++;
		rhs = rhs->next;
	}

	int temp = lhs->data;

	ChangeData(lhscounter, rhs->data);
	ChangeData(rhscounter, temp);

}
template<typename T>
typename DLL<T>::Node* DLL<T>::FindNode(T value)
{
	int counter = 0;
	Node* temp = this->head;

	while (temp->data != value && temp->next != nullptr)
	{
		temp = temp->next;
		counter++;
	}
	if (temp->next == nullptr)
	{
		return nullptr;
	}
	else
		return temp;
}
template<typename T>
typename DLL<T>::Node* DLL<T>::NewNode(T data)
{
	object_Counter++;
	return new Node(data);
}

template<typename T>
void DLL<T>::Clear()
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

template<typename T>
void DLL<T>::Swap(DLL<T>& rhs)
{
	std::swap(this->head, rhs.head);
	std::swap(this->tail, rhs.tail);
}

template<typename T>
void DLL<T>::ReverseList()
{
	size_t start = 0;
	size_t end = this->Size();

	while (start < end)
	{
		this->SwapValue(start, end-1);
		start++;
		end--;
	}
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const DLL<T> &List)
{
	typename DLL<T>::Node* temp = List.head;

	while (temp != 0)
	{
		os << std::setw(4) << temp->data << ' ';
		temp = temp->next;
	}
	os << std::endl;

	return os;
}


