// HLP3 05/14
// binfiler.c -- read a binary file (C version)

#include <stdio.h>
#include <string.h>
#include "file-struct.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s binary-file-to-read\n", argv[0]);
    return 1;
  }

  FILE *in = fopen(argv[1],"rb");
  if (in == NULL) {
    fprintf(stderr,"file not found\n");
    return 1;
  }

  char magic_number[2];
  fread(&magic_number, 2, 1, in);
  if (strncmp(magic_number, MAGIC_NUMBER, 2) != 0) {
    fprintf(stderr, "bad file\n");
    return 1;
  }

  fseek(in, 0, SEEK_END);
  long size = ftell(in);
  fseek(in, 2, SEEK_SET);
  if ((size-2)%sizeof(FileStruct) != 0) {
    fprintf(stderr,"bad or incomplete file\n");
    return 1;
  }

  while (!feof(in) && !ferror(in)) {
    FileStruct fs;
    int count = fread(&fs,sizeof(fs),1,in);
    if (count == 1)
      fprintf(stdout,"Name: %s\n  Age: %d\n  Weight: %.1f\n",
                     fs.name,fs.age,fs.weight);
  }

  fclose(in);
  return 0;
}
