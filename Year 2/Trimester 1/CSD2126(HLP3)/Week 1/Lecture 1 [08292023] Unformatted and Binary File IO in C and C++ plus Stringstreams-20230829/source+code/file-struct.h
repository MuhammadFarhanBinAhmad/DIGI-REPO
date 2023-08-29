// HLP3: 05/17/2022
// file-struct.h
// -- structure used by 'binfiler.c', 'binfilew.c', 'binfiler.cpp', and 'binfilew.cpp'

#ifndef CS225_FILE_STRUCT
#define CS225_FILE_STRUCT

#define MAGIC_NUMBER "FS"

struct FileStruct_Tag {
  int age;
  float weight;
  char name[24];
};

typedef struct FileStruct_Tag FileStruct;

#endif
