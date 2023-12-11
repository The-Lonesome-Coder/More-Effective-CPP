#include <iostream>
#include <list>
/**
 * Virtualizing constructors and non-member functions.
*/


/**
 * Example Classes:
 * The article presents an example with classes like NLComponent, TextBlock, Graphic, and NewsLetter. NLComponent is
 * an abstract base class for newsletter components, while TextBlock and Graphic are derived classes. NewsLetter
 * consists of a list of NLComponent objects.
*/
// Abstract base class for newsletter components contains at least onepure virtual function
class NLComponent { };

// Contains no pure virtual functions
class TextBlock: public NLComponent { };

// Contains no pure virtual functions
class Graphic: public NLComponent { };

// A newsletter object consists of a list of NLComponent objects
class NewsLetter
{
    private:
        std::list<NLComponent*> components;
};


/**
 * Virtual Constructors:
 * The article explains that a virtual constructor is a function that creates different types of objects depending on
 * the input it receives. This concept is demonstrated in the context of creating newsletter components from an input
 * stream.
*/
class NewsLetter
{
    public:
        NewsLetter(std::istream& str);

        // Consider what readComponent does. It creates a new object, either a TextBlock or a Graphic, depending on
        // the data it reads. Because it creates new objects, it acts much like a constructor, but because it can create
        // different types of objects, we call it a virtual constructor.
        static NLComponent* readComponent(std::istream& str);

    private:
        std::list<NLComponent*> components;
};


NewsLetter::NewsLetter(std::istream& str)
{
    while (str)
    {
        // Add the pointer returned by readComponent to the end of the components list; "push_back" is a list
        // member function that inserts at the end of the list
        components.push_back(readComponent(str));
    }
}


/**
 * Virtual Copy Constructor:
 * A specific kind of virtual constructor, the virtual copy constructor, is also discussed. It returns a pointer to a
 * new copy of the object invoking the function. The article provides examples of how to implement a virtual copy
 * constructor in the NLComponent class and its derived classes.
*/
class NLComponent
{
    public:
        // Declaration of virtual copy constructor
        virtual NLComponent * clone() const = 0;
};

class TextBlock: public NLComponent
{
    public:
        // Virtual copy constructor
        virtual TextBlock* clone() const { return new TextBlock(*this); }
};


class Graphic: public NLComponent
{
    public:
        // virtual copy constructor
        virtual Graphic* clone() const { return new Graphic(*this); }
};


/**
 * Implementation Details:
 * The article delves into the implementation details of these concepts, such as how a class’s virtual copy constructor
 * calls its real copy constructor, ensuring consistency between shallow and deep copies.
*/
class NewsLetter
{
    public:
        NewsLetter(const NewsLetter& rhs);

    private:
        std::list<NLComponent*> components;
};


NewsLetter::NewsLetter(const NewsLetter& rhs)
{
    // Iterate over rhs’s list, using each element’s virtual copy constructor to copy the element into the components
    // list for this object. For details on how the following code works, see Item 35.
    for (std::list<NLComponent*>::const_iterator it = rhs.components.begin(); it != rhs.components.end(); ++it)
    {
        // "it" points to the current element of rhs.components, so call that element’s clone function to get a copy of
        // the element, and add that copy to the end of this object’s list of components
        components.push_back((*it)->clone());
    }
}



/**
 * Relaxation in Virtual Function Return Types:
 * It notes a relaxation in the rules for virtual function return types, allowing derived classes’ functions to return
 * a pointer to a class derived from the base class.
 *
 *
 * Non-Member Functions Acting Virtually:
 * The article also discusses how non-member functions can be made to act virtually. It suggests using virtual
 * functions for the core functionality and having non-member functions simply call these virtual functions. This
 * approach is illustrated with the example of implementing output operators for the TextBlock and Graphic classes.
 *
 *
 * Inline Functions for Efficiency:
 * To avoid the cost of a function call, the article recommends inlining the non-virtual function that calls the
 * virtual function.
 *
*/
class NLComponent
{
    public:
        virtual std::ostream& print(std::ostream& s) const = 0;
};


class TextBlock: public NLComponent
{
    public:
        virtual std::ostream& print(std::ostream& s) const;
};


class Graphic: public NLComponent
{
    public:
        virtual std::ostream& print(std::ostream& s) const;
};


inline std::ostream& operator << (std::ostream& s, const NLComponent& c)
{
    return c.print(s);
}


/**
 * Complexity with Multiple Arguments:
 * Finally, the article touches on the complexity of making non-member functions act virtually on more than one of
 * their arguments, pointing readers to another item for further details.
*/