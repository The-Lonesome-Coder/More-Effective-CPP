#include <iostream>
#include <string>
/**
 * Consider using lazy evaluation.
*/

/**
 * Lazy evaluation sometimes saves resources, and it is applicable in a lot of areas. Here's three of them.
*/

/**
 * 1. Reference Counting.
 *
 * Don’t bother to make a copy of something until you really need one.
 *
 * b is a copy of a, but they are never changed. So we can just implement b as a reference to a, and wait till we really
 * need to change one of them.
*/
std::string a { "Hello " };
std::string b { a };

std::string& b = a;


/**
 * 2. Lazy Fetching.
 *
 * Consider a very large object, which will take a lot of time to construct.
 *
 * If we construct a new object only to read its OjbectID, then most of our effort spent constructing the members will
 * be wasted. So we can consider postponing the construction of the other member variables until we use them.
*/
class ObjectID { };

// Large persistent objects
class LargeObject
{
    public:
        LargeObject(ObjectID id);                // restore object from disk

        const std::string& field1() const;       // value of field 1
        int field2() const;                      // value of field 2
        double field3() const;                   // ...
        const std::string& field4() const;
        const std::string& field5() const;

    private:
        ObjectID oid;
        mutable std::string* field1Value;        // see below for a
        mutable int* field2Value;                // discussion of "mutable"
        mutable double* field3Value;
        mutable std::string* field4Value;
};

// Only the value of field2 is required, so any effort spent setting up the other fields is wasted
void restoreAndProcessObject(ObjectID id)
{
    LargeObject object(id);

    if (object.field2() == 0)
    {
        std::cout << "Object " << id << ": null field2.\n";
    }
}


// The lazy approach to this problem is to read no data from disk when a LargeObject object is created.
LargeObject::LargeObject(ObjectID id)
: oid(id), field1Value(0), field2Value(0), field3Value(0) {}


const std::string& LargeObject::field1() const
{
    if (field1Value == 0)
    {
        /* read the data for field 1 from the database and make field1Value point to it */
    }

    return *field1Value;
}


/**
 * 3. Lazy Expression Evaluation.
 *
 * A programming technique where the evaluation of an expression is postponed until its value is actually needed.
 * This is contrary to the usual "eager" evaluation, where expressions are evaluated as soon as they are encountered
 * in the code.
 *
 * In C++, lazy evaluation can be implemented using various techniques, including:
 *
 * 1. Deferred Computation: Computations are wrapped in a function or a functor, and this function is called only when
 *                          the result is needed. This is useful in scenarios where a computation might be expensive and
 *                          it's not certain if the result will be used.
 *
 * 2. Using Proxies: Involves creating proxy objects that represent the result of an expression. The actual computation
 *                   is only performed when the result is explicitly requested, typically when the proxy is converted to
 *                   the target type.
 *
 * 3. Thunks: A parameterless function that encapsulates a computation. When a thunk is called, it performs the computation
 *            and returns the result.
*/
class Matrix { };

Matrix a { 1000, 1000 };
Matrix b { 1000, 1000 };
Matrix c { 1000, 1000 };