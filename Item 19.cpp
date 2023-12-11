#include <iostream>
#include <iomanip>
#include <string>
/**
 * Understand the origin of temporary object.
*/

/**
 * Definition of Temporary Objects:
 * Unlike local variables in a function, which might be referred to as "temporaries" colloquially, true temporary
 * objects in C++ are unnamed and invisible in source code. They are created and destroyed automatically by the compiler.
*/

/**
 * Function Call Conversions:
 * Temporary objects are often created when there's a type mismatch between an argument passed to a function and the
 * function's parameter. The article gives an example of a function countChar that counts the number of occurrences of
 * a character in a string. When a char array (like buffer) is passed to this function, which expects a const string&,
 * the compiler creates a temporary string object to match the type. After the function call, this temporary object is
 * destroyed.
*/
#define MAX_STRING_LEN 50

// Returns the number of occurrences of ch in str
size_t countChar(const std::string& str, char ch);
char buffer[MAX_STRING_LEN];
char c;

// Read in a char and a string; use setw to avoid overflowing buffer when reading the string
std::cin >> c >> std::setw(MAX_STRING_LEN) >> buffer;
std::cout << "There are " << countChar(buffer, c) << " occurrences of the character " << c << " in " << buffer << std:::endl;




/**
 * Efficiency Concerns:
 * The creation and destruction of these temporary objects, especially in frequently called functions or in
 * performance-critical parts of code, can be an unnecessary and costly overhead.
 *
 *
 * Eliminating Temporary Objects:
 * Two general strategies to avoid the cost of temporary objects are:
 * 1. Redesigning code to prevent type conversions (discussed in Item 5).
 * 2. Modifying software so that conversions are unnecessary (Item 21). For instance, ensuring the function's parameter
 *    types match the types of arguments passed can prevent unnecessary temporary objects.
*/

/**
 * References-to-Non-Const and Temporaries:
 * When passing an object to a reference-to-non-const parameter, temporary objects are not created, as this could lead
 * to confusion and unintended behavior. The article uses an uppercasify function example to illustrate this.
*/
void uppercasify(std::string& str);


/**
 * Returning Objects from Functions:
 * Another common scenario for the creation of temporary objects is when a function returns an object, such as the
 * operator+ for a Number type. Each time such a function is called, a temporary object for the return value is created
 * and later destroyed.
 *
 *
 * Optimizations:
 * Some optimizations, like the return value optimization (Item 20), can help reduce or eliminate the creation of
 * temporary objects in certain scenarios.
*/