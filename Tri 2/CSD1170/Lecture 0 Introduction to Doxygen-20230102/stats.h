/*!*****************************************************************************
\file    stats.h
\author  Prasanna Ghali
\par     DP email: pghali\@digipen.edu
\par     Course: HLP2
\par     Section: ALL
\par     Interface file for clients using summary statistics library.
\date    11-30-2010

\brief
  This source file represents the implementation (of functions) that are
  specified in interface (header) file stats.h. In summary, these functions
  perform file I/O to read unknown number of int values and perform summary
  statistics on those values. The functions include:
  
  - count_values
      Private to this source file and part of anonymous namespace.       
      Computes number of int values in file.

  - read_values_from_file        
      Takes a file name as a string and reference to an int representing
      number of int values in file. Allocates array in free store to
      store these int values. Returns pointer to first element of array.

  - min   
      Takes a half-open range of int values and returns minimum value.

  - max 
      Takes a half-open range of int values and returns maximum value.
      
  - average       
      Takes a half-open range of int values and returns average of values.
  
  - median       
      Takes a half-open range of int values and returns median of values.
*******************************************************************************/

#ifndef STATS_H
#define STATS_H

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <string>

namespace hlp2 {
  
/*!*****************************************************************************
\brief
   Reads unknown number of int values from file.

   Allocates array in free store to store values.
   Reads values from file into free store array.

\param[in] file_name
  std::string type representing file name 

\param[out] cnt
  Reference that is assigned count of values in file

\return 
  pointer to first element of array in free store containing values read
  from file. In abnormal situation (file doesn't exist or no values found
  in file), return nullptr.
*******************************************************************************/
int* read_values_from_file(std::string file_name, int& cnt);

/*!*****************************************************************************
\brief
   Return minimum value in half-open range [start, end) of int values.

   Precondition: Requires start to point to element that precedes the element
                 pointed to by end in memory with the elements stored
                 in contiguous memory.

\param[in] start
  Pointer to initial position in sequence of values.

\param[out] end
  Pointer to one past the final position in sequence of values.

\return 
  minimum value in [start, end) range of int values.
*******************************************************************************/
int min(int const *start, int const *end);

/*!*****************************************************************************
\brief
   Return maximum value in half-open range [start, end) of int values.

   Precondition: Requires start to point to element that precedes the element
                 pointed to by end in memory with the elements stored
                 in contiguous memory.

\param[in] start
  Pointer to initial position in sequence of values.

\param[out] end
  Pointer to one past the final position in sequence of values.

\return 
  maximum value in [start, end) range of int values.
*******************************************************************************/
int max(int const *start, int const *end);

/*!*****************************************************************************
\brief
   Return average value of half-open range of [start, end) int values.

   Precondition: Requires start to point to element that precedes the element
                 pointed to by end in memory with the elements stored
                 in contiguous memory.

\param[in] start
  Pointer to initial position in sequence of values.

\param[out] end
  Pointer to one past the final position in sequence of values.

\return 
  average value in [start, end) range of int values.
*******************************************************************************/
double average(int const *start, int const *end);

/*!*****************************************************************************
\brief
   Return median value of half-open range [start, end) of int values.

   Precondition: Requires start to point to element that precedes the element
                 pointed to by end in memory with the elements stored
                 in contiguous memory.
   Precondition: Requires half-open range to be sorted!!!

\param[in] start
  Pointer to initial position in sequence of values.

\param[out] end
  Pointer to one past the final position in sequence of values.

\return 
  median value in [start, end) range of int values.
*******************************************************************************/
double median(int const *start, int const *end);

}      // end namespace hlp2

#endif // #ifndef STATS_H
