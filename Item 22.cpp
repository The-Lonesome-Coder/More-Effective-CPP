/**
 * Consider using op= instead of stand-alone op.
*/

/**
 * Implementation of Operators:
 * In C++, operators such as operator +, operator =, and operator += are distinct and have no inherent relationship. If
 * a programmer wants these operators to work together as expected, they must implement this functionality themselves.
 * For instance, implementing operator+ in terms of operator += ensures a natural relationship and reduces maintenance
 * by centralizing the logic in the assignment operator.
*/
class Rational
{
    public:
        Rational& operator +=(const Rational& rhs);
        Rational& operator -=(const Rational& rhs);
};

// Operator + implemented in terms of operator+=; see Item 6 for an explanation of why the return value is const and
// page 109 for a warning about implementation
const Rational operator + (const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs) += rhs;
}

// Operator - implemented in terms of operator -=
const Rational operator - (const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs) -= rhs;
}

/**
 * Overloading Techniques:
 * The article suggests using templates to generalize the implementation of stand-alone operators at a global scope.
 * This way, as long as an assignment version of an operator is defined for a type T, the corresponding stand-alone
 * operator is automatically available.
*/
template<class T>
const T operator + (const T& lhs, const T& rhs)
{
    return T(lhs) += rhs;
}

template<class T>
const T operator - (const T& lhs, const T& rhs)
{
return T(lhs) -= rhs;
}


/**
 * Efficiency Considerations:
 * The assignment versions of operators are typically more efficient than their stand-alone versions, as they don’t
 * require the construction and destruction of temporary objects. By offering both types of operators, class users can
 * choose between writing concise code using stand-alone operators or more efficient, though possibly less intuitive,
 * code using assignment operators.
 *
 *
 * Return Value Optimization (RVO):
 * The article discusses the implementation details of operator overloading with a focus on efficiency, particularly
 * concerning RVO. The use of named versus unnamed objects in the return statements of operator functions affects the
 * compiler's ability to apply RVO. Historically, unnamed objects have been easier for compilers to optimize away,
 * potentially making them more efficient than named objects, although this may vary with different compilers and their
 * capabilities.
 *
 *
 * Library Design and Application Development:
 * For library designers, the recommendation is to provide both assignment and stand-alone versions of operators to
 * offer flexibility and efficiency to users. Application developers are advised to prefer assignment operators over
 * stand-alone ones for performance-critical code.
*/