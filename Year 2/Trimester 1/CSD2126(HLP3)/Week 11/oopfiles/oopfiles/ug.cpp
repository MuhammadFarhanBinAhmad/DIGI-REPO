/*****************************************************************/ /**
  * \file	ug.cpp
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
#include "ug.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::istringstream;

int Undergraduate::ucount = 0; // Definition of the static member variable

Undergraduate::Undergraduate(std::string &line) : Student(line)
{
    istringstream ug_Data(line); // Declare my_stream here

    char type;
    ug_Data >> type;

    int student_YOB{}, student_Grade{}, student_grade{};
    std::vector<int> hw{};
    std::string student_Name;

    //All fluff to get the part that i want
    //Need find better way to get to the string part i want.
    //Unless i dont call the Student(line)
    ug_Data.ignore(1, ',');                   // Ignore the first comma
    std::getline(ug_Data, student_Name, ','); // Read until the next comma
    ug_Data >> student_YOB;                   // Read the year of birth
    ug_Data.ignore();                         // Ignore the space after the comma
    ug_Data >> student_Grade;                 // Read the first grade

    // Read the remaining grades into the vector hw
    while (ug_Data >> student_grade)
    {
        hw.push_back(student_grade);
        //break loop after encountering the comma
        if (ug_Data.peek() == ',')
        {
            break;
        }
    }

    //Additional info for type of student
    ug_Data.ignore(1, ',');           // Ignore the first comma
    std::getline(ug_Data, udorm, ','); // Read until the next comma
    ug_Data >> uyear;

    ucount++;
}

std::string Undergraduate::dormitory() const{return udorm;}
std::string Undergraduate::year() const{return uyear;}
int Undergraduate::count(){return ucount;}

void Undergraduate::print_details() const
{
    Student::print_details();
    // Print additional information specific to Undergraduate
    std::cout << "Type = Undergraduate Student" << '\n';
    std::cout << "Residence Hall =" << dormitory() << '\n';
    std::cout << "Year in College = " << year() << '\n';
    std::cout << '\n';
}
double Undergraduate::total_score() const
{
    return 0.7 * hw_mean() + 0.3 * project_score();
}
std::string Undergraduate::course_grade() const
{
    return (total_score() < 70) ? "N" : "CR";
}
