#include <list>
/**
 * Requiring or prohibiting heap-based objects.
*/

/**
 * Requiring Heap-Based Objects:
 *
 * Preventing Non-Heap Allocation:
 * To ensure objects are only created on the heap, the constructors can be made public, but the destructor should be
 * private. This prevents automatic construction and destruction (which happens for non-heap objects) while allowing
 * dynamic allocation using new.
 *
 * Pseudo-Destructor:
 * A pseudo-destructor can be introduced to manage object destruction. This is a public function that internally calls
 * delete this.
*/
class UPNumber
{
    public:
        UPNumber();
        UPNumber(int initValue);
        UPNumber(double initValue);
        UPNumber(const UPNumber& rhs);

        // Pseudo-destructor (a const member function, because even const objects may be destroyed)
        void destroy() const { delete this; }

    private:
        ~UPNumber();
};

UPNumber n;                     // Error! (legal here, but illegal when n’s dtor is later implicitly invoked)
UPNumber *p = new UPNumber;     // Fine

delete p;                       // error! attempt to call private destructor
p->destroy();                   // Fine


/**
 * Inheritance and Containment Issues:
 * Making the destructor private prevents inheritance and containment. This can be resolved by making the destructor
 * protected and using pointers for containment.
*/
class UPNumber
{
    // Declares dtor or ctors private
    public:
        UPNumber();
        UPNumber(int initValue);
        UPNumber(double initValue);
        UPNumber(const UPNumber& rhs);

        void destroy() const { delete this; }

    protected:
        ~UPNumber();
};

class NonNegativeUPNumber : public UPNumber { };    // Fine

class Asset
{
    public:
        Asset(int initValue);
        ~Asset();

    private:
        UPNumber *value;
};

// Fine
Asset::Asset(int initValue)
    : value(new UPNumber(initValue)) { }


// Fine
Asset::~Asset()
{
    value->destroy();
}


/**
 * Heap Determination Limitations:
 * It's challenging to reliably determine if an object is on the heap. Techniques like setting a flag in the operator
 * new or using address comparisons are unreliable and non-portable.
*/



/**
 * Prohibiting Heap-Based Objects:
 *
 * Preventing Heap Allocation:
 * By making operator new and operator delete private, direct heap allocation of objects can be prevented.
*/
class UPNumber
{
    private:
        static void* operator new(size_t size);
        static void operator delete(void *ptr);
};


/**
 * Effect on Derived Classes:
 * This approach also often prevents derived classes from being heap-allocated unless they explicitly declare their own
 * operator new.
*/
// Assume this class declares no operator new
class NonNegativeUPNumber: public UPNumber { };

NonNegativeUPNumber n1;                             // Fine
static NonNegativeUPNumber n2;                      // Fine
NonNegativeUPNumber *p = new NonNegativeUPNumber;   // Error! attempt to call private operator new


/**
 * No Impact on Containment:
 * This method doesn’t affect objects that contain UPNumber objects as members, as these are not directly allocated on
 * the heap.
 *
 *
 * Limitations:
 * Similar to requiring heap-based objects, reliably preventing heap allocation also faces challenges, as there’s no
 * portable way to ensure an object is not on the heap.
*/


/**
 * HeapTracked Mixin Class:
 * To track heap allocations, an abstract mixin base class HeapTracked can be used. This class keeps a list of addresses
 * returned by operator new and provides a method to check if an object is on the heap.
 *
 *
 * Dynamic Casting in HeapTracked:
 * dynamic_cast<const void*> is used in HeapTracked to get the raw address of an object, which is then compared against
 * the list of heap-allocated addresses.
*/
// Mixin class; keeps track of ptrs returned from op. new
class HeapTracked
{
    public:
        // Exception class
        class MissingAddress{};
        virtual ~HeapTracked() = 0;
        static void* operator new(size_t size);
        static void operator delete(void *ptr);
        bool isOnHeap() const;

    private:
        using RawAddress = const void*;
        static inline std::list<RawAddress> addresses;
};


// HeapTracked’s destructor is pure virtual to make the class abstract.
// The destructor must still be defined, however, so we provide this empty definition.
HeapTracked::~HeapTracked() {}

void* HeapTracked::operator new(size_t size)
{
    void *memPtr = ::operator new(size);        // Get the memory
    addresses.push_front(memPtr);               // Put its address at the front of the list

    return memPtr;
}

void HeapTracked::operator delete(void *ptr)
{
    // Gracefully handle null pointers
    if (ptr == 0)
    {
        return;
    }

    // Get an "iterator" that identifies the list entry containing ptr; see Item 35 for details
    std::list<RawAddress>::iterator it = find(addresses.begin(), addresses.end(), ptr);

    // If an entry was found
    if (it != addresses.end())
    {
        addresses.erase(it);        // Remove the entry
        ::operator delete(ptr);     // Deallocate the memory
    }
    else
    {
        throw MissingAddress();     // ptr wasn’t allocated by
    }
}

bool HeapTracked::isOnHeap() const
{
    // Get a pointer to the beginning of the memory occupied by *this; see below for details
    const void *rawAddress = dynamic_cast<const void*>(this);

    // Look up the pointer in the list of addresses returned by operator new
    std::list<RawAddress>::iterator it = find(addresses.begin(), addresses.end(), rawAddress);

    return it != addresses.end(); // return whether it was
}



/**
 * Application Limitation:
 * The HeapTracked class cannot be used with built-in types like int and char as they cannot inherit from classes.
*/