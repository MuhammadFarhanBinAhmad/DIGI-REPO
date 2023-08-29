#include "drawline.hpp"
#include <vector>
#include <string>
#include <numeric>

template<typename T>
std::vector<T> operator+(std::vector<T> const& v1,std::vector<T> const& v2)
{
    std::vector<T> result(v1.size());
    using size_type = typename std::vector<T>::size_type;
    for (size_type i{}; i < v1.size();++i)
    {
        result[i] = v1[i] + v2[i];
    }
    return result;
}
int draw_line(int x, int y)
{
    std::vector<int> v1{x,2*x},v2{y,2*y},v3{v1+v2};
    return std::accumulate(std::begin(v3),std::end(v3),0);
}