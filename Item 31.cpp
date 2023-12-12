#include <string>
#include <typeinfo>
/**
 * Making functions virtual with respect to more than one object.
*/

/**
 * Game Scenario:
 * The game involves objects like spaceships, space stations, and asteroids that can collide with each other.
 * Different collision outcomes are determined based on the types of objects involved and their collision dynamics.
 *
 *
 * Common Features and Inheritance:
 * Spaceships, space stations, and asteroids share common features, such as motion, leading to the suggestion of a base
 * class GameObject from which all these items inherit.
 *
 *
 * Collision Handling Challenge:
 * The primary challenge is to structure the C++ code to handle collisions between these objects, which varies depending
 * on the types of objects colliding.
*/
class GameObject { };
class SpaceShip: public GameObject { };
class SpaceStation: public GameObject { };
class Asteroid: public GameObject { };

void checkForCollision(GameObject& object1, GameObject& object2)
{
    if (theyJustCollided(object1, object2))
    {
        processCollision(object1, object2);
    }
    else
    {
        /* Do something */
    }
}


/** Virtual Functions and RTTI:
 * The use of virtual functions and Run-Time Type Information (RTTI) is discussed. Virtual functions allow a function's
 * behavior to depend on the object's dynamic type, but C++ standard virtual functions only account for one object's
 * type. RTTI can be used to determine an object's type at runtime, but this approach has drawbacks, including
 * maintenance issues and breaking encapsulation.
 *
 *
 * Double-Dispatching:
 * The concept of double-dispatching is introduced, where a function call depends on the runtime type of two objects.
 * This is not directly supported in C++, requiring a custom implementation.
*/
class GameObject
{
    public:
        virtual void collide(GameObject& otherObject) = 0;
};

class SpaceShip: public GameObject
{
    public:
        virtual void collide(GameObject& otherObject);
};


// If we collide with an object of unknown type, we throw an exception of this type:
class CollisionWithUnknownObject
{
    public:
        CollisionWithUnknownObject(GameObject& whatWeHit);
};


void SpaceShip::collide(GameObject& otherObject)
{
    const type_info& objectType = typeid(otherObject);

    if (objectType == typeid(SpaceShip))
    {
        SpaceShip& ss = static_cast<SpaceShip&>(otherObject);

        // Process a SpaceShip-SpaceShip collision;
    }
    else if (objectType == typeid(SpaceStation))
    {
        SpaceStation& ss = static_cast<SpaceStation&>(otherObject);

        // Process a SpaceShip-SpaceStation collision;
    }
    else if (objectType == typeid(Asteroid))
    {
        Asteroid& a = static_cast<Asteroid&>(otherObject);

        // Process a SpaceShip-Asteroid collision;
    }
    else
    {
        throw CollisionWithUnknownObject(otherObject);
    }
}


/**
 * Virtual Function Implementation:
 * A method using two virtual function calls is described. This approach correctly identifies both objects' types
 * involved in a collision but has the downside of requiring changes to class definitions when new types are added.
*/
class GameObject
{
    public:
        virtual void collide(GameObject& otherObject) = 0;
        virtual void collide(SpaceShip& otherObject) = 0;
        virtual void collide(SpaceStation& otherObject) = 0;
        virtual void collide(Asteroid& otherObject) = 0;
};


class SpaceShip: public GameObject
{
    public:
        virtual void collide(GameObject& otherObject);
        virtual void collide(SpaceShip& otherObject);
        virtual void collide(SpaceStation& otherObject);
        virtual void collide(Asteroid& otherobject);
};


void SpaceShip::collide(GameObject& otherObject)
{
    otherObject.collide(*this);
}

void SpaceShip::collide(SpaceShip& otherObject)
{
    // Process a SpaceShip-SpaceShip collision;
}

void SpaceShip::collide(SpaceStation& otherObject)
{
    // Process a SpaceShip-SpaceStation collision;
}

void SpaceShip::collide(Asteroid& otherObject)
{
    // Process a SpaceShip-Asteroid collision;
}


/**
 * Emulating Virtual Function Tables:
 * The text explains how to emulate virtual function tables manually, a method typically done by compilers. This
 * involves creating an associative array mapping object types to function pointers, representing collision behaviors.
 *
 * Extensibility and Maintenance Concerns:
 * The discussed approaches each have trade-offs regarding system extensibility and maintenance. Adding new object
 * types often requires significant changes and recompilation.
*/
class GameObject
{
    public:
        virtual void collide(GameObject& otherObject) = 0;
};

class SpaceShip: public GameObject
{
    public:
        virtual void collide(GameObject& otherObject);
        virtual void hitSpaceShip(SpaceShip& otherObject);
        virtual void hitSpaceStation(SpaceStation& otherObject);
        virtual void hitAsteroid(Asteroid& otherObject);
};

void SpaceShip::hitSpaceShip(SpaceShip& otherObject)
{
    // Process a SpaceShip-SpaceShip collision;
}
void SpaceShip::hitSpaceStation(SpaceStation& otherObject)
{
    // Process a SpaceShip-SpaceStation collision;
}
void SpaceShip::hitAsteroid(Asteroid& otherObject)
{
    // Process a SpaceShip-Asteroid collision;
}


/**
 * Alternative Approaches:
 * Other potential solutions like using non-member functions for collision processing and dynamic map-based approaches
 * are considered. These offer various advantages, such as avoiding the need for class modification when new types are
 * added, but they also come with their complexities.
*/
class CollisionMap
{
    public:
        typedef void (*HitFunctionPtr)(GameObject&, GameObject&);

        void addEntry(const std::string& type1, const std::string& type2, HitFunctionPtr collisionFunction, bool symmetric = true);

        void removeEntry(const std::string& type1, const std::string& type2);

        HitFunctionPtr lookup(const std::string& type1, const std::string& type2);

        // This function returns a reference to the one and only map — see Item 26
        static CollisionMap& theCollisionMap();


    private:
        // These functions are private to prevent the creation of multiple maps — see Item 26
        CollisionMap();

        CollisionMap(const CollisionMap&);
};


/**
 * Final Considerations:
 * The text concludes by acknowledging the inherent challenges in implementing multiple dispatch in C++ and suggests
 * that the best approach depends on specific project needs and constraints.
*/