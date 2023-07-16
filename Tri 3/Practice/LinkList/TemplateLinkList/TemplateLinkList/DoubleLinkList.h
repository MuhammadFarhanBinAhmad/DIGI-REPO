#pragma once
#include <initializer_list>
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


	/*!***********************************************************************
	* \brief
	* Get the data of a specific Node
	*
	* \param[in] Node
	* Give which Node you wish to get the value
	*
	* \param[out] int
	* Returns value of data
	*************************************************************************/
	int RetriveData(int index);

	/*!
	* \brief
	* Change value of data of selected Node
	*
	* \param[in] Node
	* Give which Node which data you wish to change
	* \param[in] value
	* What value you wish to change to
	*/
	void ChangeData(int index, int value);

	/*!
	* \brief
	* Check if list is empty
	* \param[in] DLlist
	* List you wish to check if its empty
	* \param[out] bool
	* Return bool state if list is empty or not
	 */
	bool Empty() const;

	/*!
	* \brief
	* Check the size of Linklist
	* \param[in] DLlist
	* List you wish to check
	* \param[out] size_t
	* Return the size of list
	 */
	size_t Size();

	/*!
	* \brief
	* Destroy entire list
	* \param[in] DLlist
	* List you wish to destroy
	 */
	//void DestroyList(DLlist* List);

	///*!
	//* \brief
	//* Add new node at the front of the list
	//* \param[in] DLlist
	//* List you wish to add new node
	//* \param[in] value
	//* Value of new node
	// */
	void PushFront( int value);

	/*!
	* \brief
	* Add new node at the back of the list
	* \param[in] DLlist
	* List you wish to add new node
	* \param[in] value
	* Value of new node
	 */
	void PushBack(int value);

	/*!
	* \brief
	* Remove first node in the list
	* \param[in] DLlist
	* List you wish to remove the node
	 */
	void RemoveFront();

	/*!
	* \brief
	* Remove last node in the list
	* \param[in] DLlist
	* List you wish to remove the node
	 */
	void RemoveLast();

	/*!
	* \brief
	* Remove a desired node in the list
	* \param[in] DLlist
	* List you wish to remove the node
	* \param[in] index
	* The element index you wish to remove
	 */
	void Remove( int index);

	/*!
	* \brief
	* Add a desired node in the list
	* \param[in] DLlist
	* List you wish to add a node
	* \param[in] value
	* The value you wish to add
	* \param[in] index
	* The element index position
	 */
	void Add(int value, int index);

	/*!
	* \brief
	* Move an element from the list to another position
	* \param[in] DLlist
	* List you wish to check
	* \param[in] index
	* Index position you wish to place it in the list
	 */
	void Move(int index);

	/*!
	* \brief
	* Find and return specific node in the list
	* \param[in] DLlist
	* List you wish to check
	* \param[in] value
	* Value you wish to find
	* \param[out] Node*
	* Return node containing the value you desire
	 */
	Node* FindNode(int value);

	/*!
	* \brief
	* Display all the node value
	* \param[in] DLlist
	* List you wish to check
	 */
	void Display();

	Node* NewNode(int data);

	void Clear();

};