#include <vector>
#include <stack>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <fstream>
#define NUM_HOSPITAL 2
#define HOSPITAL_SLOTS 2
#define NUM_STUDENTS 5
//#define DEBUG

struct student
{   //students can only ever be assigned one hospital
    int m_Assigned{-1};       //index of hospital assigned 
    std::vector<int> preference; //preference of hospital.
    bool CheckPreference(int index);
};

struct hospital
{   //hospitals can be assigned multiple graduates
    int numAssigned{};              //current number of people assigned to hospital
    size_t preferencePtr{0};        //current index of preferenced
    std::vector<int> preference;    //preference list
    std::vector<int> assignees;     //index of student assigned to this hospital
};

struct site
{
    int SiteNumber;
    int numAssigned{};              //current number of people assigned to the Site
    size_t preferencePtr{0};        //current index of preferenced
    std::vector<int> preference;    // to be sorted 
    std::vector<int> assignees;     //index of student assigned to this hospital
};

struct staff
{
    int requiredPay;
    int m_Assigned{-1};       //index of hospital assigned 
    std::vector<int> distanceFromSite;
    std::vector<int> preferences;    
    bool CheckPreference(int index);
};

// Comparator to sort based on distance
bool compareByDistance(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.second < b.second; // Sort ascending by distance
}

void SortEmployeePreferences(std::ifstream& stafffile, std::vector<staff>& staffs) {
    std::string line;
    int staffIndex = 0;
    
    while (std::getline(stafffile, line)) {
        std::istringstream iss(line);
        staff s;
        
        // Read required pay first
        iss >> s.requiredPay;

        // Read distances from sites (assuming 4 sites)
        for (int i = 0; i < 4; ++i) {
            int distance;
            iss >> distance;
            s.distanceFromSite.push_back(distance);
        }

        // Create a vector of pairs to store (siteIndex, distance)
        std::vector<std::pair<int, int>> siteDistancePairs;
        for (int i = 0; i < 4; ++i) {
            siteDistancePairs.push_back({i, s.distanceFromSite[i]});
        }

        // Sort the pairs by distance (smallest distance first)
        std::sort(siteDistancePairs.begin(), siteDistancePairs.end(), compareByDistance);

        // Store preferences (site indices) based on sorted distances
        for (auto& pair : siteDistancePairs) {
            s.preferences.push_back(pair.first); // Add site index
        }

        staffs.push_back(s);
        ++staffIndex;
    }
}

void SortSitePreferences(std::vector<site>& Sites, std::vector<staff> staffs, int NumberOfSite = 4) {
   for (int i = 0; i < NumberOfSite; ++i) {
        site s;
        s.SiteNumber = i + 1; // Set the site number

        // Create a vector of pairs to hold (staffIndex, pay)
        std::vector<std::pair<int, int>> staffPayPairs;
        for (int j = 0; j < staffs.size(); ++j) {
            staffPayPairs.push_back({j, staffs[j].requiredPay}); // (staff index, required pay)
        }

        // Sort staff based on required pay (lowest pay = highest preference)
        std::sort(staffPayPairs.begin(), staffPayPairs.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second; // Sort by pay ascending
        });

        // Assign sorted staff indices to the site's preference list
        for (auto& pair : staffPayPairs) {
            s.preference.push_back(pair.first); 
        }

        Sites.push_back(s);
    }
}

void PrintPreferences(const std::vector<staff>& staffs, const std::vector<site>& Sites) {
    std::cout << "=================== Staff Preferences ===================\n";
    for (int i = 0; i < staffs.size(); ++i) {
        std::cout << "Staff #" << i + 1 << " (Required Pay: " << staffs[i].requiredPay << "):\n";
        std::cout << "Preference order of sites based on distance: ";
        for (int j = 0; j < staffs[i].preferences.size(); ++j) {
            std::cout << "Site " << staffs[i].preferences[j] + 1;
            if (j < staffs[i].preferences.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n=================== Site Preferences ====================\n";
    for (int i = 0; i < Sites.size(); ++i) {
        std::cout << "Site #" << Sites[i].SiteNumber << ":\n";
        std::cout << "Preference order of staff based on pay: ";
        for (int j = 0; j < Sites[i].preference.size(); ++j) {
            std::cout << "Staff " << Sites[i].preference[j] + 1;
            if (j < Sites[i].preference.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << "\n";
    }
	std::cout << std::endl;
}


/*!***********************************************************************
  \brief
    compare the parameter index to the current assigned hospital of the 
    student based on the student's preference
  \param[ in ] index
    index of new hospital to be compared to current assigned hospital 
    according to student's preference
  \return
    if the new index is more prefered than the current assinged hospital
*************************************************************************/
bool staff::CheckPreference(int index)
{   //is index earlier than current assigned
    if (m_Assigned < 0){return true;}   //first assingment
    for(int t: preferences)
    {
        if(t == index)
            return true;    //index is more prefered than currently assigned
        if(t == m_Assigned)
            return false;   //index is less prefered than currently assigned
    }
    return true;            //default to true
}


/*!***********************************************************************
  \brief
    compare the parameter index to the current assigned hospital of the 
    student based on the student's preference
  \param[ in ] index
    index of new hospital to be compared to current assigned hospital 
    according to student's preference
  \return
    if the new index is more prefered than the current assinged hospital
*************************************************************************/
bool student::CheckPreference(int index)
{   //is index earlier than current assigned
    if (m_Assigned < 0){return true;}   //first assingment
    for(int t: preference)
    {
        if(t == index)
            return true;    //index is more prefered than currently assigned
        if(t == m_Assigned)
            return false;   //index is less prefered than currently assigned
    }
    return true;            //default to true
}


// //functions for matching
// void CleanAssignee(std::vector<student>const& graduates, hospital& hos, int index);

template <typename W, typename M>
void CleanAssignee(std::vector<W>const& graduates, M& hos, int index);

template <typename W, typename M>
bool Engagement(std::vector<W>& graduates,
 std::vector<M>& hos,
 int index, std::vector<int>&hStack, int slots);

// bool Engagement(std::vector<student>& graduates,
//  std::vector<hospital>& hos,
//  int index, std::vector<int>&hStack, int slots);

//template <int NSlots>   //NSlots = number of slots to fill per hospital
//void stableMatch(std::vector<student>& graduates, std::vector<hospital>& hospitals);

template <int NSlots, typename W, typename M> 
void stableMatch(std::vector<W>& staffList, std::vector<M>& siteList);

int main(int argc, char* argv[] )
{
	if (argc < 4)
		return 0;
	
	std::vector<student> students;
    std::vector<hospital> hos;
	
	std::string inputpath = argv[1];
	std::ifstream studentprefs(inputpath);
	
	int numberofstudents = std::count(std::istreambuf_iterator<char>(studentprefs), std::istreambuf_iterator<char>(), '\n');
	studentprefs.seekg(std::ifstream::beg);
	
	students.resize(numberofstudents+1);
	
	std::string line;
	int i = 0;
	while(std::getline(studentprefs,line))
	{
		std::istringstream stream(line);
		std::string word;
		while(stream >> word)
		{
			students[i].preference.push_back(std::stoi(word));			
		}	
		i++;	
	}
	studentprefs.close();
	
if(std::stoi(argv[4]) != 1)	
{	    std::cout << "\n=================== Student Preferences ====================\n";
	for(student t:students)
    {   
		bool first = false;
        for(int j : t.preference)
        {   
            std::cout<<((j)? "M":"C");
			if(!first)
			std::cout<< " > ";
		first = true;
        }
         std::cout<<"\n";
    }		
}	
	inputpath = argv[2];
	std::ifstream hosPrefs(inputpath);
	
	int numHos = std::count(std::istreambuf_iterator<char>(hosPrefs), std::istreambuf_iterator<char>(), '\n');
	hosPrefs.seekg(std::ifstream::beg);
	
	hos.resize(numHos+1);
	i = 0;
	
	while(std::getline(hosPrefs,line))
	{
		std::istringstream stream(line);
		std::string word;
		while(stream >> word)
		{
			hos[i].preference.push_back(std::stoi(word)-1);			
		}	
		i++;	
	}
	hosPrefs.close();
	
if(std::stoi(argv[4]) != 1)	
{ std::cout << "=================== Hospital Preferences ====================\n";
	std::stringstream line;
    for (int i:hos[0].preference)
	{
        line <<i+1 << " > ";
	}
	line.seekp(line.str().length()-2);
	line << " ";
    std::cout<< line.str() <<"\n";
	
	line = std::stringstream();
    for (int i:hos[1].preference)
        line<<i+1 << " > ";
	line.seekp(line.str().length()-2);
	line << " ";	
    std::cout<< line.str() <<"\n";
}
////////////////////////////////////////

	inputpath = argv[3];
	std::ifstream stafflist(inputpath);	
	
	std::vector<staff> staffs;
	std::vector<site> Sites;
	
	//Sites.resize(4);
	
	SortEmployeePreferences(stafflist, staffs);
	SortSitePreferences(Sites, staffs);
	
if(std::stoi(argv[4]) != 0)	
	PrintPreferences(staffs, Sites);


/////////////////////////////////////
if(std::stoi(argv[4]) != 1)	
{
    stableMatch<2>(students,hos);
std::cout << "\n=================== Student Assignment ====================\n";
    i = 0;
    for(student const& t:students)
    {
        std::cout<<"student ["<<i+1<<"] is assigned hospital ["
        << ((t.m_Assigned < 0)?"none":((t.m_Assigned)?"M":"C")) 
        << "] \n";
        ++i;
    }
    i=0;
	std::cout << "\n=================== Hospital Assignments ====================\n";
    for(hospital const& t:hos)
    {
        std::cout<<"hospital ["<<((i)?"M":"C")<<"] is assigned students["; 
		bool first = true;
        for(int j:t.assignees)
        {
            std::cout<<" "<<j+1 << " ";
			if(first)
				std::cout<<",";
			first = false;
        }
        std::cout<< "] \n";
        ++i;
    }
}
    
	
	
	
    stableMatch<2>(staffs,Sites);
if(std::stoi(argv[4]) != 0)	
{
	std::cout << "=================== Staff Assignments ===================\n";
	
    i = 0;
    for(auto const& t:staffs)
    {
        std::cout<<"staff ["<<i+1<<"] is assigned site ["
        << t.m_Assigned +1
        << "] \n";
        ++i;
    }
    i=0;
	std::cout<<std::endl;
		std::cout << "=================== Site Assignments ===================\n";
    for(auto const& t:Sites)
    {
        std::cout<<"site ["<<i+1<<"] is assigned staff [";
		bool first = true;
        for(int j:t.assignees)
        {
            std::cout<<" "<<j+1 << " ";
			if(first)
				std::cout<<",";
			first = false;
        }
        std::cout<< "] \n";
        ++i;
    }
}
}


/*!***********************************************************************
  \brief
    perform a stable sort given some graduates and some hospitals
  \param[ in/out ] graduates
    students to be assigned to hospitals
  \param[ in/out ] hospitals
    hospitals to be assigned students
  \param[ in ] NSlots
    number of slots per hospital to be filled
*************************************************************************/
template <int NSlots>   //NSlots = number of slots to fill per hospital
void stableMatch(std::vector<student>& graduates, std::vector<hospital>& hospitals)
{
    
    if(hospitals.size()*NSlots > graduates.size())
    {//stable matching impossible, not enough students
        return;
    }  

    //fill hStack with hospital indexes, to be used for iterating
    std::vector<int> hStack(hospitals.size());
    std::iota(hStack.begin(), hStack.end(), 0); 

    //while stack to clear is not empty, and the number of assigned graduates are 
    //less than required. 
    while(!hStack.empty() && hospitals[hStack[0]].numAssigned < NSlots)
    {
        hospital& current {hospitals[hStack[0]]};       //quick access
        CleanAssignee(graduates,current,hStack[0]);       //remove assignees who have jump ship
        Engagement(graduates,hospitals,hStack[0],hStack, hospitals.size());   //attempt to engage new grads
        hStack.erase(hStack.begin());           //remove first index from the stack
    }
    //by this point, all hospitals should be full.
}

/*!***********************************************************************
  \brief
    perform a stable sort given some graduates and some hospitals
  \param[ in/out ] graduates
    students to be assigned to hospitals
  \param[ in/out ] hospitals
    hospitals to be assigned students
  \param[ in ] NSlots
    number of slots per hospital to be filled
*************************************************************************/
template <int NSlots, typename W, typename M> 
void stableMatch(std::vector<W>& staffList, std::vector<M>& siteList)
{
        
    if(siteList.size()*NSlots > staffList.size())
    {//stable matching impossible, not enough students
        return;
    }  

    //fill hStack with hospital indexes, to be used for iterating
    std::vector<int> hStack(siteList.size());
    std::iota(hStack.begin(), hStack.end(), 0); 

    //while stack to clear is not empty, and the number of assigned graduates are 
    //less than required. 
    while(!hStack.empty())
    {
        if(siteList[hStack[0]].numAssigned < NSlots){
            M& current {siteList[hStack[0]]};       //quick access
            CleanAssignee(staffList,current,hStack[0]);       //remove assignees who have jump ship
            Engagement(staffList,siteList,hStack[0],hStack, NSlots);   //attempt to engage new grads
        }
        hStack.erase(hStack.begin());           //remove first index from the stack
    }  
}

/*!***********************************************************************
  \brief
    remove assigned students who have jumped ship to another hospital
  \param[ in ] graduates
    students to be assigned to hospitals
  \param[ in/out ] hos
    hospitals to be updated
  \param[ in ] index
    the index of the hospital amongst the other hospital(vector index position)
*************************************************************************/
template <typename W, typename M>
void CleanAssignee(std::vector<W>const& graduates, M& hos, int index)
{
    if(!hos.assignees.size()){return;}  //if not yet assigned, return
    //if already assigned but some jump ship, id those who jump ship and remove
    for(size_t i{0};i != hos.assignees.size();++i)
    {
        if(graduates[hos.assignees[i]].m_Assigned != index)
        {
            hos.assignees.erase(hos.assignees.begin() + i); //remove index i
            --i;    //check new i element next loop
        }
    }
}

/*!***********************************************************************
  \brief
    remove assigned students who have jumped ship to another hospital
  \param[ in/out ] graduates
    students to be assigned to hospitals
  \param[ in/out ] hospitals
    hospitals to be assigned students
  \param[ in ] index
    the index of the hospital amongst the other hospital(vector index position)
  \param[ out ] hStack
    stack representing hospitals yet to complete engagement
  \param[ in ] slots
    number of openings per hospitals
  \return
    if the hospital has finished it's preference list without filling its slots
*************************************************************************/
template <typename W, typename M>
bool Engagement(std::vector<W>& graduates,
 std::vector<M>& hos,
 int index, std::vector<int>&hStack, int slots)
{
    M& current{hos[index]};
    while (current.numAssigned < slots)
    {
        if(current.preference.size() == current.preferencePtr)
        {   //failed to match, no stable matching possible
            return false;
        }
        //check preference of current grad, try to recruit
        if(graduates[current.preference[current.preferencePtr]].CheckPreference(index))
        {   
            int oldAssignment {graduates[current.preference[current.preferencePtr]].m_Assigned};
            if(!(oldAssignment < 0))
            {   //if old assignment is a hospital.          
                //reduce number of assigned people to old hospital
                --hos[oldAssignment].numAssigned;
                //add hospital of the old assignment to the hospital yet to be filled stack
                hStack.push_back(oldAssignment);
            }
            //update assignment for the graduate
            graduates[current.preference[current.preferencePtr]].m_Assigned = index;
            //update stats for the hospital
            ++current.numAssigned;
            current.assignees.push_back(current.preference[current.preferencePtr]); //add assignee
        }

        ++current.preferencePtr;    //iterate hospital's preference to next graduate
    }
    return true;    //successful matching for hospital.
}

