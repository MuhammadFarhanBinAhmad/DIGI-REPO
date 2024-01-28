/******************************************************************************/
/*!
\file:		ObjectAllocator.cpp
\author:    Muhammad Farhan Bin Ahmad, 2200544
\par email: b.muhammadfarhan@digipen.edu
*/
/******************************************************************************/

#include "ObjectAllocator.h"
#include <cstring>

#define u_char unsigned char

ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig &config)
    : Config_{config}, Stats_{}, PageList_{nullptr}, FreeList_{nullptr}, MidBlockSize{0}, Offset{0}
{
    Stats_.ObjectSize_ = ObjectSize;

    // check if left alignment needs to be calculated
    if (Config_.Alignment_ > 1)
    {
        // calculate byte needed for left alignment
        size_t left_bytes = sizeof(void *) + Config_.HBlockInfo_.size_ + Config_.PadBytes_;

        Config_.LeftAlignSize_ = Config_.Alignment_ - (static_cast<unsigned>(left_bytes) % Config_.Alignment_);

        // calculate byte needed for inter alignment
        size_t inter_bytes = Stats_.ObjectSize_ + Config_.HBlockInfo_.size_ + Config_.PadBytes_ * 2;

        Config_.InterAlignSize_ = Config_.Alignment_ - (static_cast<unsigned>(inter_bytes) % Config_.Alignment_);
    }

    size_t tempsize = 0;

    // left alignment size
    // nextP + al (left alignment). Only first block has left alignment
    tempsize = sizeof(void *) + Config_.LeftAlignSize_;

    // InterAlignSize_
    tempsize += Config_.ObjectsPerPage_ * (Config_.PadBytes_ + Config_.HBlockInfo_.size_ + Stats_.ObjectSize_ + Config_.PadBytes_);

    tempsize += (Config_.ObjectsPerPage_ - 1) * Config_.InterAlignSize_;

    Stats_.PageSize_ = tempsize;

    // calculate size of block
    MidBlockSize = Config_.HBlockInfo_.size_ + Config_.InterAlignSize_ + Config_.PadBytes_ * 2 + Stats_.ObjectSize_;

    // calculate page size
    Stats_.PageSize_ = sizeof(void *) + Config_.LeftAlignSize_ + (Config_.ObjectsPerPage_ * MidBlockSize) - Config_.InterAlignSize_;

    // calculate offset to start at s
    // offset = P + al + h + s
    Offset = sizeof(void *) + Config_.LeftAlignSize_ + Config_.PadBytes_ + Config_.HBlockInfo_.size_;

    // if memory is allocated
    if (Config_.UseCPPMemManager_)
    {
        return;
    }
    // Page Allocation
    addPage();
}

ObjectAllocator::~ObjectAllocator()
{
    u_char *page;

    while (PageList_ != NULL)
    {
        page = reinterpret_cast<u_char *>(PageList_);

        PageList_ = PageList_->Next;
        delete[] page;
    }
}
void ObjectAllocator::addPage()
{
    // Check if maximum pages is reached
    if (Config_.MaxPages_ && (Stats_.PagesInUse_ == Config_.MaxPages_))
    {
        throw OAException(OAException::E_NO_PAGES, "maximum page allocated");
    }

    GenericObject *newPage;

    try
    {
        // allocate memory for new page
        newPage = reinterpret_cast<GenericObject *>(new u_char[Stats_.PageSize_]);

        Stats_.PagesInUse_++;
    }
    catch (std::bad_alloc &)
    {
        throw OAException(OAException::E_NO_PAGES, "Not enough memory to add new page");
    }

    // link PageList_
    newPage->Next = PageList_;
    PageList_ = newPage;

    // Putting object onto free list
    unsigned char *temp = reinterpret_cast<unsigned char *>(newPage);
    temp += sizeof(void *);

    memset(temp, ALIGN_PATTERN, Config_.LeftAlignSize_);

    temp += (Offset - sizeof(void *));

    for (unsigned int i = 0; i < Config_.ObjectsPerPage_; i++)
    {
        Stats_.FreeObjects_++;

        if (i != Config_.ObjectsPerPage_ - 1)
        {
            std::memset(reinterpret_cast<unsigned char *>(temp) + Stats_.ObjectSize_ + Config_.PadBytes_, ALIGN_PATTERN, Config_.InterAlignSize_);
        }
        if (Config_.DebugOn_)
        {
            std::memset(temp - Config_.PadBytes_ - Config_.HBlockInfo_.size_, 0, Config_.HBlockInfo_.size_);
            std::memset(temp - Config_.PadBytes_, PAD_PATTERN, Config_.PadBytes_);
            std::memset(temp + Stats_.ObjectSize_, PAD_PATTERN, Config_.PadBytes_);

            std::memset(temp, UNALLOCATED_PATTERN, Stats_.ObjectSize_);
        }
        reinterpret_cast<GenericObject *>(temp)->Next = FreeList_;
        FreeList_ = reinterpret_cast<GenericObject *>(temp);

        temp += Stats_.ObjectSize_ + 2 * Config_.PadBytes_ + Config_.HBlockInfo_.size_ + Config_.InterAlignSize_;
    }
}
void *ObjectAllocator::Allocate(const char *label)
{
    if (Config_.UseCPPMemManager_)
    {
        try
        {
            u_char *newObj = new u_char[Stats_.ObjectSize_];
            Stats_.Allocations_++;
            Stats_.ObjectsInUse_++;

            if (Stats_.ObjectsInUse_ > Stats_.MostObjects_)
            {
                Stats_.MostObjects_ = Stats_.ObjectsInUse_;
            }

            Stats_.FreeObjects_--;

            return newObj;
        }
        catch (std::bad_alloc &)
        {
            throw OAException(OAException::E_NO_MEMORY, "Not enough memory!");
        }
    }

    // Freelist is empty, no page allocated
    if (FreeList_ == nullptr)
    {
        if (Stats_.PagesInUse_ < Config_.MaxPages_ || Config_.MaxPages_ == 0)
        {
            addPage();
        }
        else
        {
            throw OAException(OAException::E_NO_PAGES, "No available page!");
        }
    }

    GenericObject *object = FreeList_;
    FreeList_ = FreeList_->Next;

    if (Config_.DebugOn_)
    {
        std::memset(object, ALLOCATED_PATTERN, Stats_.ObjectSize_);
    }

    Stats_.Allocations_++;
    Stats_.ObjectsInUse_++;

    if (Stats_.ObjectsInUse_ > Stats_.MostObjects_)
    {
        Stats_.MostObjects_ = Stats_.ObjectsInUse_;
    }
    Stats_.FreeObjects_--;

    switch (Config_.HBlockInfo_.type_)
    {
    case OAConfig::hbBasic:
    {
        // Start of header
        u_char *headerStart = reinterpret_cast<u_char *>(object) - Config_.HBlockInfo_.size_ - Config_.PadBytes_;

        unsigned *allocationNumber = reinterpret_cast<unsigned *>(headerStart);
        *allocationNumber = Stats_.Allocations_;

        // Start of flag
        u_char *flag = reinterpret_cast<u_char *>(sizeof(unsigned) + headerStart);

        *flag = true;

        break;
    }
    case OAConfig::hbExtended:
    {
        // Start of Flag
        u_char *flagStart = reinterpret_cast<u_char *>(object) - Config_.PadBytes_ - sizeof(u_char);

        *flagStart = true;

        // Start of allocation number
        u_char *allocNumStart = flagStart - sizeof(unsigned);

        unsigned *allocationNumber = reinterpret_cast<unsigned *>(allocNumStart);

        *allocationNumber = Stats_.Allocations_;

        // Start of use-count
        u_char *useCountStart = allocNumStart - sizeof(unsigned short);

        unsigned short *useCount = reinterpret_cast<unsigned short *>(useCountStart);

        (*useCount)++;

        break;
    }
    case OAConfig::hbExternal:
    {
        // one unsigned for allocation number, one flag to determine on off
        u_char *headerStart = reinterpret_cast<u_char *>(object) - Config_.PadBytes_ - Config_.HBlockInfo_.size_;

        MemBlockInfo **memPtr = reinterpret_cast<MemBlockInfo **>(headerStart);

        try
        {
            *memPtr = new MemBlockInfo;

            (*memPtr)->in_use = true;
            (*memPtr)->label = nullptr;
            (*memPtr)->alloc_num = Stats_.Allocations_;

            if (label)
            {
                try
                {
                    (*memPtr)->label = new char[strlen(label) + 1];
                }
                catch (std::bad_alloc &)
                {
                    throw OAException(OAException::E_NO_MEMORY, "Out of memory!");
                }

                std::strcpy((*memPtr)->label, label);
            }
        }
        catch (std::bad_alloc &)
        {
            throw OAException(OAException::E_NO_MEMORY, "Out of memory!");
        }
        break;
    }

    default:
        break;
    }

    return object;
}

void ObjectAllocator::Free(void *Object)
{
    if (Config_.UseCPPMemManager_)
    {
        delete[] reinterpret_cast<u_char *>(Object);

        Stats_.ObjectsInUse_--;
        Stats_.Deallocations_++;
        Stats_.FreeObjects_++;

        return;
    }

    GenericObject *page = PageList_;
    u_char *objAddress = reinterpret_cast<u_char *>(Object);

    // Only perform check when debugging
    if (Config_.DebugOn_)
    {
        bool onBound = false;
        bool corrupted = false;
        bool alreadyFreed = true;

        do
        {
            if (reinterpret_cast<u_char *>(page) < objAddress &&
                objAddress < reinterpret_cast<u_char *>(page) + Stats_.PageSize_)
            {
                u_char *blockStart = reinterpret_cast<u_char *>(page) + Offset;

                size_t separation = MidBlockSize;

                if ((objAddress - blockStart) % separation == 0)
                {
                    onBound = true;
                }
            }

            page = page->Next;
        } while (page != NULL);

        if (onBound == false)
        {
            throw(OAException(OAException::E_BAD_BOUNDARY, "Object not on a block boundary"));
        }
        else
        {
            // Check padding blocks
            u_char *leftPad = objAddress - Config_.PadBytes_;
            u_char *rightPad = objAddress + Stats_.ObjectSize_;

            for (unsigned int i = 0; i < Config_.PadBytes_; ++i)
            {
                if (leftPad[i] != PAD_PATTERN || rightPad[i] != PAD_PATTERN)
                {
                    corrupted = true;
                    break;
                }
            }
            // check data block
            for (unsigned i = sizeof(u_char *); i < Stats_.ObjectSize_; ++i)
            {
                if (objAddress[i] != FREED_PATTERN)
                {
                    alreadyFreed = false;
                    break;
                }
            }
        }

        if (alreadyFreed)
        {
            throw(OAException(OAException::E_MULTIPLE_FREE, "Block already freed once"));
        }
        else if (corrupted)
        {
            throw(OAException(OAException::E_CORRUPTED_BLOCK, "Block is corrupted"));
        }
    }

    u_char *headerStart = reinterpret_cast<u_char *>(objAddress) - Config_.PadBytes_ - Config_.HBlockInfo_.size_;

    switch (Config_.HBlockInfo_.type_)
    {
    case OAConfig::hbBasic:
    {
        std::memset(headerStart, 0, OAConfig::BASIC_HEADER_SIZE);
        break;
    }
    case OAConfig::hbExtended:
    {
        std::memset(headerStart + Config_.HBlockInfo_.additional_ + sizeof(unsigned short), 0, OAConfig::BASIC_HEADER_SIZE);
        break;
    }
    case OAConfig::hbExternal:
    {
        MemBlockInfo **memPtr = reinterpret_cast<MemBlockInfo **>(headerStart);

        delete[] (*memPtr)->label;
        delete *memPtr;

        std::memset(memPtr, 0, Config_.HBlockInfo_.size_);
    }
    default:
        break;
    }

    if (Config_.DebugOn_)
    {
        std::memset(Object, FREED_PATTERN, Stats_.ObjectSize_);
    }

    GenericObject *object = reinterpret_cast<GenericObject *>(Object);
    object->Next = FreeList_;
    FreeList_ = object;

    Stats_.ObjectsInUse_--;
    Stats_.Deallocations_++;
    Stats_.FreeObjects_++;
}

unsigned ObjectAllocator::DumpMemoryInUse(DUMPCALLBACK fn) const
{
    GenericObject *page = PageList_;

    do
    {
        u_char *block = reinterpret_cast<u_char *>(page) + Offset;

        for (unsigned i = 0; i < Config_.ObjectsPerPage_; i++)
        {
            if (*block == ALLOCATED_PATTERN)
            {
                fn(block, Stats_.ObjectSize_);
            }
            if (i < Config_.ObjectsPerPage_ - 1)
            {
                block += MidBlockSize;
            }
        }

        page = page->Next;
    } while (page);

    return Stats_.ObjectsInUse_;
}

unsigned ObjectAllocator::ValidatePages(VALIDATECALLBACK fn) const
{
    if (Config_.PadBytes_ == 0)
    {
        return 0;
    }

    unsigned corruptedBlocks = 0;
    GenericObject *page = PageList_;

    do
    {
        u_char *block = reinterpret_cast<u_char *>(page) + Offset;

        for (unsigned i = 0; i < Config_.ObjectsPerPage_; i++)
        {
            // Check padding blocks
            u_char *leftPad = block - Config_.PadBytes_;
            u_char *rightPad = block + Stats_.ObjectSize_;

            // Prevents pointer arithmetic overrun
            if (i < Config_.ObjectsPerPage_ - 1)
            {
                block += MidBlockSize;
            }

            for (unsigned j = 0; j < Config_.PadBytes_; j++)
            {
                if (leftPad[j] != PAD_PATTERN || rightPad[j] != PAD_PATTERN)
                {
                    fn(block, Stats_.ObjectSize_);
                    corruptedBlocks++;
                    break;
                }
            }
        }
        page = page->Next;
    } while (page);

    return corruptedBlocks;
}

unsigned ObjectAllocator::FreeEmptyPages()
{
    if (PageList_ == nullptr)
    {
        return 0;

    }
    unsigned emptyPages = 0;

    GenericObject *temp = PageList_;
    GenericObject *previous = nullptr;

    // If head node holds a key or multiple key
    while (temp != nullptr && isPageEmpty(temp))
    {
        // Change head
        PageList_ = temp->Next;
        // free page
        removePgObjInFreeList(temp);
        delete[] reinterpret_cast<u_char *>(temp);
        Stats_.PagesInUse_--;

        // Change temp
        temp = PageList_;
        emptyPages++;
    }

    // Delete occurance other than head
    while (temp != nullptr)
    {
        // Search key to be deleted
        // Keep track of previous node as we need to change previous->Next
        while (temp != nullptr && !isPageEmpty(temp))
        {
            previous = temp;
            temp = temp->Next;
        }

        // If key not present in linked list
        if (temp == nullptr)
        {
            return emptyPages;
        }
        // Unlink node from linked list
        previous->Next = temp->Next;
        removePgObjInFreeList(temp);
        delete[] reinterpret_cast<u_char *>(temp);
        Stats_.PagesInUse_--;

        // Update temp for next loop
        temp = previous->Next;
        emptyPages++;
    }
    return emptyPages;
}

bool ObjectAllocator::isPageEmpty(GenericObject *page)
{
    GenericObject *freeList = FreeList_;

    unsigned freeWithinPage = 0;

    do
    {
        if (inPage(page, reinterpret_cast<u_char *>(freeList)))
        {
            freeWithinPage++;

            if (freeWithinPage >= Config_.ObjectsPerPage_)
            {
                return true;
            }
        }
        freeList = freeList->Next;
    } while (freeList);

    return false;
}

void ObjectAllocator::removePgObjInFreeList(GenericObject *pageAddress)
{
    GenericObject *temp = FreeList_;
    GenericObject *previous = nullptr;

    // If head node itself holds the key or multiple keys
    do
    {
        // Change head
        FreeList_ = temp->Next;

        // Change temp
        temp = FreeList_;
        Stats_.FreeObjects_--;
    } while (temp != nullptr && inPage(pageAddress, reinterpret_cast<u_char *>(temp)));

    // Delete occurrences other than head
    do
    {
        // Search key to be deleted
        // Keep track of the previous node, need to change previous->Next
        while (temp != nullptr && !inPage(pageAddress, reinterpret_cast<u_char *>(temp)))
        {
            previous = temp;
            temp = temp->Next;
        }

        // If the key is not present in the linked list
        if (temp == nullptr)
        {
            return;
        }

        // Unlink node from the linked list
        previous->Next = temp->Next;

        Stats_.FreeObjects_--;

        // Update temp for the next loop
        temp = previous->Next;
    } while (temp != nullptr);
}

bool ObjectAllocator::inPage(GenericObject *pageAddress, u_char *address)
{
    return (address < reinterpret_cast<u_char *>(pageAddress) + Stats_.PageSize_ && address >= reinterpret_cast<u_char *>(pageAddress));
}

void ObjectAllocator::SetDebugState(bool State)
{
    Config_.DebugOn_ = State;
}

const void *ObjectAllocator::GetFreeList() const
{
    return FreeList_;
}

const void *ObjectAllocator::GetPageList() const
{
    return PageList_;
}

OAConfig ObjectAllocator::GetConfig() const
{
    return Config_;
}

OAStats ObjectAllocator::GetStats() const
{
    return Stats_;
}