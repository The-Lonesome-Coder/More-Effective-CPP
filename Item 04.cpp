/**
 * Avoid gratuitous (compiler-generated) default constructor.
*/

/**
 *  If a class lacks a default constructor, there are restrictions on how you can use that class.
*/

/**
 * Consider a class that lacks default constructor, its use may be problematic in three contexts.
 *
 * 1. Creation of arrays. There is, in general, no way to specify constructor arguments for objects in arrays.
 *
 * 2. They are ineligible for use with many template-based container classes. It’s a common requirement for such
 *    templates that the type used to instantiate the template provide a default constructor. In most cases,
 *    careful template design can eliminate the need for a default constructor.
 *
 * 3. Virtual base classes lacking default constructors are a pain to work with. That’s because the arguments for
 *    virtual base class constructors must be provided by the most derived class of the object being constructed.
 *
*/
// 1
class Equipment
{
    public:
        Equipment(int ID);
};

Equipment pieces[10];   // Error, no way to call Equipment's constructor
Equipment *best = new Equipment[10];    // Same error


// 2
template <class T>
class Array
{
    public:
        Array(int size);

    private:
        T* data;
};

template <class T>
Array<T>::Array(int size)
{
    // Calls T::T() for each element of array
    data = new T[size];
}


/**
 * Inclusion of meaningless default constructors affects the efficiency of classes, so it’s best to avoid them
 * in classes where they make no sense. That places some limits on how such classes can be used, yes, but it also
 * guarantees that when you do use such classes, you can expect that the objects they generate are fully initialized
 * and are efficiently implemented.
*/