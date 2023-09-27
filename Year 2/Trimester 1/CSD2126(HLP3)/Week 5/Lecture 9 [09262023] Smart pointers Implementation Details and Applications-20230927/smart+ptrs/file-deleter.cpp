// CSD2125/CS225 10/25
// Customizing deletion callback
// std::unique_ptr<T,D> has a second template type parameter: a deletion callback type.
// This parameter defaults to std::default_delete<T> which just calls delete operator,
// but you can pass in any type you want - typically a user-defined class with an
// overloaded operator().
// Here, rather than heap memory, we use a unique_ptr to encapsulate C standard
// library FILE*. 
// We define a static function file_open to open a file and the custom deleter
// File_Closer to close the previously opened file ...

#include <cstdio>
#include <memory>

struct File_Closer {
  void operator()(FILE *fp) const { fclose(fp); printf("%s\n", __PRETTY_FUNCTION__); }

  static std::unique_ptr<FILE, File_Closer> file_open(char const *file_name, char const *mode);
};

std::unique_ptr<FILE, File_Closer> File_Closer::file_open(char const *file_name, char const *mode) {
  return std::unique_ptr<FILE, File_Closer>(fopen(file_name, mode));
}

// DO NOT close the file stream!!!
int line_count(FILE *fp) {
  int count{};
  char buffer[257];
  while ( fgets(buffer, sizeof(buffer), fp) != NULL ) {
    ++count;
  }
  return count;
}

int main() {
  std::unique_ptr<FILE, File_Closer> uf = File_Closer::file_open("file-deleter.cpp", "r");
  printf("Line count in file-deleter.cpp: %d\n", line_count(uf.get()));
  // when uf goes out of scope, its dtor will call the functor File_Closer to close the file!!!
}
