/**
 * Make non-leaf classes abstract.
*/

/**
 * Concrete vs. Abstract Classes:
 * In a scenario where software deals with animals, with special cases for lizards and chickens, it's suggested to use
 * an abstract class Animal for shared features and concrete classes Lizard and Chicken for specific behaviors. This
 * approach avoids partial assignments and ensures type safety.
 *
 *
 * Problems with Non-Abstract Base Classes:
 * Assigning objects of derived classes (Lizard, Chicken) through base class (Animal) pointers can lead to partial
 * assignments and mixed-type assignments, which are problematic.
*/
class Animal
{
    public:
        Animal& operator = (const Animal& rhs);
};

class Lizard: public Animal
{
    public:
        Lizard& operator = (const Lizard& rhs);
};

class Chicken: public Animal
{
    public:
        Chicken& operator = (const Chicken& rhs);
};


/**
 * Virtual Assignment Operators:
 * Making assignment operators virtual in the base class allows correct operator invocation for derived classes.
 * However, this introduces the possibility of mixed-type assignments (assigning a Chicken object to a Lizard object),
 * which is undesirable.
*/
class Animal
{
    public:
        virtual Animal& operator = (const Animal& rhs);
};

class Lizard: public Animal
{
    public:
        virtual Lizard& operator = (const Lizard& rhs) override;
};

class Chicken: public Animal
{
    public:
        virtual Chicken& operator = (const Chicken& rhs) override;
};


/**
 * Using Abstract Classes:
 * The solution proposed is to introduce an abstract base class (AbstractAnimal) from which concrete classes (Animal,
 * Lizard, Chicken) derive. This prevents instantiation of the base class, avoiding problematic assignments while
 * allowing concrete classes to have their specific behaviors.
 *
 *
 * Abstract Class with Pure Virtual Destructor:
 * Implementing a pure virtual destructor in the abstract base class is necessary for proper polymorphism and resource
 * management.
 *
 *
 * Design Transformation:
 * When needing to relate two concrete classes by public inheritance, it's beneficial to introduce an abstract class
 * from which both concrete classes inherit. This approach helps in identifying and formalizing useful abstractions.
*/
class AbstractAnimal
{
    public:
        virtual ~AbstractAnimal() = 0;

    protected:
        AbstractAnimal& operator = (const AbstractAnimal& rhs);
};

class Animal: public AbstractAnimal
{
    public:
        Animal& operator = (const Animal& rhs);
};

class Lizard: public AbstractAnimal
{
    public:
        Lizard& operator = (const Lizard& rhs);
};

class Chicken: public AbstractAnimal
{
    public:
        Chicken& operator = (const Chicken& rhs);
};


/**
 * Challenges with Third-Party Libraries:
 * When extending classes from external libraries, the inability to modify the library to introduce an abstract class
 * leads to less desirable solutions, such as composition or re-implementation of library class functionality.
 *
 *
 * General Rule:
 * Non-leaf classes in a hierarchy should be abstract to increase the reliability, robustness, comprehensibility, and
 * extensibility of the software. Exceptions may occur when working with external libraries.
*/