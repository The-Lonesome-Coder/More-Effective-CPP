#include <cstring>
/**
 * Reference counting.
*/

/**
 * Reference counting is a method for managing memory and resources in programming, especially useful in languages like
 * C++ where manual memory management is required. The technique allows multiple objects to share a single
 * representation of a value, which has two primary benefits:
 *
 * 1. Simplified Bookkeeping for Heap Objects:
 * It alleviates the complexity of tracking who owns an object and is responsible for deallocating it. This is typically
 * challenging as ownership can shift during program execution. With reference counting, an object essentially owns
 * itself and self-destructs when it's no longer in use, acting as a form of garbage collection.
 *
 * 2. Efficiency in Memory and Performance:
 * If many objects share the same value, it's inefficient to store and manage separate copies of this value. Reference
 * counting allows these objects to share a single instance of the value, saving memory and potentially improving
 * performance as it reduces the need to repeatedly construct and destruct identical objects.
*/


/**
 * The implementation of reference counting involves associating each value with a reference count. This count tracks
 * how many objects are using the value. When an object changes its value or is destroyed, the reference count is
 * adjusted. If the count drops to zero, the shared value is destroyed to prevent memory leaks.
 *
 *
 * The process is illustrated with a String class example, where multiple string objects might hold the same text.
 * In a typical implementation, each string object would carry its own copy of the text. Reference counting changes
 * this by storing only one copy of the text and letting all string objects with that text share this single copy,
 * alongside a count of how many objects are sharing it.
 *
 *
 * The article also delves into the implementation details of reference counting in C++. It discusses how to manage the
 * reference count and the shared value, and how to handle copying and assignment of objects in a way that correctly
 * updates reference counts. This includes managing scenarios where an object's value is modified (copy-on-write),
 * ensuring that modifications don't inadvertently affect other objects sharing the same value.
*/
class String
{
    public:
        String(const char* value = "");
        String& operator=(const String& rhs);

        const char& operator [] (int index) const;  // For const Strings
        char& operator [] (int index);              // For non-const Strings

        ~String();

    private:
        // Holds a reference count and a string value
        struct StringValue
        {
            size_t refCount;
            bool shareable;
            char* data;

            StringValue(const char *initValue);
            ~StringValue();
        };

        // Value of this String
        StringValue* value;
};


String::String(const String& rhs)
{
    if (rhs.value->shareable)
    {
        value = rhs.value;
        ++value->refCount;
    }
    else
    {
        value = new StringValue(rhs.value->data);
    }
}


String& String::operator = (const String& rhs)
{
    // Do nothing if the values are already the same; this subsumes the usual test of this against &rhs
    if (value == rhs.value)
    {
        return *this;
    }

    // destroy *this’s value if no one else is using it
    if (--value->refCount == 0)
    {
        delete value;
    }

    // Have *this share rhs’s value
    value = rhs.value;
    ++value->refCount;

    return *this;
}


const char& String::operator [] (int index) const
{
    return value->data[index];
}


char& String::operator [] (int index)
{
    // If we’re sharing a value with other String objects, break off a separate copy of the value for ourselves
    if (value->refCount > 1)
    {
        // Decrement current value’s refCount, because we won’t be using that value any more
        --value->refCount;

        value->shareable = false;

        // Make a copy of the value for ourselves
        value = new StringValue(value->data);
    }

    // return a reference to a character inside our unshared StringValue object
    return value->data[index];
}


String::~String()
{
    if (--value->refCount == 0)
    {
        delete value;
    }
}


String::StringValue::StringValue(const char *initValue)
    : refCount { 1 }, shareable { true }
{
    data = new char[std::strlen(initValue) + 1];
    std::strcpy(data, initValue);
}


String::StringValue::~StringValue()
{
    delete [] data;
}



/**
 * Additionally, the article introduces RCObject and RCPtr, two classes that encapsulate the mechanics of reference
 * counting, making it easier to add reference counting to any class. This implementation strategy involves creating a
 * base class for reference-counted objects (RCObject) and using smart pointers (RCPtr) to automate reference count
 * manipulations.
*/
class RCObject
{
    public:
        RCObject();
        RCObject(const RCObject& rhs);
        RCObject& operator = (const RCObject& rhs);

        virtual ~RCObject() = 0;

        void addReference();
        void removeReference();

        void markUnshareable();
        bool isShareable() const;
        bool isShared() const;

    private:
        size_t refCount;
        bool shareable;
};

RCObject::RCObject()
    : refCount(0), shareable(true) {}

RCObject::RCObject(const RCObject&)
    : refCount(0), shareable(true) {}

RCObject& RCObject::operator=(const RCObject&) { return *this; }

RCObject::~RCObject() {}

void RCObject::addReference() { ++refCount; }

void RCObject::removeReference() { if (--refCount == 0) delete this; }

void RCObject::markUnshareable() { shareable = false; }

bool RCObject::isShareable() const { return shareable; }

bool RCObject::isShared() const { return refCount > 1; }


class String
{
    private:
        struct StringValue: public RCObject {  };

        StringValue *value;
};


/**
 * In conclusion, reference counting is a powerful technique for managing resources and optimizing memory usage in
 * programs, particularly useful in languages without automatic garbage collection. However, it adds complexity to the
 * code and can introduce performance overhead due to the constant updating of reference counts. It's most effective
 * when objects frequently share large, immutable values.
*/