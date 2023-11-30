#include <cstddef>
#include <string>
/**
 * Understand the different meanings of new and delete.
 *
 * If you want to create an object on the heap, use the new operator. It both allocates memory and calls a constructor
 * for the object.
 *
 * If you only want to allocate memory, call operator new; no constructor will be called.
 *
 * If you want to customize the memory allocation that takes place when heap objects are created, write your own
 * version of operator new and use the new operator; it will automatically invoke your custom version of operator new.
 *
 * If you want to construct an object in memory you’ve already got a pointer to, use placement new.
 *
 * Arrays should use new[] and delete[].
*/

/**
 * new operator is normally used to create an object from the free store. This operator is built into the language
 * and, like sizeof, you can’t change its meaning: it always does the same thing.
 *
 * 1. It allocates enough memory to hold an object of the type requested.
 * 2. It calls a constructor to initialize an object in the memory that was allocated.
*/

/**
 * What you can change is how the memory for an object is allocated - operator new.
 * Operator new is a function that allocates raw memory, conceptually, it's not much different from malloc().
 *
 * The operator new function is usually declared like below,you can overload operator new by adding additional
 * parameters, but the first parameter must always be of type size_t. You’ll probably never want to call operator
 * new directly.
 *
 * Like malloc, operator new’s only responsibility is to allocate memory. It knows nothing about constructors.
 * All operator new understands is memory allocation. It is the job of the new operator to take the raw memory
 * that operator new returns and transform it into an object. When your compilers see a statement like below (1),
 * they must generate code that more or less corresponds to (2).
*/
void* operator new (std::size_t size);

// 1
std::string *p_s { new std::string { "Memory Management" } };

// 2
// Get raw memory for a string object
void* memory { new(sizeof(std::string)) };

// Initialize the object in the memory
/* Call std::string::string("Memory Management") */   // Calling a constructor is what we are prohibited from doing

// Make p_s point to the new object
std::string *p_s { static_cast<std::string*>(memory) };



/**
 * Placement new.
 *
 * There are times when you really want to call a constructor directly.
 *
 * Invoking a constructor on an existing object makes no sense, but occasionally you have some raw memory that’s
 * already been allocated, and you need to construct an object in the memory you have. A special version of operator
 * new called placement new allows you to do it.
 *
 * As an example of how placement new might be used, see below.
 * This function returns a pointer to an Example object that’s constructed within the buffer passed to the function.
 * Such a function might be useful for applications using shared memory or memory-mapped I/O, because objects in such
 * applications must be placed at specific addresses or in memory allocated by special routines.
*/
// Example of placement new
class Example
{
    public:
        Example(int size);
};

Example* constructExampleInBuffer(void* buffer, int size)
{
    /**
     * A use of the new operator in which an additional argument (buffer) is being specified for the implicit call
     * that the new operator makes to operator new. The operator new thus called must, in addition to the mandatory
     * size_t argument, accept a void* parameter that points to the memory the object being constructed is to occupy.
    */
    return new (buffer) Example(size);
}

/**
 * The operator new in constructExampleInBuffer is placement new, and it looks like below.
 *
 * This is all placement new needs to do. the purpose of operator new is to find memory for an object and return a
 * pointer to that memory.  In the case of placement new, the caller already knows what the pointer to the memory
 * should be, because the caller knows where the object is supposed to be placed. All placement new has to do, then,
 * is return the pointer that’s passed into it.
*/
void* operator new (std::size_t size, void* location)
{
    return location;
}


/**
 * To avoid resource leaks, every dynamic allocation must be matched by an equal and opposite deallocation.
 * The function operator delete is to the built-in delete operator as operator new is to the new operator.
 * (This is the C++ equivalent of calling malloc and free)
 *
 * If you use placement new to create an object in some memory, you should avoid using the delete operator on that
 * memory. That’s because the delete operator calls operator delete to deallocate the memory, but the memory containing
 * the object wasn’t allocated by operator new in the first place; placement new just returned the pointer that was
 * passed to it. Instead, you should undo the effect of the constructor by explicitly calling the object’s destructor:
*/
// Functions for allocating and deallocating memory in shared memory
void * mallocShared(size_t size);
void freeShared(void *memory);

void* sharedMemory { mallocShared(sizeof(Example)) };

Example* p_e { constructExampleInBuffer(sharedMemory, 10) };

// Fine, destructs the Example pointed to by p_e, but doesn't deallocate the memory containing the Example
p_e->~Example();

// Fine, deallocates the memory pointer to by p_e, but calls no destructor
freeShared(p_e);