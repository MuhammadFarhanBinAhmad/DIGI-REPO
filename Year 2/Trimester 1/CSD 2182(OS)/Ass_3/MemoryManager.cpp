// MemoryManager.cpp
#include "MemoryManager.h"

MemoryManager::MemoryManager(int total_bytes) {
    // Allocate the entire heap
    mempool = ::operator new(total_bytes);

    // Create the initial memory block representing the entire heap
    MemCtrlBlk initialBlock(mempool, total_bytes);
    memoryBlock.push_back(initialBlock);
}

MemoryManager::~MemoryManager() {
    // Cleanup or deallocate any resources in the destructor
    ::operator delete(mempool);
}

void* MemoryManager::allocate(int bytes) {
    for (auto& block : memoryBlock) {
        if (!block.allocated && block.size >= bytes) {
            // Allocate memory from this block
            block.allocated = true;
            return block.data;
        }
    }

    // No suitable block found
    return nullptr;
}

void MemoryManager::deallocate(void* pointer) {
    for (auto& block : memoryBlock) {
        if (block.data == pointer) {
            // Deallocate memory in this block
            block.allocated = false;
            return;
        }
    }
}

void MemoryManager::dump(std::ostream& out) {
    for (const auto& block : memoryBlock) {
        out << "Block at address " << block.data
            << ", size: " << block.size
            << ", allocated: " << (block.allocated ? "Yes" : "No")
            << std::endl;
    }
}
