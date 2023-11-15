/*****************************************************************/ /**
  * \file	process.cpp
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
#include "process.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

// vs- All student
// vus- undergraduate
// vgs- graduates
void parse_file(std::ifstream &ifs, std::vector<Student *> &vs,
                std::vector<Student *> &vus, std::vector<Student *> &vgs)
{
  // TODO: Implement this method.
  // See function header in process.hpp for additional information

  std::string line;

  std::string str;
  while (getline(ifs, str))
  {
    char ch = str[0];
    if (ch == 'U')
    {
      Student *ps = new Undergraduate(str);
      vs.push_back(ps); // vs will be used when all students
      // are to be processed
      vus.push_back(ps); // vus will be used when only undergrads
      // are to be processed
    }
    else if (ch == 'G')
    {
      Student *ps = new Graduate(str);
      vs.push_back(ps); // vs will be used when all student are
      // to be processed
      vgs.push_back(ps); // vgs will be used when only grads are
      // to be processed
    }
  }
}

void print_records(std::vector<Student *> const &v)
{

  // TODO: Implement this method.
  // See function header in process.hpp for additional information
  for (size_t i = 0; i < v.size(); i++)
  {
    v[i]->print_details();
  }
}

void print_stats(std::vector<Student *> const &v)
{
  // TODO: Implement this method.
  // See function header in process.hpp for additional information
  std::cout << "Number of students = " << v.size() << '\n';

  std::vector<Student *> temp = v;

  double total{};

  for (size_t i = 0; i < v.size(); i++)
  {
    total += v[i]->total_score();
  }
  std::cout << "The mean of the total score = " << total / v.size() << '\n';
  std::cout << "The sorted list of students (id, name, total, grade) in descending order of total:\n";

  std::sort(temp.begin(), temp.end(), [](const Student *a, const Student *b)
            { return a->total_score() > b->total_score(); });


  for (size_t i = 0 ;i < temp.size(); i++)
  {
        std::cout<< temp[i]->id() << "," << temp[i]->name() << ", " << temp[i]->total_score() << ", " << temp[i]->course_grade() << '\n';
  }
  std::cout << '\n';
  // # of students in container.
  // compute and print mean of the total score.
  // sort and print the students based on their total score.
}

/**
 * @brief Return memory allocated by operator new ONLY using pointers contained
 * in container specified by first parameter. Why? Because containers specified
 * in the next two containers reference the same memory locations as elements of
 * first container, double deletion will cause undefined run-time behavior.
 * Next, clear contents of all 3 containers.
 *
 * @param vs Reference to vector<Student*> containing pointers to all students.
 * @param vs Reference to vector<Student*> containing pointers to undergraduates.
 * @param vs Reference to vector<Student*> containing pointers to graduates.
 */
void cleanup(std::vector<Student *> &vs, std::vector<Student *> &vus, std::vector<Student *> &vgs)
{
  // delete memory previously allocated by operator new
  for (Student *ps : vs)
  {
    delete ps;
  }
  // avoid double deletion!!!
  vs.clear();
  vus.clear();
  vgs.clear();
}
