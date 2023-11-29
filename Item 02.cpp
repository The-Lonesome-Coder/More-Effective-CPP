/**
 * Prefer C++ style casts.
*/

/**
 * C++ addresses the shortcomings of C-style casts by introducing four new cast operators:
*/
// static_cast<> - cast the object to another type
int number { 50 };
double result { static_cast<double>(number) };


// const_cast<> - modify a const object
const int num { 60 };
const int& r_num = num;

const_cast<int&>(r_num) = 70;


// dynamic_cast<> - navigate inheritance hierarchies
// reinterpret_cast<> - cast between function pointer types