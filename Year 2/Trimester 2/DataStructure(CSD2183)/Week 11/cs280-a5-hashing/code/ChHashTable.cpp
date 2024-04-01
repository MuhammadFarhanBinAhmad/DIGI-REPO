/******************************************************************************/
/*!
\file:		ChHashTable.cpp
\author:  MuhammadFarhanBinAhmad
\par email: 2200544@sit.singaporetech.edu.sg
\date:		March 27, 2024
\brief		Sudoku solver
*/
/******************************************************************************/
#include "ChHashTable.h"

template <typename T>
ChHashTable<T>::ChHashTable(const HTConfig &Config, ObjectAllocator *allocator)
    : _config{Config}, _oa{allocator}
{
  // Initilise stats
  _stats.TableSize_ = _config.InitialTableSize_;
  _stats.HashFunc_ = _config.HashFunc_;

  // Initilise table array
  _table = new ChHTHeadNode[_stats.TableSize_];
}

template <typename T>
ChHashTable<T>::~ChHashTable()
{
  clear();
  delete[] _table;
}
template <typename T>
HTStats ChHashTable<T>::GetStats() const
{
  return _stats;
}
template <typename T>
const typename ChHashTable<T>::ChHTHeadNode *ChHashTable<T>::GetTable() const
{
  return _table;
}
template <typename T>
void ChHashTable<T>::DeleteNode(ChHTNode *node)
{
  if (_oa)
  {
    node->~ChHTNode();
  }
  delete node;
}
template <typename T>
typename ChHashTable<T>::ChHTNode *ChHashTable<T>::CreateNode(const char *Key, const T &Data)
{
  ChHTNode *newNode;

  if (_oa)
  {
    newNode = new (_oa->Allocate()) ChHTNode(Data);
  }
  else
  {
    newNode = new ChHTNode(Data);
  }

  std::strcpy(newNode->Key, Key);
  return newNode;
}
template <typename T>
typename ChHashTable<T>::ChHTNode *ChHashTable<T>::SearchNode(const unsigned &i, const char *Key, ChHTNode *&prev_node) const
{
  // Loop through linked list to find key
  if (_table[i].Count == 0)
  {
    _stats.Probes_++;
    return NULL;
  }
  else
  {
    ChHTNode *node = _table[i].Nodes;
    prev_node = node;

    do
    {
      _stats.Probes_++;

      if (strcmp(node->Key, Key) == 0)
        return node;

      prev_node = node;
      node = node->Next;
    } while (node);

    _stats.Probes_++;
    return node;
  }
}

template <typename T>
void ChHashTable<T>::clear()
{
  for (unsigned i = 0; i < _stats.TableSize_; i++)
  {
    ChHTHeadNode headNode = _table[i];
    ChHTNode *node = headNode.Nodes;

    do
    {
      if (!node)
      {
        break;
      }

      ChHTNode *temp = node;
      node = node->Next;

      DeleteNode(temp);

      _table[i].Count--;
      _stats.Count_--;
    } while (node);

    _table[i].Nodes = NULL;
  }
}

template <typename T>
const T &ChHashTable<T>::find(const char *Key) const
{
  // Get index from table
  unsigned i = _stats.HashFunc_(Key, _stats.TableSize_);

  // Search nodes
  ChHTNode *prev_node;
  ChHTNode *node = SearchNode(i, Key, prev_node);

  if (node == NULL)
  {
    throw HashTableException(HashTableException::E_ITEM_NOT_FOUND,
                             "Key does not exist in table");
  }

  return node->Data;
}
template <typename T>
void ChHashTable<T>::remove(const char *Key)
{
  unsigned i = _stats.HashFunc_(Key, _stats.TableSize_);

  ChHTNode *prev_node;
  ChHTNode *node = SearchNode(i, Key, prev_node);

  if (node == NULL)
    throw HashTableException(HashTableException::E_ITEM_NOT_FOUND,
                             "Key does not exist in table");

  // Remove node
  ChHTNode *temp = node;

  if (prev_node == node)
  {
    _table[i].Nodes = node->Next;
  }
  else
  {
    prev_node->Next = node->Next;
  }

  DeleteNode(temp);

  _table[i].Count--;
  _stats.Count_--;
}
template <typename T>
void ChHashTable<T>::insert(const char *Key, const T &Data)
{
  // Calculate load factor
  double loadFactor = (_stats.Count_ + 1) / static_cast<double>(_stats.TableSize_);

  // if loadFactor > max load factor, expand table
  if (loadFactor > _config.MaxLoadFactor_)
  {
    unsigned oldTableSize = _stats.TableSize_;
    double factor = std::ceil(_stats.TableSize_ * _config.GrowthFactor_);

    _stats.TableSize_ = GetClosestPrime(static_cast<unsigned>(factor));
    ChHTHeadNode *oldTable = _table;

    // reinsert items from old to new table
    _table = new ChHTHeadNode[_stats.TableSize_];

    for (unsigned i = 0; i < oldTableSize; i++)
    {
      ChHTHeadNode headNode = oldTable[i];
      ChHTNode *node = headNode.Nodes;

      do
      {
        if (!node)
          break;

        ChHTNode *prev_node;

        ChHTNode *temp = node;
        node = node->Next;

        // Get index in table
        unsigned i = _stats.HashFunc_(temp->Key, _stats.TableSize_);

        // check if node exist in new table
        ChHTNode *NodeFound = SearchNode(i, Key, prev_node);

        // If node found is not the first node, have to check for duplicate
        // If there is a duplicate, throw an exception
        if (NodeFound != NULL)
        {
          throw HashTableException(HashTableException::E_DUPLICATE,
                                   "Key inserted is already in Hash Table");
        }

        temp->Next = _table[i].Nodes;
        _table[i].Nodes = temp;
        _table[i].Count++;
      } while (node);

      oldTable[i].Nodes = NULL;
    }

    delete[] oldTable;
    _stats.Expansions_++;
  }

  // Get index in table
  unsigned i = _stats.HashFunc_(Key, _stats.TableSize_);

  ChHTNode *prev_node;

  ChHTNode *node = SearchNode(i, Key, prev_node);

  if (node != NULL)
  {
    throw HashTableException(HashTableException::E_DUPLICATE,
                             "Key inserted is already in the Hash Table");
  }

  // Create and insert node
  node = CreateNode(Key, Data);
  node->Next = _table[i].Nodes;
  _table[i].Nodes = node;

  _table[i].Count++;
  _stats.Count_++;
}
