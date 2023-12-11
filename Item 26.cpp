#include <memory>
/**
 * Limiting the number of objects of a class.
*/


/**
 * Preventing Any Instantiation:
 * To prevent any instantiation of a class, declare its constructors as private. This suppresses object creation,
 * effectively allowing zero instances.
*/
class CantBeInstantiated
{
    private:
        CantBeInstantiated();
        CantBeInstantiated(const CantBeInstantiated&);
};


/**
 * Single Instance (Singleton Pattern):
 * For allowing only one instance, create a static function in the class that returns a reference to a static instance.
 * This is demonstrated with the Printer class example, where the Printer class has private constructors, and a static
 * function thePrinter() returns a reference to the sole Printer instance.
*/
class PrintJob { };

class Printer
{
    public:
        void submitJob(const PrintJob& job);
        void reset();
        void performSelfTest();

        friend Printer& thePrinter();

    private:
        Printer();
        Printer(const Printer& rhs);
};

Printer& thePrinter()
{
    // The single printer object
    static Printer p;

    return p;
}


/**
 * Namespace Usage:
 * To avoid global scope pollution and potential naming conflicts, classes and functions like Printer and thePrinter()
 * can be encapsulated within a namespace.
*/
namespace PrintingStuff
{
    // This class is in the PrintingStuff namespace
    class Printer
    {
        public:
            void submitJob(const PrintJob& job);
            void reset();
            void performSelfTest();

            friend Printer& thePrinter();

        private:
            Printer();
            Printer(const Printer& rhs);
    };

    // So is this function
    Printer& thePrinter()
    {
        static Printer p;

        return p;
    }
}


/**
 * Initialization Subtleties:
 * Static objects should be defined within a function rather than as class statics to ensure they are created only when
 * needed and to control the initialization time.
 *
 *
 * Object Counting:
 * For limiting the number of instances to a specific number, use a static counter incremented in constructors and
 * decremented in destructors. However, this approach becomes complex when dealing with derived classes or objects
 * contained within other objects.
*/
class Printer
{
    public:
        // Exception class for use when too many objects are requested
        class TooManyObjects{};

        Printer();
        ~Printer();

    private:
        static inline size_t numObjects;

        // There is a limit of 1 printer, so never allow copying
        Printer(const Printer& rhs);
};

// Obligatory definition of the class static
size_t Printer::numObjects = 0;

Printer::Printer()
{
    if (numObjects >= 1)
    {
        throw TooManyObjects();
    }

    // proceed with normal construction here;
    ++numObjects;
}

Printer::~Printer()
{
    // Perform normal destruction here;

    --numObjects;
}


/**
 * Pseudo-Constructors:
 * To manage object creation and enforce limits, use pseudo-constructors. These are static member functions that create
 * and return instances, allowing control over the number of instances created.
*/
class FSA
{
    public:
        ~FSA() = default;

        // Pseudo-constructors
        static std::unique_ptr<FSA> makeFSA();
        static std::unique_ptr<FSA> makeFSA(const FSA& rhs);

    private:
        FSA();
        FSA(const FSA& rhs);
};

std::unique_ptr<FSA> FSA::makeFSA() { return std::make_unique<FSA>(); }
std::unique_ptr<FSA> FSA::makeFSA(const FSA& rhs) { return std::make_unique<FSA>(rhs); }


/**
 * Object-Counting Base Class:
 * Introduce a base class template for counting instances. This base class manages the instantiation count, and derived
 * classes inherit this functionality, reducing code duplication.
*/
template<class BeingCounted>
class Counted
{
    public:
        class TooManyObjects{}; // for throwing exceptions
        static size_t objectCount() { return numObjects; }

    protected:
        Counted();
        Counted(const Counted& rhs);
        ~Counted() { --numObjects; }

    private:
        static inline size_t numObjects;
        static inline const size_t maxObjects;

        // To avoid ctor code duplication
        void init();
};

template<class BeingCounted>
Counted<BeingCounted>::Counted()
{
    init();
}

template<class BeingCounted>
Counted<BeingCounted>::Counted(const Counted<BeingCounted>&)
{
    init();
}

template<class BeingCounted>
void Counted<BeingCounted>::init()
{
    if (numObjects >= maxObjects)
    {
        throw TooManyObjects();
    }

    ++numObjects;
}


// Printer class that use the Counted template
class Printer: private Counted<Printer>
{
    public:
        // Pseudo-constructors
        static Printer * makePrinter();
        static Printer * makePrinter(const Printer& rhs);
        ~Printer();
        void submitJob(const PrintJob& job);
        void reset();
        void performSelfTest();

        using Counted<Printer>::objectCount;
        using Counted<Printer>::TooManyObjects;

    private:
        Printer();
        Printer(const Printer& rhs);
};


/**
 * Client Responsibilities:
 * With pseudo-constructors, clients must remember to delete objects to avoid resource leaks, or use smart pointers
 * for automatic memory management.
 *
 *
 * Generalizing for Multiple Objects:
 * This concept can be generalized to allow a specific maximum number of instances (not just one) by adjusting the
 * static counter and conditions in constructors.
 *
 *
 * Initialization of Statics:
 * Clients of the counting class template must provide initialization for the maximum number of allowable instances,
 * such as setting the maximum number of Printer objects to 10.
*/
const size_t Counted<Printer>::maxObjects = 10;