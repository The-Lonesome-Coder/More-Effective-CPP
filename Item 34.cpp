/**
 * Understand how to combine C++ and C in the same program.
*/

/**
 * Compiler Compatibility:
 * Ensure that the C++ and C compilers used for the project produce compatible object files. This compatibility is
 * essential for the seamless combination of C++ and C components in the same program.
*/


/**
 * Name Mangling:
 * C++ compilers use name mangling to give each function a unique name, which can be problematic when calling C
 * functions from C++. To prevent name mangling for C functions, use the extern "C" directive in C++ code. This tells
 * the compiler to treat these functions as if they were written in C, without mangling their names.
 *
 *
 * Using extern "C" for Function Declarations:
 * For functions that will be used in both C and C++, declare them with extern "C" to prevent name mangling. This can
 * be applied to individual functions or to a block of function declarations.
*/
// Declare a function called drawLine; don’t mangle its name
extern "C" void drawLine(int x1, int y1, int x2, int y2);


/**
 * Initialization of Statics:
 * In C++, constructors for static objects are typically called before the main function. To ensure these constructors
 * are invoked in a mixed C/C++ program, it's advised to write the main function in C++. If main must be written in C,
 * investigate compiler-specific ways to initiate static initialization and destruction.
*/
// Implement this function in C write this in C++
extern "C" int realMain(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    return realMain(argc, argv);
}


/**
 * Dynamic Memory Allocation:
 * Use new and delete for memory management in C++ parts of the program, and malloc and free in C parts. Mixing these
 * (e.g., using delete on a pointer allocated with malloc) can lead to undefined behavior.
*/


/**
 * Data Structure Compatibility:
 * Data structures shared between C++ and C should be compatible with both languages. Structures defined in C++ that
 * are also valid in C can be safely passed between the two. However, adding virtual functions or inheritance in C++
 * can change the memory layout and should be avoided for structures shared with C.
 *
 * Passing Data Structures:
 * Only pass data structures that are compatible with C, generally those that don't contain C++-specific features like
 * virtual functions or inheritance. Adding non-virtual member functions in C++ to a C-compatible struct is usually safe.
*/


/**
 * Header File Compatibility:
 * Use the __cplusplus preprocessor symbol to conditionally include extern "C" in header files shared between C++ and
 * C, ensuring proper function linkage.
*/
#ifdef __cplusplus

extern "C"
{

#endif

    void drawLine(int x1, int y1, int x2, int y2);
    void twiddleBits(unsigned char bits);
    void simulate(int iterations);


#ifdef __cplusplus
}

#endif