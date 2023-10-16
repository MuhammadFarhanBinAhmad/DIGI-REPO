#pragma once
//SINGLETON:
//Useful when you just want one variant of something(Random number generator,Time keeper)
class Random
{
public:

    Random(const Random&) = delete;//Dont want copy constructor
    Random& operator=(const Random&) = delete;

    static Random& Get()
    {
        static Random Instance;//intiate at start. But after that will just be use as already in memory
        return Instance;
    }
    static float Float() { return Get().IFloat(); }//helper function.Still calling the get function but now less cumbersome

private:

    float IFloat() { return m_RandomGenerator; }
    Random() {}
    float m_RandomGenerator = 0.5f;//not really random. Just here for test case sake
};


//WHY NOT USE NAMESPACE??
//You can, functionality is the same. But its just that maybe got the class features available
namespace RandomClass
{
    static float s_RandomGenerator = 0.5f;
    static float Float() { return s_RandomGenerator; }
}
