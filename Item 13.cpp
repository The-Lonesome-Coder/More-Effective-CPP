#include <iostream>
#include <stdexcept>
/**
 * Catch exceptions by reference.
*/

/**
 * throw() dynamic exception specification in function declaration is deprecated in C++11, and removed in C++17.
 * throw() specifier is deprecated in C++17, and removed in C++20.
 * 
 * In following code, throw() will be convert to modern "noexcept".
*/

/**
 * You can catch exceptions by pointer, by value or by reference.
*/

/**
 * 1. Catching exceptions by pointer leaves us with the question of whether to delete the pointer.
 *    When you write (1), you definitely don't want to delete the pointer caught by catch.
 *
 *    But if you write (2), you will suffer from memory leaks if you don't delete the pointer.
 *    So you better not catch exceptions by pointer.
*/
// (1)
static std::exception e;
throw (&e);

// (2)
std::exception* e = new std::exception;
throw (&e);


/**
 * 2. Catching exceptions by value also causes trouble. First, the exception objects will be copied twice,
 *    as discussed in Item 12. Moreover, it gives rise to the specter of the slicing problem.
*/
class exception
{                                               // As above, this is a standard exception class
    public:
        virtual const char * what() noexcept;   // Returns a brief description of the exception
};


class runtime_error : public exception { };     // Also from the standard C++ exception hierarchy


class Validation_error : public runtime_error   // This is a class added by a client
{
    public:
       virtual const char * what() noexcept;     // This is a redefinition of the function declared in class exception above
};


void someFunction()                 // May throw a validation exception
{
    if (/* a validation test fails */)
    {
        throw Validation_error();
    }
}


void doSomething()
{
    try
    {
        someFunction();             // May throw a validation exception
    }
    catch (exception ex)            // Catches all exceptions in or derived from the standard hierarchy
    {
        std::cerr << ex.what();     // calls exception::what(), never Validation_error::what()
    }
}


/**
 * 3. Catching exceptions by reference will solve all the problems above.
 *    So you should always catch exceptions by reference.
*/