#include <iostream>
#include <string>
#include <string_view>
/**
 * Be wary of user-defined conversion functions.
*/

/**
 * Two kinds of functions allow compilers to perform implicit type conversions:
 *
 * 1. Single-argument constructors
 * 2. Implicit type conversion operators - a member function with a strange-looking name: the word operator
 *    followed by a type specification.
*/
// 1
class Name
{
    public:
        Name(std::string_view name);    // Implicitly converts string_view to name
};

class Rational
{
    public:
        Rational(int numerator = 0, int denominator = 0);   // Implicitly converts int to Rational
};


// 2
class Rational2
{
    public:
        Rational2(int numerator = 0, int denominator = 0);
        operator double() const;   // Coverts Rational to double

    private:
        int numerator;
        int denominator;
};


/**
 * The fundamental problem of providing type conversion functions is that such functions often end up being called
 * when you neither want nor expect them to be. The result can be incorrect and unintuitive program behavior that
 * is maddeningly difficult to diagnose.
 *
 * Because there is no appropriate operator << to call, compilers would then try to find an acceptable sequence of
 * implicit type conversions they could apply to make the call succeed, in this case, operator double(). This is
 * hardly a disaster, but it demonstrates the disadvantage of implicit type conversion operators.
*/
Rational2 number { 1, 2 };
std::cout << number << '\n';   // This will implicitly convert to double


/**
 * The solution is to replace the operators with equivalent functions that don’t have the syntactically magic names.
*/
class Rational3
{
    public:
        Rational3(int numerator = 0, int denominator = 0);
        double asDouble() const;


    private:
        int numerator;
        int denominator;
};

Rational3 num { 1, 2 };
std::cout << num;   // Now it will not implicitly convert
std::cout << num.asDouble();    // Fine, print num as double


/**
 * Implicit conversions via single-argument constructors are more difficult to eliminate.
*/
// Suppose a class Array
template <class T>
class Array
{
    public:
        Array(int size);

        T& operator [] (int index);
};


/**
 * Consider a template specialization for comparing Array<int> objects and some code that uses such objects.
 *
 * If we accidentally omitted the subscripting syntax when we typed a, because compilers notice they can convert
 * the int into an Array<int> object by calling the Array<int> constructor that takes a single int as an argument,
 * they will implicitly call the constructor to convert an int to Array<int>.
*/
bool operator == (const Array<int>& lhs, const Array<int>& rhs);

Array<int> a { 10 };
Array<int> b { 10 };

for (int i = 0; i < 10; ++i)
{
    if (a == b[i])
    {
        /* ... */
    }
}


/**
 * The easy way is to declare the constructor "explicit".
*/
template <class T>
class Array2
{
    public:
        explicit Array(int size);

        T& operator [] (int index);
};