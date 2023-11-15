/*****************************************************************/ /**
  * \file	student.cpp
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
 ***********************************************************************/#include "student.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::istringstream;

int Student::scount = 0;

double Student::hw_mean() const
{
    double total{};
    for (size_t i =0; i < shw.size();i++)
    {
        total += shw[i];
    }

    return total / shw.size();
}

Student::Student(std::string &line)
{
    scount++;
    sid = scount;

    istringstream s_Data(line); // Declare my_stream here

    char type;
    s_Data >> type;

    int student_Assigment{};

    //All fluff to get the part that i want
    //Need find better way to get to the string part i want.
    //Unless i dont call the Student(line)
    //From future self: You need to call Student(line) for scount
    s_Data.ignore(1, ',');                   // Ignore the first comma
    std::getline(s_Data, sname, ','); // Read until the next comma
    s_Data >> syob;                   // Read the year of birth
    s_Data.ignore();                         // Ignore the space after the comma
    s_Data >> sproj;                 // Read the first grade

    // Read the remaining grades into the vector hw
    while (s_Data >> student_Assigment)
    {
        shw.push_back(student_Assigment);
        //break loop after encountering the comma
        if (s_Data.peek() == ',')
        {
            s_Data.ignore(0, ','); 
            break;
        }
    }
}

int Student::id() const{return sid;}
std::string Student::name() const{ return sname;}
int Student::yob() const{return syob;}
double Student::project_score() const{return sproj;}
int Student::count(){return scount;}

void Student::print_details() const
{
    std::cout << "Id = " << id() << '\n';
    std::cout << "Name =" << name() << '\n';
    std::cout << "Age = " << age() << '\n';
    std::cout << "Project = " << project_score() << '\n';
    std::cout << "Assignment = [";
    for (size_t i =0 ;i < shw.size() - 1; i++)
    {
        std::cout << shw[i] << ", ";
    }
    std::cout << shw[shw.size() - 1];
    std::cout << "]" << '\n';
    std::cout << "Total = " << total_score() << '\n';
    std::cout << "Grade = " << course_grade() << '\n';
}