#include "ObjectAllocator.h"
#include <bits/stdc++.h>

// Constructor
// ObjectAllocator constructor
ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig &config)
    : PageList_(nullptr), FreeLisst_(nullptr), ObjectSize(ObjectSize), Config(config)
{
    // Calculate the actual size of each block, including padding and headers
    size_t blockSize = ObjectSize + Config.PadBytes_ + Config.HBlockInfo_.size_;

    // Ensure the block size is aligned according to the specified alignment
    if (Config.Alignment_ > 1)
    {
        size_t remainder = blockSize % Config.Alignment_;
        if (remainder != 0)
        {
            blockSize += Config.Alignment_ - remainder;
        }
    }

    // Calculate the page size, including all headers, padding, etc.
    PageSize = (blockSize + Config.PadBytes_) * Config.ObjectsPerPage_ + sizeof(GenericObject);

    // Set the alignment-related sizes
    Config.LeftAlignSize_ = (Config.Alignment_ > 1) ? Config.Alignment_ : 0;
    Config.InterAlignSize_ = (Config.ObjectsPerPage_ > 1) ? (Config.ObjectsPerPage_ - 1) * Config.Alignment_ : 0;

    // Explicitly set to 0 when the condition is not true
    if (Config.LeftAlignSize_ == 0)
        Config.InterAlignSize_ = 0;

    // Allocate the first page
    GenericObject *newPage = static_cast<GenericObject *>(::operator new(PageSize));
    newPage->Next = PageList_; // Set Next to the existing PageList
    PageList_ = newPage;       // Update PageList to point to the new page

    // Set up the FreeList by splitting the page into blocks
    FreeLisst_ = newPage;
    GenericObject *current = newPage;

    for (unsigned i = 1; i < Config.ObjectsPerPage_; ++i)
    {
        // Calculate the offset for the next block with alignment and padding consideration
        size_t offset = i * blockSize + Config.PadBytes_;
        if (Config.Alignment_ > 1)
        {
            size_t remainder = offset % Config.Alignment_;
            if (remainder != 0)
            {
                offset += Config.Alignment_ - remainder;
            }
        }

        GenericObject *nextBlock = reinterpret_cast<GenericObject *>(reinterpret_cast<char *>(current) + offset);
        nextBlock->Next = FreeLisst_;
        FreeLisst_ = nextBlock;
        current = nextBlock;
    }

    // Initialize stats
    Stats.PagesInUse_ = 1;
    Stats.ObjectsInUse_ = 0;
    Stats.FreeObjects_ = Config.ObjectsPerPage_;
    Stats.ObjectSize_ = ObjectSize;
    Stats.PageSize_ = PageSize;
}
ObjectAllocator::~ObjectAllocator()
{
    // Free all allocated pages
    while (PageList_ != nullptr)
    {
        GenericObject *nextPage = PageList_->Next;
        ::operator delete(PageList_);
        PageList_ = nextPage;
    }

    // Reset FreeList (optional, as the destructor will be called when the program exits)
    FreeLisst_ = nullptr;
}

// Allocate
// ObjectAllocator Allocate function
void *ObjectAllocator::Allocate(const char *label)
{
    if (FreeLisst_ == nullptr)
    {
        // No free blocks available, allocate a new page
        if (Config.MaxPages_ == 0 || Stats.PagesInUse_ < Config.MaxPages_)
        {
            // Allocate a new page
            GenericObject *newPage = static_cast<GenericObject *>(::operator new(PageSize));
            newPage->Next = PageList_;
            PageList_ = newPage;
            ++Stats.PagesInUse_;
            ++Stats.ObjectsInUse_;
            ++Stats.Allocations_;
            // Add new blocks to the FreeList
            size_t blockSize = ObjectSize + Config.PadBytes_ + Config.HBlockInfo_.size_;

            // Ensure the block size is aligned according to the specified alignment
            if (Config.Alignment_ > 1)
            {
                size_t remainder = blockSize % Config.Alignment_;
                if (remainder != 0)
                {
                    blockSize += Config.Alignment_ - remainder;
                }
            }

            GenericObject *current = newPage;
            for (unsigned i = 1; i < Config.ObjectsPerPage_; ++i)
            {
                GenericObject *nextBlock = reinterpret_cast<GenericObject *>(reinterpret_cast<char *>(current) + blockSize);
                nextBlock->Next = FreeLisst_;
                FreeLisst_ = nextBlock;
                current = nextBlock;
            }
        }
        else
        {
            // Maximum pages limit reached
            throw OAException(OAException::E_NO_PAGES, "Maximum pages limit reached.");
        }
    }

    // Pop a block from the FreeList
    GenericObject *allocatedBlock = FreeLisst_;
    FreeLisst_ = allocatedBlock->Next;

    ++Stats.ObjectsInUse_;
    ++Stats.Allocations_;

    // Ensure FreeObjects_ doesn't go negative
    if (Stats.FreeObjects_ > 0)
        --Stats.FreeObjects_;

    if (Stats.Allocations_ > Stats.MostObjects_)
    {
        Stats.MostObjects_ = Stats.Allocations_;
    }
    return allocatedBlock;
}
void ObjectAllocator::Free(void *Object)
{
    // Handle the case where the provided object is nullptr
    if (Object == nullptr)
    {
        throw OAException(OAException::E_NO_MEMORY, "Attempting to free a nullptr.");
    }

    // Check if the provided object falls within the boundaries of a valid allocated block
    GenericObject *allocatedBlock = PageList_;
    while (allocatedBlock != nullptr)
    {
        // Determine the start and end addresses of the allocated block, considering header size
        char *blockStart = reinterpret_cast<char *>(allocatedBlock) + sizeof(GenericObject) + Config.HBlockInfo_.size_;
        char *blockEnd = blockStart + PageSize - sizeof(GenericObject);

        // Calculate the address of the provided object
        char *objectAddress = reinterpret_cast<char *>(Object);

        // Check if the provided object is within the boundaries of this allocated block
        if (objectAddress >= blockStart && objectAddress < blockEnd)
        {
            // Calculate the offset of the provided object from the start of the block
            size_t offset = objectAddress - blockStart;

            // Adjust the offset for alignment and padding considerations
            if (Config.Alignment_ > 1)
            {
                size_t remainder = offset % Config.Alignment_;
                if (remainder != 0)
                {
                    offset += Config.Alignment_ - remainder;
                }
            }

            // Calculate the address of the block to free
            GenericObject *freedBlock = reinterpret_cast<GenericObject *>(blockStart + offset - Config.HBlockInfo_.size_);

            // Push the block back onto the FreeList
            freedBlock->Next = FreeLisst_;
            FreeLisst_ = freedBlock;

            // Update stats
            --Stats.ObjectsInUse_;
            ++Stats.Deallocations_;
            ++Stats.FreeObjects_; // Adjust the count of free objects
            return;               // Exit the function after successful deallocation
        }

        allocatedBlock = allocatedBlock->Next;
    }

    // If the provided object is not within the boundaries of any allocated block, throw an exception
    throw OAException(OAException::E_BAD_BOUNDARY, "Attempting to free an object with a bad boundary.");
}

unsigned ObjectAllocator::FreeEmptyPages()
{
    unsigned freedPages = 0;

    // Iterate through pages and free the ones with no allocated blocks
    GenericObject *current = PageList_;
    GenericObject *prev = nullptr;

    while (current != nullptr)
    {
        if (FreeLisst_ == nullptr)
        {
            // No free blocks, free the entire page
            if (prev == nullptr)
            {
                // First page
                PageList_ = current->Next;
            }
            else
            {
                prev->Next = current->Next;
            }

            GenericObject *nextPage = current->Next;
            ::operator delete(current);
            current = nextPage;

            ++freedPages;
        }
        else
        {
            prev = current;
            current = current->Next;
        }
    }

    Stats.PagesInUse_ -= freedPages;

    return freedPages;
}
// unsigned ObjectAllocator::DumpMemoryInUse(DUMPCALLBACK fn) const
// {

// }
// GetPageList
const void *ObjectAllocator::GetPageList() const
{
    return PageList_;
}

// GetConfig
OAConfig ObjectAllocator::GetConfig() const
{
    return Config;
}

// GetStats
OAStats ObjectAllocator::GetStats() const
{
    return Stats;
}
