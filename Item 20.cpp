/**
 * Facilitate the return value optimization.
*/

/**
 * The article discusses the challenges and strategies associated with returning objects from functions in C++,
 * focusing on efficiency concerns. It highlights that returning objects by value, including the constructor and
 * destructor calls, is unavoidable in some functions like the operator* for rational numbers. This is because such
 * functions need to create and return a new object to operate correctly.
*/
class Rational
{
    public:
        Rational(int numerator = 0, int denominator = 1);

        int numerator() const;
        int denominator() const;
};

// For an explanation of why the return value is const, see Item 6
const Rational operator *(const Rational& lhs, const Rational& rhs);


/**
 * The article critiques alternative methods like returning pointers or references, which either lead to syntactic
 * oddities or incorrect behavior due to the return of references to destroyed objects. The author emphasizes that some
 * functions must return objects and advises against trying to eliminate by-value returns.
*/
// Another dangerous (and incorrect) way to avoid returning an object
const Rational& operator *(const Rational& lhs, const Rational& rhs)
{
    Rational result(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());

    return result;
}


/**
 * Instead, the focus should be on reducing the cost of returned objects. One efficient method is to return constructor
 * arguments directly, allowing compilers to optimize and potentially eliminate temporary objects. This technique,
 * known as the "return value optimization," is widely implemented in compilers and can significantly reduce overhead.
*/
// An efficient and correct way to implement a function that returns an object
const Rational operator *(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}


/**
 * The author concludes by emphasizing the practicality of these optimizations in real compilers, citing the prevalence
 * and effectiveness of return value optimization in C++ programming. This approach aligns with the overall goal of
 * maximizing efficiency while maintaining correct function behavior.
*/
// The most efficient way to write a function returning an object
inline const Rational operator *(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}