/**
 * Understand the costs of virtual functions, multiple inheritance, virtual base classes, and RTTI.
*/

/**
 * When a virtual function is called, the code executed must correspond to the dynamic type of the object on which the
 * function is invoked; the type of the pointer or reference to the object is immaterial. How can compilers provide this
 * behavior efficiently? Most implementations use virtual tables and virtual table pointers. Virtual tables and virtual
 * table pointers are commonly referred to as vtbls and vptrs, respectively.
 *
 *
 * A vtbl is usually an array of pointers to functions. (Some compilers use a form of linked list instead of an array,
 * but the fundamental strategy is the same.) Each class in a program that declares or inherits virtual functions has
 * its own vtbl, and the entries in a class's vtbl are pointers to the implementations of the virtual functions for that
 * class. Each object whose class declares virtual functions carries with it a hidden data member that points to the
 * virtual table for that class. This hidden data member — the vptr — is added by compilers at a location in the object
 * known only to the compilers.
*/