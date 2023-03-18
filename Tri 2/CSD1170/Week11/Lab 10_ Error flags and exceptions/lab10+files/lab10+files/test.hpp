/******************************************************************************/
/*!
\file   array.tpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS1170
\par    Section A
\par    Lab 10: Error flag and exceptions
\date   18/03/2022
\brief
   3 classes:
   invalid input - returns text stating that the input is invalid
   stream_wrapper - read input and decide whether to throw exception or not
   division_by_zero - return an exception is the value is divided by zero

   *Note: Need ask is there any other use case for try catch and throw. Cause it seems like(for programmer), debugging but with extra step
   Cause this project have us play the role of cilent.
   Also should play around with std::exception i guess
*/
#include <iostream>
#include <sstream>
namespace hlp2
{

    //return invalid input if input is invalid(bruh)
    class invalid_input : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Invalid input!";
        }
    };

    class stream_wrapper
    {
    public:
        stream_wrapper(std::istream &is) : input_(is) {}//intilize input

        template<typename T>
        stream_wrapper &operator>>(T &value)
        {
            //throw invalid input if input is invalid(bruh)
            if (!(input_ >> value))
            {
                throw invalid_input();
            }

            return *this;
        }

    private:
    std::istream &input_;

    };

    class division_by_zero : public std::exception
    {
    public:
        division_by_zero(int number)
        {
            std::stringstream string_Stream;

            string_Stream << "Division by zero: " << number << " / 0!" << std::endl;

            my_StringStream = string_Stream.str();
        }
        // need find what noexcept override means. TA explain still dont understand:(
        const char *what() const noexcept override
        {
            return my_StringStream.c_str();
        }

    private:
        std::string my_StringStream;
    };

    template <typename T>
    void test1(int numerator, int denominator, T func)
    {

        int val{};
        if (func(numerator, denominator, val))
        {
            std::cout << "Calling function #1; result: " << val << '.' << std::endl;
        }
        else
        {
            std::stringstream string_Stream;

            string_Stream << "Division by zero: " << numerator << " / " << denominator;
            std::cout << "Calling function #1." << std::endl;

            throw division_by_zero(numerator);
        }
    }
    template <typename T>
    void test2(int numerator, int denominator, T value)
    {
        std::pair<bool, int> result = value(numerator, denominator);

        if (result.first)
        {
            std::cout << "Calling function #2; result: " << result.second << '.' << std::endl;
        }
        else
        {
            std::stringstream string_Stream;

            string_Stream << "Division by zero: " << numerator << " / " << denominator;
            std::cout << "Calling function #2." << std::endl;

            throw division_by_zero(numerator);
        }
    }
    template <typename T>
    void test3(int numerator, int denominator, T value)
    {
        //errno is a preprocessor macro used for error indication
        errno = 0;
        int val = value(numerator, denominator);

        if (errno)
        {
            std::cout << "Calling function #3; result: " << val << '.' << std::endl;
        }
        else
        {
            std::stringstream string_Stream;

            string_Stream << "Division by zero: " << numerator << " / " << denominator;
            std::cout << "Calling function #3." << std::endl;

            throw division_by_zero(numerator);
        }
    }
    template <typename T>
    void test4(int numerator, int denominator, T value)
    {
        int val = value(numerator, denominator);

        if (val != std::numeric_limits<int>::min())
        {
            std::cout << "Calling function #4; result: " << val << '.' << std::endl;
        }
        else
        {
            std::stringstream string_Stream;

            string_Stream << "Division by zero: " << numerator << " / " << denominator;
            std::cout << "Calling function #4." << std::endl;

            throw division_by_zero(numerator);
        }
    }
    template <typename T>
    void test5(int numerator, int denominator, T value)
    {
        //try to run code
        try // your best :)
        {
            int val = value(numerator, denominator);
            std::cout << "Calling function #5; result: " << val << '.' << std::endl;
        }
        //if the value divided is with 0, catch it
        catch (const division_by_zero &div)
        {
            std::cout << "Calling function #5." << std::endl;
            throw; // away
        }
    }
} // namespace hlp2