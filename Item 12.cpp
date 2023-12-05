/**
 * Understand how throwing an exception differs from passing a parameter or calling a virtual function.
*/

/**
 * There are three major difference.
*/

/**
 * 1. Exception objects are always copied. When caught by value, they are copied twice.
*/
class Widget { };

catch (Widget w)
    // two copies of the exception objects are made.
    // 1.  the throw object -> temporary object
    // 2.  temporary object -> w

catch (Widget& w)

catch (const Widget& w)
    // one copy
    // the thrown object -> temporary object
    // Widget & w=temporary object

catch (Widget *pw)

catch (const Widget *pw)
    // pointers are copied
    // for Widget * pw, two copies
    // for const Widget * pw, one copy


/**
 * 2. catch(double d) won't catch an int. Exception objects can only be converted up the inheritance hierarchy.
*/
try
{
    int a;
    throw a
}
catch(double d);


class A { };

class B : public A { };

try
{
    B b;
    throw b;
}
catch(A & a); // okay, b can be caught


/**
 * 3. Exception objects are caught in first-fit order.
*/
try
{
    B b;
    throw b;
}
catch(A & a){ }   // this catches exceptions of type
                  // A and all its derived classes

catch(B & b){ }   // this will never be executed, for all B are caught by
                  // the one above


/**
 * The difference between throw; and throw a;
*/
try
{
    B exc_b;
    throw exc_b;
}
catch(A & a)
{
    throw;   // this throws a copy of exc_b (the temporary object)
}


try
{
    B exc_b;
    throw exc_b;
}
catch(A & a)
{
    throw a;   // this performs A a = exc_b; (the temporary object) and then throw a
}