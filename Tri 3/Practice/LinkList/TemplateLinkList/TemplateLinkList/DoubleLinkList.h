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
class DLL
{
private:
	struct Node
	{
		Node* prev;
		Node* next;
		int data;
		Node(int val) :data(val), prev(nullptr), next(nullptr) {}//Constructor to create new Node
	};
public:
	Node *head{nullptr};
	Node *tail{nullptr};
	size_t object_Counter;
	DLL();//Constructor
	DLL(const DLL&);//Copy Constructor
	DLL(std::initializer_list<int>);//Will replace this with template
	~DLL();

	//Operators
	friend std::ostream& operator<<(std::ostream& os, const DLL& List);
	DLL& operator=( DLL& rhs);
	DLL& operator=(std::initializer_list<int> rhs);

	int operator[](size_t index);
	const int operator[](size_t index) const;

	/*!***********************************************************************
	* \brief
	* Get the data of a specific Node
	*
	*
	*************************************************************************/
	int RetriveData(int index);
	/*!***********************************************************************
	* \brief
	* Change value of data of selected Node
	* \param[in] Node
	* Give which Node which data you wish to change
	* \param[in] value
	* What value you wish to change to
	*************************************************************************/
	void ChangeData(int index, int value);
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

	void PushFront(int value);
	/*!***********************************************************************
	* \brief
	* Add new node at the back of the list
	* \param[in] DLlist
	* List you wish to add new node
	* \param[in] int
	* Value of new node
	*************************************************************************/
	void PushBack(int value);
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
	void Add(int value, int index);
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
	Node* FindNode(int value);


	 /*!***********************************************************************
	 * \brief
	 * Create a new Node
	 * \param[in] int
	 * Data for the new node
	 * \param[out] Node*
	 * Return the pointer of the newly created Node
	 * *************************************************************************/
	Node* NewNode(int data);


	/*!***********************************************************************
	* \brief
	*  Delete the entire list
	* *************************************************************************/
	void Clear();


	void Swap(DLL& rhs);
};
