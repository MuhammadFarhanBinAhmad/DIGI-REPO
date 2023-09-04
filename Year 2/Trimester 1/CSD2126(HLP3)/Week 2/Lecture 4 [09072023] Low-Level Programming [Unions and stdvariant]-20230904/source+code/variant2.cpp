#include <variant>
#include <iostream>

#include <cstdint>

class Int
{
  public:
    Int():i{}{std::cout<<__PRETTY_FUNCTION__<<'\n';}
    Int(Int const&ip):i{ip.i}{std::cout<<__PRETTY_FUNCTION__<<'\n';}
    ~Int(){std::cout<<__PRETTY_FUNCTION__<<'\n';}
  private:
    int i;
};

int main() {
  std::cout<<"Abt to new -\n";
  std::variant<Int, int, float>* pi1=new std::variant<Int, int, float>;
  std::cout<<"Abt to set int -\n";
  *pi1=1;
  std::cout<<"Abt to set Int -\n";
  *pi1=Int();
  std::cout<<"Abt to del -"<<'\n';
  delete pi1;
}