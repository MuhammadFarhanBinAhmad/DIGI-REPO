/*****************************************************************//**
 * \file	spliter.h
 * \brief	Split up binary file to smaller binary or join multiple binary file to one binary file
 *        depending on your console command prompt
 *
 * \author	FarhanAhmad(ID:2200544)(EMAIL:2200544@sit.SingaporeTech.edu.sg)
 * \date	02-SEP-2023
***********************************************************************/
#ifndef SPLITTER_H
#define SPLITTER_H

// this header file must be amended to make both splitter.cpp AND splitter.c be compatible with
// both driver.c AND driver.cpp
// in other words, there will be a single splitter.h that will be used with driver.c, driver.cpp, splitter.c, and splitter.cpp

#include <stddef.h> // size_t definition

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum {
    E_BAD_SOURCE = 1,
    E_BAD_DESTINATION,
    E_NO_MEMORY,
    E_SMALL_SIZE,
    E_NO_ACTION,
    E_SPLIT_SUCCESS,
    E_JOIN_SUCCESS
  } SplitResult;
  
  SplitResult split_join(int argc, char *argv[]);

#ifdef __cplusplus
}
#endif

#endif // end of #ifndef SPLITTER_H
