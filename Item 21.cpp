/**
 * Overload to avoid implicit type conversion.
*/

/**
 * The article discusses the use of function overloading in C++ to avoid the costs associated with implicit type
 * conversions. It starts with an example of a class UPInt (unlimited precision integers) and an operator + function.
 * The article points out that adding two UPInt objects is straightforward, but when adding a UPInt object with an int
 * (e.g., upi1 + 10), a temporary UPInt object is created for the conversion, which incurs a computational cost.
*/
// Class for unlimited precision integers
class UPInt
{
    public:
        UPInt();
        UPInt(int value);
};

// For an explanation of why the return value is const, see Item 6
const UPInt operator + (const UPInt& lhs, const UPInt& rhs);

UPInt upi1, upi2;
UPInt upi3 = upi1 + upi2;

upi3 = upi1 + 10;
upi3 = 10 + upi2;


/**
 * To avoid these costs, the article suggests explicitly overloading the operator + function to handle different
 * combinations of UPInt and int parameters directly. This approach eliminates the need for implicit type conversions
 * and the associated creation of temporary objects. The author provides examples of how to overload the operator + for
 * UPInt and int combinations, thereby enhancing efficiency.
*/
const UPInt operator + (const UPInt& lhs, const UPInt& rhs);   // add UPInt and UPInt
const UPInt operator+(const UPInt& lhs, int rhs);   // add UPInt and int
const UPInt operator + (int lhs, const UPInt& rhs);   // add int and UPInt

UPInt upi1, upi2;
UPInt upi3 = upi1 + upi2;   // fine, no temporary for upi1 or upi2
upi3 = upi1 + 10;   // fine, no temporary for upi1 or 10
upi3 = 10 + upi2;   // fine, no temporary for 10 or upi2


/**
 * However, the article cautions against over-enthusiasm in overloading, using the example of trying to overload
 * operator + for two int parameters, which is prohibited in C++. This rule exists to prevent changing the meaning of
 * operations on built-in types, which could lead to chaos in programming.
 *
 * The principle of overloading to avoid temporaries is not limited to operators but can also be applied to other
 * functions, such as those accepting string, char*, or numerical types like complex. The goal is to allow more
 * efficient function calls by eliminating unnecessary type conversions.
*/


/**
 * Finally, the article emphasizes the importance of the 80-20 rule in this context: Overloading should be implemented
 * judiciously and only when it significantly contributes to the efficiency of the program. There's no point in creating
 * many overloaded functions unless they provide a noticeable performance improvement.
*/