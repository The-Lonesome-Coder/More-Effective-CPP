#include <string>
/**
 * Distinguish between pointers and references.
*/

/**
 * If you have a variable whose purpose is to refer to another object, but it is possible that there might
 * not be an object to refer to, you should make the variable a pointer, because then you can set it to null.
 * On the other hand, if the variable must always refer to an object, i.e., if your design does not allow for the
 * possibility that the variable is null, you should probably make the variable a reference.
*/

/**
 * The result of a reference to null pointer is undefined.
 *
 * Because a reference must refer to an object, C++ requires that references be initialized;
 * pointers are subject to no such restriction.
*/
char *p_c = nullptr;
char& r_c= = *p_c;   // Dereferencing a null pointer is undefined

std::string& r_str;   // Error, references must be initialized

std::string str { "Apple" };
std::string& r_s = str;   // Fine


/**
 * Pointers may be reassigned to refer to different objects.
 * A reference, however, always refers to the object with which it is initialized.
*/
std::string s1 { "Apple" };
std::string s2 { "Banana" };

std::string& r_s1 = s1;
std::string* p_s1 = &s1;

r_s1 = s2;   // r_s1 still refers to s1, but s1's value is now "Banana"
p_s1 = &s2;   // p_s1 now points to s2


/**
 * You should use a pointer whenever you need to take into account the possibility that there’s nothing to refer to,
 * or whenever you need to be able to refer to different things at different times.
 *
 * You should use a reference whenever you know there will always be an object to refer to and you also know that
 * once you’re referring to that object, you’ll never want to refer to anything else. They’re also appropriate when
 * implementing operators whose syntactic requirements make the use of pointers undesirable.
*/