void min_val(int const *parr, int size) {
  /*
  this declaration announces the name minval and the type int
  to the compiler and further says that this variable is
  defined somewhere else (could be in this source file or some
  other source file - that is for the linker to figure out)
  */
  extern int minval;

  minval = parr[0];
  for (int i = 1; i < size; ++i) {
    minval = (parr[i] < minval) ? parr[i] : minval;
  }
  // nothing to return ...
}
