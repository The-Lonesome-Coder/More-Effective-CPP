#include <iostream>
/**
 * Never treat array polymorphically.
*/

/**
 * One of the most important features of inheritance is that you can manipulate derived class objects through
 * pointers and references to base class objects. Such pointers and references are said to behave polymorphically.
 *
 * C++ also allows you to manipulate arrays of derived class objects through base class pointers and references,
 * but it almost never works the way you want it to.
*/
// Assume Base and Derived contains only int
class Base { };
class Derived : public Base { };


/**
 * Consider the following function. It works fine when passing it an array of Base object.
 *
 * array[i] is really just shorthand for an expression involving pointer arithmetic: it stands for *(array+i).
 * The distance between them is i*sizeof(an object in the array), because there are i objects between array[0]
 * and array[i].
 *
 * In this case, when you pass it an array of Derived objects, notwithstanding your compilers will accept this
 * function  * call without complaint, they’d assume each object in the array is the size of a Base, but each object
 * would actually be the size of a Derived. Derived classes usually have more data members than their base classes,
 * so derived class objects are usually larger than base class objects.
 *
 * We thus expect a Derived object to be larger than a Base object. If it is, the pointer arithmetic generated for
 * printArray will be wrong for arrays of Derived objects, and there’s no telling what will happen when printArray
 * is invoked on a Derived array. Whatever does happen, it’s a good bet it won’t be pleasant.
*/
void printArray(std::ostream& os, const Base array[], std::size_t elements)
{
    for (std::size_t i; i < elements; ++i)
    {
        // Assume operator << is defined for Base object
        os << array[i];
    }
}


/**
 * The language specification says the result of deleting an array of derived class objects through a base class
 * pointer is undefined.
*/