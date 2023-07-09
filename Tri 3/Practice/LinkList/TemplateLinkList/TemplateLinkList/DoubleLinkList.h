#pragma once
/*****************************************************************//**
 * \file   DoubleLinkList.h
 * \brief
 *
 * \author Farhan
 * \date   April 2020
***********************************************************************/
struct Node
{
	Node* prev;
	Node* next;
	int data;
};
struct DLlist
{
	Node* Head;
};
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
int RetriveData(Node *node);

/*!
* \brief
* Change value of data of selected Node
* 
* \param[in] Node
* Give which Node which data you wish to change
* \param[in] value
* What value you wish to change to
*/
void ChangeData(Node *node, int value);

/*!  
* \brief
* Check if list is empty
* \param[in] DLlist
* List you wish to check if its empty
* \param[out] bool
* Return bool state if list is empty or not
 */
bool Empty(DLlist const *List);

/*!
* \brief
* Check the size of Linklist
* \param[in] DLlist
* List you wish to check
* \param[out] size_t
* Return the size of list
 */
size_t Size(DLlist const *List);

/*!
* \brief
* Destroy entire list
* \param[in] DLlist
* List you wish to destroy
 */
void DestroyList(DLlist *List);

/*!
* \brief
* Add new node at the front of the list
* \param[in] DLlist
* List you wish to add new node
* \param[in] value
* Value of new node
 */
void PushFront(DLlist* List, int value);

/*!
* \brief
* Add new node at the back of the list
* \param[in] DLlist
* List you wish to add new node
* \param[in] value
* Value of new node
 */
void PushBack(DLlist* List, int value);

/*!
* \brief
* Remove first node in the list
* \param[in] DLlist
* List you wish to remove the node
 */
void RemoveFront(DLlist* List);

/*!
* \brief
* Remove last node in the list
* \param[in] DLlist
* List you wish to remove the node
 */
void RemoveLast(DLlist* List);

/*!
* \brief
* Remove a desired node in the list
* \param[in] DLlist
* List you wish to remove the node
* \param[in] index
* The element index you wish to remove
 */
void Remove(DLlist* List, int index);

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
void Add(DLlist List, int value,int index);

/*!
* \brief
* Move an element from the list to another position
* \param[in] DLlist
* List you wish to check
* \param[in] index
* Index position you wish to place it in the list
 */
void Move(DLlist, int index);

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
Node* FindNode(DLlist const *List, int value);

/*!
* \brief
* Display all the node value
* \param[in] DLlist
* List you wish to check
 */
void Display(DLlist const* List);