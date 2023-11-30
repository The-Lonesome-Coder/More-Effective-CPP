/**
 * Distinguish between prefix and postfix forms of increment and decrement operators.
*/

/**
 * Prefix forms return a reference; postfix forms return a const object.
 *
 * Prefix form of the increment operator is sometimes called “increment and fetch,”
 * while the postfix form is often known as “fetch and increment.”
 *
 * Postfix operator makes no use of its parameter. This is typical.
 * The only purpose of the parameter is to distinguish prefix from postfix function invocation.
 * To avoid compiler warnings, a common strategy is to omit names for parameters you don’t plan to use.
*/
class Number
{
    public:
        Number& operator ++ ();                    // Prefix ++
        const Number operator ++ (int number);     // Postfix ++

        Number& operator -- ();                    // Prefix --
        const Number operator -- (int number);     // Postfix --

        Number& operator += (int number);          // += operator for Number and int
};


// Prefix - increment and fetch
Number& Number::operator ++ ()
{
    *this += 1;

    return *this;
}


// Postfix - fetch and increment
const Number Number::operator ++ (int number)
{
    const Number oldValue { *this };
    ++(*this);

    return oldValue;
}

Number num;

++num;      // Calls num.operator ++ ()
num++;      // Calls num.operator ++ (0)


