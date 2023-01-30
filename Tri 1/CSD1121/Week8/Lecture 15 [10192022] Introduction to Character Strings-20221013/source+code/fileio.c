// HLP1: 05/18/2016
// fileio.c contains code from lecture illustrating a file copy function
// implemented using line I/O functions fgets and fputs ...
//
// Usage: ./a.out name-of-file-to-copy name-of-new-file

#include <stdio.h>

#define LINE_LEN 81

int main(int argc, char *argv[]) {
  // check if user has provided the proper inputs ...
  if (argc < 3) {
    printf("Usage: ./a.out name-of-file-to-copy name-of-new-file\n");
    return 0;
  }

  // check if user specified input file can be opened for read
  // and output file can be created ...
  FILE *infile  = fopen(argv[1], "r");
  FILE *outfile = fopen(argv[2], "w");
  // if either input or output file cannot be opened ...
  if (!infile || !outfile) {
    printf("Can't open input or output file\n");
    return 0;
  }

  // now that the basics have been taken care of, begin copying
  // source file to destination file, line by line
  char line[LINE_LEN]; // we assume lines have no more than LINE_LEN-1 columns ...
  while ( fgets(line, LINE_LEN, infile) != NULL ) {
    fputs(line, outfile);
  }
  // once you're done using external resources, return them back to the system
  fclose(infile);
  fclose(outfile);
  return 0;
}
