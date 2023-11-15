/*****************************************************************/ /**
  * \file	grad.cpp
  * \brief	Learning Outcomes
            Inheritance
            Run-time polymorphism
            Practice using C++ standard library
            Practice file I/O
            Practice C++ standard library std::string and std::vector classes
            Practice C++ standard library std::vector class
            Gain practice in reading and understanding code
            Intro to polymorphism, OOP, inheritance and all that good stuff
  *
  * \author	 FarhanAhmad(ID:2200544)(EMAIL:2200544@sit.SingaporeTech.edu.sg)
  *
  * \note    I somewhat did this type assigment before but it was during the holiday as practice but not as
  *          practice. Wanted to go find that sln. file but dunno where.Sad
  *          
  *
  * \date	15-NOV-2023
 ***********************************************************************/
#include "grad.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::istringstream;

int Graduate::gcount = 0; // Definition of the static member variable

Graduate::Graduate(std::string &line):Student(line)
{
    istringstream g_Data(line); // Declare my_stream here

    char type;
    g_Data >> type;

    int student_YOB{}, student_Grade{}, student_grade{};
    std::vector<int> hw{};
    std::string student_Name;

    //All fluff to get the part that i want
    //Need find better way to get to the string part i want.
    //Unless i dont call the Student(line)
    g_Data.ignore(1, ',');                   // Ignore the first comma
    std::getline(g_Data, student_Name, ','); // Read until the next comma
    g_Data >> student_YOB;                   // Read the year of birth
    g_Data.ignore();                         // Ignore the space after the comma
    g_Data >> student_Grade;                 // Read the first grade

    // Read the remaining grades into the vector hw
    while (g_Data >> student_grade)
    {
        hw.push_back(student_grade);
        //break loop after encountering the comma
        if (g_Data.peek() == ',')
        {
            break;
        }
    }

    std::string first_name ,last_name;
    g_Data.ignore(1, ',');           // Ignore the first comma
    std::getline(g_Data, gresearch, ','); // Read until the next comma
    g_Data >> first_name;
    g_Data >> last_name;
    gadvisor = first_name + ' ' + last_name;

    gcount++;
}
std::string Graduate::research() const { return gresearch; }
std::string Graduate::advisor() const { return gadvisor; }
int Graduate::count() { return gcount; }

void Graduate::print_details() const
{
    Student::print_details();
    // Print additional information specific to Undergraduate
    std::cout << "Type = Graduate Student" << '\n';
    std::cout << "Research Area =" << research() << '\n';
    std::cout << "Advisor = " << advisor() << '\n';
    std::cout << '\n';
}
double Graduate::total_score() const
{
    return 0.5 * hw_mean() + 0.5 * project_score();
}
std::string Graduate::course_grade() const
{
    return (total_score() < 80) ? "N" : "CR";
}
