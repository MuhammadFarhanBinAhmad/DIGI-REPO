// source file: yours.c
// increment external variable x defined in file mine.c
void foo_in_your_file(void) {
  extern int x;
  ++x;
}
