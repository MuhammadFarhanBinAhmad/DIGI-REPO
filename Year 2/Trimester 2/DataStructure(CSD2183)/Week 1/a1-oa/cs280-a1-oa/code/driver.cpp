#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using std::cout;
using std::endl;
using std::printf;

int SHOWADDRESS1 = 0;
int SHOWADDRESS2 = 0;
int SHOWREAL = 0;
int SHOW_EXCEPTIONS = 0;

#include "ObjectAllocator.h"
#include "PRNG.h"

struct Student
{
    int Age;
    float GPA;
    long Year;
    long ID;
};

struct Employee
{
    Employee *Next;
    char lastName[12];
    char firstName[12];
    float salary;
    int years;
};

ObjectAllocator *studentObjectMgr;
ObjectAllocator *employeeObjectMgr;

// Support functions
void PrintCounts(const ObjectAllocator *nm);
void PrintCounts2(const ObjectAllocator *nm);
void PrintConfig(const ObjectAllocator *nm);
void DumpPages(const ObjectAllocator *nm, unsigned width = 16);
void DumpPagesEx(const ObjectAllocator *nm, unsigned width = 16);

void DoStudents(unsigned padding = 0, bool printall = false); // debug, padding=X

struct Person
{
    char lastName[12];
    char firstName[12];
    float salary;
    int years;
};

struct Person PEOPLE[] = {
    {"Faith", "Ian", 80000, 10},
    {"Tufnel", "Nigel", 90000, 12},
    {"Savage", "Viv", 50000, 4},
    {"Shrimpton", "Mick", 50000, 4},
    {"Besser", "Joe", 40000, 1},
    {"Smalls", "Derek", 80000, 10},
    {"St.Hubbins", "David", 90000, 12},
    {"Fleckman", "Bobbi", 120000, 8},
    {"Eton-Hogg", "Denis", 250000, 22},
    {"Upham", "Denny", 60000, 5},
    {"McLochness", "Ross", 60000, 5},
    {"Pudding", "Ronnie", 50000, 2},
    {"Schindler", "Danny", 60000, 3},
    {"Pettibone", "Jeanine", 85000, 3},
    {"Fame", "Duke", 95000, 8},
    {"Fufkin", "Artie", 45000, 1},
    {"DiBergi", "Marty", 15000, 7},
    {"Floyd", "Pink", 25000, 6},
    {"Zeppelin", "Led", 35000, 3},
    {"Mason", "Nick", 15000, 7},
    {"Wright", "Richard", 17000, 9},
    {"Waters", "Roger", 10000, 3},
    {"Gilmore", "David", 19000, 5}};

//****************************************************************************************************
void DoStudents(unsigned padding, bool printall)
{
    try
    {
        bool newdel = false;
        bool debug = true;
        unsigned padbytes = padding;
        OAConfig::HeaderBlockInfo header(OAConfig::hbNone);
        unsigned alignment = 0;

        OAConfig config(newdel, 4, 2, debug, padbytes, header, alignment);
        studentObjectMgr = new ObjectAllocator(sizeof(Student), config);
    }
    catch (const OAException &e)
    {
        if (SHOW_EXCEPTIONS)
            cout << e.what() << endl;
        else
            cout << "Exception thrown during construction in DoStudents." << endl;
        return;
    }
    catch (...)
    {
        cout << "Unexpected exception thrown from constructor in DoStudents." << endl;
    }

    unsigned wrap = 32;
    PrintConfig(studentObjectMgr); //
    PrintCounts(studentObjectMgr);
    DumpPages(studentObjectMgr, wrap);

    Student *pStudent1 = 0, *pStudent2 = 0, *pStudent3 = 0;
    try
    {
        pStudent1 = static_cast<Student *>(studentObjectMgr->Allocate());
        PrintCounts(studentObjectMgr);
        if (printall)
            DumpPages(studentObjectMgr, wrap);
        pStudent2 = static_cast<Student *>(studentObjectMgr->Allocate());
        PrintCounts(studentObjectMgr);
        if (printall)
            DumpPages(studentObjectMgr, wrap);
        pStudent3 = static_cast<Student *>(studentObjectMgr->Allocate());
        PrintCounts(studentObjectMgr);
        if (printall)
            DumpPages(studentObjectMgr, wrap);
    }
    catch (const OAException &e)
    {
        if (SHOW_EXCEPTIONS)
            cout << e.what() << endl;
        else
            cout << "Exception thrown from Allocate in DoStudents." << endl;
    }
    catch (...)
    {
        cout << "Unexpected exception thrown from Allocate in DoStudents." << endl;
    }

    Student *pStudent4[6];
    for (int i = 0; i < 6; i++)
    {
        try
        {
            pStudent4[i] = static_cast<Student *>(studentObjectMgr->Allocate());
            if (pStudent4[i] == 0)
                break;
        }
        catch (const OAException &e)
        {
            if (SHOW_EXCEPTIONS)
                cout << e.what() << endl;
            else
                cout << "Exception thrown from Allocate (2) in DoStudents." << endl;

            break;
        }
        catch (...)
        {
            cout << "Unexpected exception thrown from Allocate (2) in DoStudents." << endl;
        }
    }
    PrintCounts(studentObjectMgr);
    if (printall)
        DumpPages(studentObjectMgr, wrap);

    try
    {
        studentObjectMgr->Free(pStudent1);
        PrintCounts(studentObjectMgr);
        if (printall)
            DumpPages(studentObjectMgr, wrap);
        studentObjectMgr->Free(pStudent2);
        PrintCounts(studentObjectMgr);
        if (printall)
            DumpPages(studentObjectMgr, wrap);
        studentObjectMgr->Free(pStudent3);
        PrintCounts(studentObjectMgr);
        if (printall)
            DumpPages(studentObjectMgr, wrap);
    }
    catch (const OAException &e)
    {
        if (SHOW_EXCEPTIONS)
            cout << e.what() << endl;
        else
            cout << "Exception thrown from Free in DoStudents." << endl;
    }
    catch (...)
    {
        cout << "Unexpected exception thrown from Free in DoStudents." << endl;
    }

    cout << "Most students in use: " << studentObjectMgr->GetStats().MostObjects_ << endl;
    delete studentObjectMgr;
}

void PrintCounts(const ObjectAllocator *nm)
{
    OAStats stats = nm->GetStats();
    cout << "Pages in use: " << stats.PagesInUse_;
    cout << ", Objects in use: " << stats.ObjectsInUse_;
    cout << ", Available objects: " << stats.FreeObjects_;
    cout << ", Allocs: " << stats.Allocations_;
    cout << ", Frees: " << stats.Deallocations_ << endl;
}

void PrintCounts2(const ObjectAllocator *nm)
{
    OAStats stats = nm->GetStats();
    cout << "Allocs: " << stats.Allocations_;
    cout << ", Frees: " << stats.Deallocations_ << endl;
}

void PrintConfig(const ObjectAllocator *oa)
{
    cout << "Object size = " << oa->GetStats().ObjectSize_;
    cout << ", Page size = " << oa->GetStats().PageSize_;
    cout << ", Pad bytes = " << oa->GetConfig().PadBytes_;
    cout << ", ObjectsPerPage = " << oa->GetConfig().ObjectsPerPage_;
    cout << ", MaxPages = " << oa->GetConfig().MaxPages_;
    cout << ", MaxObjects = " << oa->GetConfig().ObjectsPerPage_ * oa->GetConfig().MaxPages_;
    cout << endl;
    cout << "Alignment = " << oa->GetConfig().Alignment_;
    cout << ", LeftAlign = " << oa->GetConfig().LeftAlignSize_;
    cout << ", InterAlign = " << oa->GetConfig().InterAlignSize_;
    cout << ", HeaderBlocks = ";
    if (oa->GetConfig().HBlockInfo_.type_ == OAConfig::hbNone)
        cout << "None";
    else if (oa->GetConfig().HBlockInfo_.type_ == OAConfig::hbBasic)
        cout << "Basic";
    else if (oa->GetConfig().HBlockInfo_.type_ == OAConfig::hbExtended)
        cout << "Extended";
    else if (oa->GetConfig().HBlockInfo_.type_ == OAConfig::hbExternal)
        cout << "External";
    cout << ", Header size = " << oa->GetConfig().HBlockInfo_.size_;
    cout << endl;
}

void DumpPages(const ObjectAllocator *nm, unsigned width)
{
    const unsigned char *pages = static_cast<const unsigned char *>(nm->GetPageList());
    const unsigned char *realpage = pages;

    size_t header_size = nm->GetConfig().HBlockInfo_.size_;

    while (pages)
    {
        unsigned count = 0;

        if (SHOWREAL)
            printf("%p\n", pages);
        else
            printf("XXXXXXXX\n");

        // print column header
        for (unsigned j = 0; j < width; j++)
            printf(" %2i", j);
        printf("\n");

        // "Next page" pointer in the page
        if (SHOWREAL)
        {
            for (unsigned i = 0; i < sizeof(void *); i++, count++)
                printf(" %02X", *pages++);
        }
        else
        {
            for (unsigned j = 0; j < sizeof(void *); pages++, count++, j++)
                printf(" %s", "XX");
        }

        // Left leading alignment bytes
        if (nm->GetConfig().Alignment_ > 1)
        {
            // leading alignment block (if any)
            for (unsigned j = 0; j < nm->GetConfig().LeftAlignSize_; count++, j++)
            {
                if (count >= width)
                {
                    printf("\n");
                    count = 0;
                }
                printf(" %02X", *pages++);
            }
        }

        // Dump each object and its associated info
        for (unsigned int i = 0; i < nm->GetConfig().ObjectsPerPage_; i++)
        {
            // inter-block alignment (not on first block)
            if (i > 0)
            {
                for (unsigned j = 0; j < nm->GetConfig().InterAlignSize_; count++, j++)
                {
                    if (count >= width)
                    {
                        printf("\n");
                        count = 0;
                    }
                    printf(" %02X", *pages++);
                }
            }

            // header block bytes
            for (unsigned j = 0; j < header_size; count++, j++)
            {
                if (count >= width)
                {
                    printf("\n");
                    count = 0;
                }
                printf(" %02X", *pages++);
            }

            // left padding
            for (unsigned j = 0; j < nm->GetConfig().PadBytes_; count++, j++)
            {
                if (count >= width)
                {
                    printf("\n");
                    count = 0;
                }
                printf(" %02X", *pages++);
            }

            // possible next pointer (zero it out)
            for (unsigned j = 0; j < sizeof(void *); count++, pages++, j++)
            {
                if (count >= width)
                {
                    printf("\n");
                    count = 0;
                }
                if (SHOWREAL)
                    printf(" %02X", *pages);
                else
                    printf(" %s", "XX");
            }

            // remaining bytes
            for (unsigned j = 0; j < nm->GetStats().ObjectSize_ - sizeof(void *); count++, j++)
            {
                if (count >= width)
                {
                    printf("\n");
                    count = 0;
                }
                printf(" %02X", *pages++);
            }

            // right pad bytes
            for (unsigned j = 0; j < nm->GetConfig().PadBytes_; count++, j++)
            {
                if (count >= width)
                {
                    printf("\n");
                    count = 0;
                }
                printf(" %02X", *pages++);
            }
        }
        printf("\n\n");

        pages = reinterpret_cast<const unsigned char *>((reinterpret_cast<const GenericObject *>(realpage))->Next);
        realpage = pages;
    }
}

int main(int argc, char **argv)
{
    int test = 0;
    std::cin >> test;
    if (argc > 1)
        test = std::atoi(argv[1]);
    if (argc > 2)
        SHOWADDRESS1 = std::atoi(argv[2]);
    if (argc > 3)
        SHOWADDRESS2 = std::atoi(argv[3]);
    if (argc > 4)
        SHOWREAL = std::atoi(argv[4]);
    if (argc > 5)
        SHOW_EXCEPTIONS = std::atoi(argv[5]);

    switch (test)
    {
    case 1:
        cout << "============================== Students..." << endl;
        DoStudents(0, false);
        cout << endl;
        break;
    case 2:
        cout << "============================== Students..." << endl;
        DoStudents(0, true);
        cout << endl;
        break;

        // OAConfig config(false, 16, 4, false);
        // ObjectAllocator a(sizeof(Student), config);
        // ObjectAllocator b(sizeof(Student), config);
        //  These should fail to compile:
        // ObjectAllocator c(a);
        // a = b;

        return 0;
    }
    // #ifdef _MSC_VER
    //     _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //     _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    //     _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
    // #endif
}