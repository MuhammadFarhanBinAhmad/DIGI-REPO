#include "ObjectAllocator.h"
#include <bits/stdc++.h>

// Constructor
// ObjectAllocator constructor
ObjectAllocator::ObjectAllocator(size_t ObjectSize, const OAConfig &config)
    : PageList_(nullptr), FreeLisst_(nullptr), ObjectSize(ObjectSize), Config(config), Stats{}
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

    // Calculate offset value
    OffSet = sizeof(void *) + Config.HBlockInfo_.size_ + Config.PadBytes_ + Config.LeftAlignSize_;

    // Calculate Midblock size
    MidBlockSize = Config.HBlockInfo_.size_ + Config.PadBytes_ * 2 + Stats.ObjectSize_ + Config.InterAlignSize_;

    // Calcule pagesize
    Stats.PageSize_ = sizeof(void *) + Config.LeftAlignSize_ + (Config.ObjectsPerPage_ * MidBlockSize) - Config.InterAlignSize_;

    if (Config.UseCPPMemManager_)
    {
        return;
    }

    AddPage();
}
ObjectAllocator::AddPage()
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

        if (i != Config.ObjectsPerPage_ - 1)
        {
            std::memset(reinterpret_cast<unsigned char *>(temp) + Stats.ObjectSize_ + Config.PadBytes_, ALIGN_PATTERN, Config.InterAlignSize_);
        }

        if (Config.DebugOn_)
        {
            std::memset(temp - Config.PadBytes_ - Config.HBlockInfo_.size_, 0, Config.HBlockInfo_.size_);
            std::memset(temp - Config.PadBytes_, PAD_PATTERN, Config.PadBytes_);
            std::memset(temp + Stats.ObjectSize_, PAD_PATTERN, Config.PadBytes_);
            std::memset(temp, UNALLOCATED_PATTERN, Stats.ObjectSize_);
        }

        reinterpret_cast<GenericObject *>(temp)->Next = FreeLisst_;
        FreeLisst_ = reinterpret_cast<GenericObject *>(temp);

        temp += Stats.ObjectSize_ + (2 * Config.PadBytes_) + Config.InterAlignSize_ + Config.HBlockInfo_.size_;
    }
}
ObjectAllocator::~ObjectAllocator()
{
    unsigned char *page;

    while (PageList_ != NULL)
    {
        page = reinterpret_cast<unsigned char *>(PageList_);

        PageList_ = PageList_->Next;
        delete[] page;
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
            ++Stats.Allocations_;
            ++Stats.ObjectsInUse_;

            if (Stats.ObjectsInUse_ > Stats.MostObjects_)
            {
                Stats.MostObjects_ = Stats.ObjectsInUse_;
            }
            --Stats.FreeObjects_;

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
        unsigned char *HeaderStart = reinterpret_cast<unsigned char *>(object) - Config.HBlockInfo_.size_ - Config.PadBytes_;

        unsigned *AllocationNumber = reinterpret_cast<unsigned *>(HeaderStart);
        *AllocationNumber = Stats.Allocations_;

        unsigned char *flag = reinterpret_cast<unsigned char *>(HeaderStart + sizeof(unsigned));

        *flag = true;

        break;
    case OAConfig::hbExternal:

        break;
    case OAConfig::hbExtended:
        //Start of flag
        unsigned char* start = reinterpret_cast<unsigned char*>(object) - sizeof(unsigned char) - Config.PadBytes_;

        *flag = true;

        //Start of allocation number
        unsigned char* allocNumberStart = flag -  sizeof(unsigned);

        unsigned *allocationNumber = reinterpret_cast<unsigned*>(allocNumberStart);

        *allocationNumber = Stats.Allocations_;

        unsigned char* CountStart = allocNumberStart - sizeof(unsigned short);

        unsigned short* UseCount = reinterpret_cast<unsigned short*>(CountStart);

        (*UseCount)++;

        break;
    default:
        break;
    }

    return object;
}
void ObjectAllocator::Free(void *Object)
{
}

// unsigned ObjectAllocator::FreeEmptyPages()
// {
//     unsigned freedPages = 0;

//     // Iterate through pages and free the ones with no allocated blocks
//     GenericObject *current = PageList_;
//     GenericObject *prev = nullptr;

//     while (current != nullptr)
//     {
//         if (FreeLisst_ == nullptr)
//         {
//             // No free blocks, free the entire page
//             if (prev == nullptr)
//             {
//                 // First page
//                 PageList_ = current->Next;
//             }
//             else
//             {
//                 prev->Next = current->Next;
//             }

//             GenericObject *nextPage = current->Next;
//             ::operator delete(current);
//             current = nextPage;

//             ++freedPages;
//         }
//         else
//         {
//             prev = current;
//             current = current->Next;
//         }
//     }

//     Stats.PagesInUse_ -= freedPages;

//     return freedPages;
// }
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
