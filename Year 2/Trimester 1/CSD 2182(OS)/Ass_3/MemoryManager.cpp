/*!************************************************************************
\file   MemoryManager.cpp
\author Muhammad Farhan Bin Ahmad(2200544)
\par    email: b.muhammadfarhan@digipen.edu
\par    Course: CSD 2182
\par    OS Part 3
\date   17-11-2023

\brief 	In this assignment you will write a simple memory manager for dynamically allocated
        memory. The memory manager will make use of a linked list to keep track of allocated and
        unallocated blocks of memory.
**************************************************************************/
#include "MemoryManager.h"
#include <list>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>

//set up mem block basic variable
MemoryManager::MemCtrlBlk::MemCtrlBlk(void* ptr, int size)
    : data(ptr), size(size), allocated(false) {}


//Merge 2 memblock together
void MemoryManager::MemCtrlBlk::Merge(MemCtrlBlk other)
{
    // Check if the other block is adjacent to this block
    // Merge the two blocks into a single block
    if (static_cast<char*>(data) + size == other.data)
    {
        size += other.size;
    }
    else
    {
        data = other.data;
        size += other.size;
    }
}
//Allocate space into the mempool
MemoryManager::MemoryManager(int total_bytes)
{
    mempool = new char[total_bytes];
    memoryBlock.emplace_back(mempool, total_bytes);
}
//DELETE
MemoryManager::~MemoryManager(void)
{
    delete[] static_cast<char*>(mempool);
}

void* MemoryManager::allocate(int bytes)
{
    //loop thorugh all the memblock
    for (std::list<MemCtrlBlk>::iterator it = memoryBlock.begin(); it != memoryBlock.end(); ++it)
    {
        //if current mem block is not allocated and has enough size
        if (!it->allocated && it->size >= bytes)
        {
            it->allocated = true;
            
            // Check if splitting is needed
            if (it->size > bytes)
            {
                //allocate new memctrlblock into list. need to offset position
                MemCtrlBlk newBlock(static_cast<char*>(it->data) + bytes, it->size - bytes);
                memoryBlock.insert(std::next(it), newBlock);
                it->size = bytes;
            }
            
            return it->data;
        }
    }
    return nullptr; // Allocation failed
}

void MemoryManager::deallocate(void* pointer)
{
    if (pointer != nullptr)
    {
        for (std::list<MemCtrlBlk>::iterator it = memoryBlock.begin(); it != memoryBlock.end() ; it++)
        {
            //Loop through the list to get the correct mem block
            if (it->allocated && it->data == pointer)
            {
                it->allocated = false;

                //Merge with previous block if exist and not allocated
                std::list<MemCtrlBlk>::iterator prevBlock = std::prev(it);
                if (prevBlock != memoryBlock.end() && !prevBlock->allocated)
                {
                    //merge with prev block and erase with the prev block from memblock list
                    it->Merge(*prevBlock);
                    memoryBlock.erase(prevBlock);
                }

                //Merge with next block if exist and not allocated
                std::list<MemCtrlBlk>::iterator nextblock = std::next(it);
                if (nextblock != memoryBlock.end() && !nextblock->allocated)
                {
                    //merge with next block and erase with the next block from memblock list
                    it->Merge(*nextblock);
                    memoryBlock.erase(nextblock);
                }
                break;
            }
        }
    }
}

void MemoryManager::dump(std::ostream& out)
{
    for (const MemCtrlBlk& block : memoryBlock)
    {
        out << "relative to start address: " << std::hex << static_cast<char*>(block.data) - static_cast<char*>(mempool) << std::endl;
        //out << std::dec; // Set the output stream back to decimal mode
        out << "  byte count: " << block.size << std::endl;
        out << "  allocated? " << (block.allocated ? "true" : "false") << std::endl;
    }
}