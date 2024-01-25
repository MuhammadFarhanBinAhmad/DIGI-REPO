#include "ObjectAllocator.h"
#include <bits/stdc++.h>
#include <cstring>

#define u_char unsigned char
// Constructor
// ObjectAllocator constructor
ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig &config)
    : PageList_(nullptr), FreeList_(nullptr), ObjectSize(ObjectSize), Config(config), Stats{}
{

    Stats.ObjectSize_ = ObjectSize;

    // Need check if left allignment need to be calculated
    if (Config.Alignment_ > 1)
    {
        // Get inter allignment
        size_t InterBytes = Stats.ObjectSize_ + (Config.PadBytes_ * 2) + Config.HBlockInfo_.size_;

        Config.InterAlignSize_ = Config.Alignment_ - (static_cast<unsigned>(InterBytes) % Config.Alignment_);

        // Calculate byte needed for left alignment
        size_t LeftBytes = sizeof(void *) + Config.PadBytes_ + Config.HBlockInfo_.size_;

        Config.LeftAlignSize_ = Config.Alignment_ - (static_cast<unsigned>(LeftBytes) & Config.Alignment_);
    }

    size_t size{};

    // left allignment size
    // only 1st block has left allignemtn
    size = sizeof(void *) + Config.LeftAlignSize_;

    // Interalign size
    size += Config.ObjectsPerPage_ * (Config.PadBytes_ + Config.PadBytes_ + Config.HBlockInfo_.size_ + Stats.ObjectSize_);
    size += (Config.ObjectsPerPage_ - 1) * Config.InterAlignSize_;

    Stats.PageSize_ = size;

    // Calculate Midblock size
    MidBlockSize = Config.HBlockInfo_.size_ + Config.PadBytes_ * 2 + Stats.ObjectSize_ + Config.InterAlignSize_;

    // Calcule pagesize
    Stats.PageSize_ = sizeof(void *) + Config.LeftAlignSize_ + (Config.ObjectsPerPage_ * MidBlockSize) - Config.InterAlignSize_;

    // Calculate offset value
    OffSet = sizeof(void *) + Config.HBlockInfo_.size_ + Config.PadBytes_ + Config.LeftAlignSize_;

    if (Config.UseCPPMemManager_)
    {
        return;
    }

    AddPage();
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

void ObjectAllocator::AddPage()
{
    if ((Stats.PagesInUse_ == Config.MaxPages_) && Config.MaxPages_)
    {
        throw OAException(OAException::E_NO_PAGES, "Maximum page allocated");
    }

    GenericObject *newPage;

    try
    {
        newPage = reinterpret_cast<GenericObject *>(new u_char[Stats.PageSize_]);

        Stats.PagesInUse_++;
    }
    catch (std::bad_alloc &)
    {
        throw OAException(OAException::E_NO_PAGES, "Not enough memory to add new page");
    }

    newPage->Next = PageList_;
    PageList_ = newPage;

    unsigned char *temp = reinterpret_cast<unsigned char *>(newPage);
    temp += sizeof(void *);

    std::memset(temp, ALIGN_PATTERN, Config.LeftAlignSize_);

    temp += (OffSet - sizeof(void *));

    for (size_t i = 0; i < Config.ObjectsPerPage_; i++)
    {
        Stats.FreeObjects_++;

        if (Config.DebugOn_)
        {
            std::memset(temp - Config.PadBytes_ - Config.HBlockInfo_.size_, 0, Config.HBlockInfo_.size_);
            std::memset(temp - Config.PadBytes_, PAD_PATTERN, Config.PadBytes_);
            std::memset(temp + Stats.ObjectSize_, PAD_PATTERN, Config.PadBytes_);
            std::memset(temp, UNALLOCATED_PATTERN, Stats.ObjectSize_);
        }

        if (i != Config.ObjectsPerPage_ - 1)
        {
            std::memset(reinterpret_cast<unsigned char *>(temp) + Stats.ObjectSize_ + Config.PadBytes_, ALIGN_PATTERN, Config.InterAlignSize_);
        }

        reinterpret_cast<GenericObject *>(temp)->Next = FreeList_;
        FreeList_ = reinterpret_cast<GenericObject *>(temp);

        temp += Stats.ObjectSize_ + 2 * Config.PadBytes_ + Config.InterAlignSize_ + Config.HBlockInfo_.size_;
    }
}
// Allocate
// ObjectAllocator Allocate function
void *ObjectAllocator::Allocate(const char *label)
{
    if (Config.UseCPPMemManager_)
    {
        try
        {
            u_char *newObj = new u_char[Stats.ObjectSize_];
            // Upade the OA stats
            Stats.Allocations_++;
            Stats.ObjectsInUse_++;

            if (Stats.ObjectsInUse_ > Stats.MostObjects_)
            {
                Stats.MostObjects_ = Stats.ObjectsInUse_;
            }
            Stats.FreeObjects_--;

            return newObj;
        }
        catch (std::bad_alloc &)
        {
            throw OAException(OAException::E_NO_MEMORY, "Not enough memory!");
        }
    }

    // Freelist is emprt, no page allocate
    if (FreeList_ == NULL)
    {
        if (Stats.PagesInUse_ < Config.MaxPages_ || Config.MaxPages_ == 0)
        {
            AddPage();
        }
        else
        {
            throw OAException(OAException::E_NO_PAGES, "No available page!");
        }
    }

    GenericObject *object = FreeList_;
    FreeList_ = FreeList_->Next;

    if (Config.DebugOn_)
    {
        memset(object, ALLOCATED_PATTERN, Stats.ObjectSize_);
    }

    // Update OAstats
    ++Stats.Allocations_;
    ++Stats.ObjectsInUse_;

    if (Stats.ObjectsInUse_ > Stats.MostObjects_)
    {
        Stats.MostObjects_ = Stats.ObjectsInUse_;
    }
    --Stats.FreeObjects_;

    switch (Config.HBlockInfo_.type_)
    {
    case OAConfig::hbBasic:
    {
        u_char *HeaderStart = reinterpret_cast<u_char *>(object) - Config.HBlockInfo_.size_ - Config.PadBytes_;

        unsigned *AllocationNumber = reinterpret_cast<unsigned *>(HeaderStart);
        *AllocationNumber = Stats.Allocations_;

        u_char *flag = reinterpret_cast<u_char *>(HeaderStart + sizeof(unsigned));

        *flag = true;

        break;
    }
    case OAConfig::hbExternal:
    {
        // one unsigned for allocation number, one flag to determine on off
        u_char *headerStart = reinterpret_cast<u_char *>(object) - Config.PadBytes_ - Config.HBlockInfo_.size_;

        MemBlockInfo **memPtr =
            reinterpret_cast<MemBlockInfo **>(headerStart);

        try
        {
            *memPtr = new MemBlockInfo;

            (*memPtr)->in_use = true;
            (*memPtr)->label = nullptr;
            (*memPtr)->alloc_num = Stats.Allocations_;

            if (label)
            {
                try
                {
                    (*memPtr)->label = new char[strlen(label) + 1];
                }
                catch (std::bad_alloc &)
                {
                    throw OAException(OAException::E_NO_MEMORY,
                                      "Out of memory!");
                }

                strcpy((*memPtr)->label, label);
            }
        }
        catch (std::bad_alloc &)
        {
            throw OAException(OAException::E_NO_MEMORY, "Out of memory!");
        }
        break;
    }
    case OAConfig::hbExtended:
    {
        // Start of flag
        u_char *start = reinterpret_cast<u_char *>(object) - sizeof(u_char) - Config.PadBytes_;

        *start = true;

        // Start of allocation number
        u_char *allocNumberStart = start - sizeof(unsigned);

        unsigned *allocationNumber = reinterpret_cast<unsigned *>(allocNumberStart);

        *allocationNumber = Stats.Allocations_;

        u_char *CountStart = allocNumberStart - sizeof(unsigned short);

        unsigned short *UseCount = reinterpret_cast<unsigned short *>(CountStart);

        (*UseCount)++;

        break;
    }
    default:
        break;
    }

    return object;
}
void ObjectAllocator::Free(void *Object)
{
    if (Config.UseCPPMemManager_)
    {
        Stats.FreeObjects_++;
        Stats.Deallocations_++;
        Stats.ObjectsInUse_--;

        delete[] reinterpret_cast<unsigned char *>(Object);

        return;
    }

    GenericObject *page = PageList_;
    u_char *objAddress = reinterpret_cast<u_char *>(Object);

    // Need set debug mode here
    if (Config.DebugOn_)
    {
        bool onBound = false;
        bool corrupted = false;
        bool alreadyFreed = true;

        while (page != NULL)
        {
            if (reinterpret_cast<u_char *>(page) < objAddress && objAddress < reinterpret_cast<u_char *>(page) + Stats.PageSize_)
            {
                u_char *blockStart = reinterpret_cast<u_char *>(page) + OffSet;

                size_t separation = MidBlockSize;

                if ((objAddress - blockStart) % separation == 0)
                {
                    onBound = true;
                }
            }

            page = page->Next;
        }

        if (onBound == false)
        {
            throw(OAException(OAException::E_BAD_BOUNDARY, "Object not on a block boundary"));
        }
        else
        {
            // check data block
            unsigned i = sizeof(u_char *);
            while (i < Stats.ObjectSize_)
            {
                if (objAddress[i] != FREED_PATTERN)
                {
                    alreadyFreed = false;
                    break;
                }
                i++;
            }

            // Check padding blocks
            u_char *leftPad = objAddress - Config.PadBytes_;
            u_char *rightPad = objAddress + Stats.ObjectSize_;

            unsigned int j = 0;
            while (j < Config.PadBytes_)
            {
                if (leftPad[j] != PAD_PATTERN || rightPad[j] != PAD_PATTERN)
                {
                    corrupted = true;
                    break;
                }
                ++j;
            }
        }

        if (alreadyFreed == true)
        {
            throw(OAException(OAException::E_MULTIPLE_FREE,
                              "Block already freed once"));
        }
        else if (corrupted == true)
        {
            throw(OAException(OAException::E_CORRUPTED_BLOCK,
                              "Block is corrupted"));
        }
    }

    u_char *headerStart = reinterpret_cast<u_char *>(objAddress) - Config.PadBytes_ - Config.HBlockInfo_.size_;

    switch (Config.HBlockInfo_.type_)
    {
    case OAConfig::hbBasic:
    {
        memset(headerStart, 0, OAConfig::BASIC_HEADER_SIZE);
        break;
    }
    case OAConfig::hbExtended:
    {
        memset(headerStart + Config.HBlockInfo_.additional_ +
                   sizeof(unsigned short),
               0, OAConfig::BASIC_HEADER_SIZE);

        break;
    }
    case OAConfig::hbExternal:
    {
        MemBlockInfo **memPtr =
            reinterpret_cast<MemBlockInfo **>(headerStart);

        delete[] (*memPtr)->label;
        delete *memPtr;

        memset(memPtr, 0, Config.HBlockInfo_.size_);
    }
    default:
        break;
    }

    // if(Config.DebugOn_)
    // {
    //     memset(Object, FREED_PATTERN, Stats.ObjectSize_);
    // }

    GenericObject *object = reinterpret_cast<GenericObject *>(Object);
    object->Next = FreeList_;
    FreeList_ = object;

    --Stats.ObjectsInUse_;
    ++Stats.Deallocations_;
    ++Stats.FreeObjects_;
}
unsigned ObjectAllocator::ValidatePages(VALIDATECALLBACK fn) const
{
    if (Config.PadBytes_ == 0)
    {
        return 0;
    }

    u_char *right;
    u_char *left;
    u_char *block;

    unsigned corruptedBlocks{};
    GenericObject *page = PageList_;

    while (page)
    {
        block = reinterpret_cast<u_char *>(page) + OffSet;

        for (unsigned i = 0; i < Config.ObjectsPerPage_; ++i)
        {
            // Check padding blocks
            right = block + Stats.ObjectSize_;
            left = block - Config.PadBytes_;

            for (unsigned j = 0; j < Config.PadBytes_; ++j)
            {
                if (left[j] != PAD_PATTERN || right[j] != PAD_PATTERN)
                {
                    fn(block, Stats.ObjectSize_);
                    corruptedBlocks++;
                    break;
                }
            }

            // Prevents pointer arithmetic overrun
            if (i < Config.ObjectsPerPage_ - 1)
            {
                block += MidBlockSize;
            }
        }
        page = page->Next;
    }

    return corruptedBlocks;
}
unsigned ObjectAllocator::FreeEmptyPages()
{
    if (PageList_ == NULL)
    {
        return 0;
    }

    unsigned freedPages = 0;

    // Iterate through pages and free the ones with no allocated blocks
    GenericObject *current = PageList_;
    GenericObject *prev = nullptr;

    while (current != nullptr && PageEmpty((current)))
    {
        PageList_ = current->Next;

        // Freepage
        RemovePageObjectInFreeList(current);
        delete[] reinterpret_cast<u_char *>(current);
        Stats.PagesInUse_--;

        current = current->Next;
        freedPages++;

        // if (FreeLisst_ == nullptr)
        // {
        //     // No free blocks, free the entire page
        //     if (prev == nullptr)
        //     {
        //         // First page
        //         PageList_ = current->Next;
        //     }
        //     else
        //     {
        //         prev->Next = current->Next;
        //     }
    }

    while (!current)
    {
        while (!PageEmpty(current) && current != nullptr)
        {
            prev = current;
            current = current->Next;
        }

        // If key not present in linked list
        if (current == NULL)
        {
            return freedPages;
        }

        // Unlink node from linked list
        prev->Next = current->Next;
        // Freepage
        RemovePageObjectInFreeList(current);
        delete[] reinterpret_cast<u_char *>(current);
        Stats.PagesInUse_--;

        // Update temp for next loop
        current = prev->Next;
        freedPages++;
    }

    return freedPages;
}
bool ObjectAllocator::PageEmpty(GenericObject *page)
{
    unsigned int freePage{};
    GenericObject *tempFreeList = FreeList_;

    if (tempFreeList != nullptr)
    {
        do
        {
            if (IsInPage(page, reinterpret_cast<u_char *>(tempFreeList)))
            {
                freePage++;

                if (freePage >= Config.ObjectsPerPage_)
                {
                    return true;
                }
            }
            tempFreeList = tempFreeList->Next;
        } while (tempFreeList != nullptr);
    }

    return false;
}
void ObjectAllocator::RemovePageObjectInFreeList(GenericObject *pageAddress)
{
    GenericObject *temp = FreeList_;
    GenericObject *previous = nullptr;

    // If head node itself holds key or multiple keys
    do
    {
        // Change temp
        temp = FreeList_;
        Stats.FreeObjects_--;
        // Change head
        FreeList_ = temp->Next;

    } while (temp != nullptr && IsInPage(pageAddress, reinterpret_cast<u_char *>(temp)));

    // Delete occurrences other than head
    do
    {
        // Search key to be deleted
        // Keep track of previous node, need to change previous->Next
        while (!IsInPage(pageAddress, reinterpret_cast<u_char *>(temp)) && temp != nullptr)
        {
            previous = temp;
            temp = temp->Next;
        }

        // If key not present in linked list
        if (temp == nullptr)
        {
            return;
        }
        // Unlink node from linked list
        previous->Next = temp->Next;

        Stats.FreeObjects_--;

        // Update temp for the next iteration
        temp = previous->Next;

    } while (temp != nullptr);
}
bool ObjectAllocator::IsInPage(GenericObject *pageAddress, u_char *address)
{
    return (address >= reinterpret_cast<u_char *>(pageAddress) && address < reinterpret_cast<u_char *>(pageAddress) + Stats.PageSize_);
}
unsigned ObjectAllocator::DumpMemoryInUse(DUMPCALLBACK fn) const
{
    GenericObject *page = PageList_;

    u_char *block;

    while (page)
    {
        block = reinterpret_cast<u_char *>(page) + OffSet;

        for (int i = 0; i < Config.ObjectsPerPage_; i++)
        {
            if (i < Config.ObjectsPerPage_ - 1)
            {
                block += MidBlockSize;
            }

            if (*block == ALLOCATED_PATTERN)
            {
                fn(block, Stats.ObjectSize_);
            }
        }

        page = page->Next;
    }

    return Stats.ObjectsInUse_;
}
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
