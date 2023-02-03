#include <cstddef>


class Str
{
    public :
    using value_type = char;
    using reference = value_type&;
    using const_reference = const reference;
    using pointer = value_type*;
    using const_pointer = const pointer;
    using iterator = pointer;
    using const_iterator = const_pointer;

    public:
    Str();//Default constructor
    Str(char const*);//single argument constructor
    Str(Str const&);//copy constructor
    ~Str();

    //COPY ASSIGNMENT OPERATOR
    Str& operator=(Str const&);
    Str& operator=(Str const*);

Str& operator

    //SUBSCRIPT OPERATOR
    //Both are the same. Just that one is const and the other is not
    //Just need to maintain one guy :const char& operator[](size_t index)
    const char& operator[](size_t index) const{return ptr[index]}//Str const lisa{"lisa"}; char ch = lisa[2];
    char& operator[](size_t index) {//return ptr[index]
    
    return cosnst_cast<char&>(static_cast<Str const&>(*this)[index]);//you want to convert the original. not make a copy
    };//Str  lisa{"lisa"}; lisa[0] = 'L';

    void swap(Str&);


    char const* c_str() const;
    bool empty() const{return len==0;}
    size_t size() const {return len;}

    iterator       begin(){return ptr;}
    const_iterator begin() const {return ptr;};
    iterator       end(){return ptr + len;}
    const_iterator end() const {return ptr + len;};
    private:
    size_t len;
    char *ptr;
};