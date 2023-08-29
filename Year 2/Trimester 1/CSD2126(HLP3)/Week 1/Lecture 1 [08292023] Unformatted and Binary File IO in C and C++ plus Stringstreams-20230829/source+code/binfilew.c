// HLP3 05/14
// binfilew.c - write a binary file (C version)
//
// gcc doesn't like line 25 even though the logic in this program is correct.
// To avoid compiler errors, use the following to compile/link:
// gcc -std=c11 -pedantic-errors -Wall -Wextra -Werror
//    -Wno-stringop-truncation binfilew.c -o binfilew.out

#include <stdio.h>
#include <string.h>
#include "file-struct.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s binary-file-to-create\n", argv[0]);
    return 1;
  }

  FILE *out = fopen(argv[1],"wb");

  char magic_number[2];
  strncpy(magic_number, MAGIC_NUMBER, 2);
  fwrite(magic_number, 2, 1, out);

  FileStruct fs = {42, 231.5f, "Fred Flintstone"};
  fwrite(&fs,sizeof(fs),1,out);

  fs.age = 2;
  fs.weight = 41.7f;
  strcpy(fs.name,"Pebbles Flintstone");
  fwrite(&fs,sizeof(fs),1,out);

  fs.age = 5;
  fs.weight = 310.2f;
  strcpy(fs.name,"Dino");
  fwrite(&fs,sizeof(fs),1,out);

  fclose(out);
  return 0;
}
