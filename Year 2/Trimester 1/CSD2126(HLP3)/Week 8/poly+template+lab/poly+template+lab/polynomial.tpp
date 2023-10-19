// Provide file documentation header
// Don't include any library headers!!!

namespace HLP3 
{
// Define member functions of class template Polynomial ...
template<typename CoefficientType, int Degree>
Polynomial<CoefficientType, Degree>::Polynomial()
{
    for (int i = 0; i <= Degree; ++i) 
    {
        coefficients[i] = CoefficientType();
    }
}

template<typename CoefficientType, int Degree>
Polynomial<CoefficientType, Degree>::Polynomial(const Polynomial& rhs)
{
    for (int i = 0; i <= Degree; ++i) 
    {
        coefficients[i] = rhs[i];
    }
}


// Define non-modifiable operator[] for reading coefficient values
template<typename CoefficientType, int Degree>
CoefficientType Polynomial<CoefficientType, Degree>::operator[](int index) const
{
    if (index < 0 || index > Degree) 
    {
        return CoefficientType();
    }
    return coefficients[index];
}

// Define modifiable operator[] for writing coefficient values
template<typename CoefficientType, int Degree>
CoefficientType& Polynomial<CoefficientType, Degree>::operator[](int index)
{
    if (index < 0 || index > Degree) 
    {
        throw std::out_of_range("Index out of range");
    }
    return coefficients[index];
}

template<typename CoefficientType, int Degree>
Polynomial<CoefficientType,Degree> Polynomial<CoefficientType,Degree>::operator*(const Polynomial<CoefficientType,Degree>& rhs) const
{
    Polynomial<CoefficientType, Degree> temp;

    for (int i = 0; i <= Degree; ++i)
    {
        for (int j = 0; j <= Degree; ++j)
        {
            if (i + j <= Degree)
            {
                temp[i + j] += coefficients[i] * rhs[j];
            }
        }
    }
    return temp;
}

//This is something new
//Something to do with the Degree
// template<typename CoefficientType, int Degree>
// template<typename OtherType>
// Polynomial<OtherType, Degree> Polynomial<CoefficientType, Degree>::operator*(const Polynomial<CoefficientType, Degree>& rhs) const
// {
//   Polynomial<OtherType,Degree> temp;

//   for (int i =0; i<= Degree;i++)
//   {
//     for (int j = 0; j <= Degree;j++)
//     {
//       if (i+j <= Degree)
//       {
//         temp[i+j] += static_cast<OtherType>(coefficients[i]) * rhs[j];
//       }
//     }
//   }
//   return temp;
// }



template<typename CoefficientType, int Degree>
Polynomial<CoefficientType,Degree>& Polynomial<CoefficientType,Degree>::operator=(const Polynomial<CoefficientType,Degree>& rhs) 
{
    Polynomial<CoefficientType, Degree> temp;

    for (int i = 0; i <= Degree; ++i)
    {
        for (int j = 0; j <= Degree; ++j)
        {
          coefficients[i][j] = rhs[i][j];
        }
        coefficients[i] = rhs[i];
    }
    return *this;
}

template<typename CoefficientType, int Degree>
CoefficientType Polynomial<CoefficientType, Degree>::operator()(CoefficientType rhs) const
{
  CoefficientType temp = 0;

  for (int i=0;i <= Degree;i++)
  {
    temp += coefficients[i] * std::pow(x,i);
  }

  return temp;
}


//I wasted 10 min thinking i need to make and friend this :(.
// DON'T CHANGE/EDIT THE FOLLOWING DEFINITION:
template< typename T, int N > 
std::ostream& operator<<(std::ostream &out, Polynomial<T, N> const& pol) {
  out << pol[0] << " ";
  for ( int i=1; i<=N; ++i ) {
    if ( pol[i] != 0 ) { // skip terms with zero coefficients
      if      ( pol[i] > 0 ) {  out << "+"; }
      if      ( pol[i] == 1 )  { }
      else if ( pol[i] == -1 ) { out << "-"; }
      else                     { out << pol[i] << "*"; }
      out << "x^" << i << " ";
    }
  }
  return out;
}

} // end namespace HLP3
