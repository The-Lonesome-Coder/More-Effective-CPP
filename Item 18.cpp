#include <map>
#include <string>
#include <string_view>
/**
 * Amortize the cost of expected computations.
*/

/**
 * Over-Eager Evaluation:
 * This approach involves pre-computing or maintaining running calculations to quickly provide results when needed.
 * It's especially useful when certain computations are expected to be requested frequently.
 *
 * Example -
 * Data Collection Template:
 * The author illustrates this concept using a DataCollection class template, which maintains running minimum, maximum,
 * and average values for a collection of numeric data. This allows for immediate response to queries without additional
 * computation.
 *
*/
template<class NumericalType>
class DataCollection
{
    public:
        NumericalType min() const;
        NumericalType max() const;
        NumericalType avg() const;
};


/**
 * Caching:
 * The article suggests using caches to store already computed values. This is exemplified with a findCubicleNumber
 * function that uses a local cache to store employee cubicle numbers. This reduces the need for repeated database
 * queries, lowering the average cost of fetching this data.
*/
int findCubicleNumber(std::string employeeName)
{
    // Define a static map to hold (employee name, cubicle number)
    // pairs. This map is the local cache.
    using CubicleMap = std::map<std::string, int>;

    static CubicleMap cubes;

    // Try to find an entry for employeeName in the cache;
    // the STL iterator "it" will then point to the found
    // entry, if there is one (see Item 35 for details)
    CubicleMap::iterator it = cubes.find(employeeName);

    // "it"’s value will be cubes.end() if no entry was
    // found (this is standard STL behavior). If this is
    // the case, consult the database for the cubicle
    // number, then add it to the cache
    if (it == cubes.end())
    {
        int cubicle;   // = The result of looking up employeeName’s cubicle number in the database;

        cubes[employeeName] = cubicle; // add the pair (employeeName, cubicle) to the cache

        return cubicle;
    }
    else
    {
        // "it" points to the correct cache entry, which is a
        // (employee name, cubicle number) pair. We want only
        // the second component of this pair, and the member
        // "second" will give it to us
        return it->second;
    }
}


/**
 * Prefetching:
 * Another form of over-eager evaluation is prefetching, where data is retrieved in larger chunks than immediately
 * needed, based on the expectation that the extra data will be used soon. This is common in disk controllers and CPU
 * caches and can be applied in high-level programming.
*/


/**
 * Dynamic Arrays Example:
 * The concept is further exemplified with a DynArray template, which automatically extends its size. Instead of
 * allocating just the needed memory, it allocates extra space to reduce future allocation calls.
*/
// Template for dynamic
template<class T>
class DynArray
{
    public:
        T& operator[](int index)
};


template<class T>
T& DynArray<T>::operator[](int index)
{
    // Negative indices are still invalid
    if (index < 0)
    {
        throw /* An exception */
    }

    if (index > /* The current maximum index value */)
    {
        /* Call new to allocate enough additional memory so that index is valid */
    }

    return;  // The index-th element of the array;
}


/**
 * Trade-Off:
 * The author notes that this approach often requires more memory usage but saves time in computation. It's a classic
 * trade-off in computer science: trading space for time.
 *
 *
 * When to Use Over-Eager Evaluation:
 * The strategy is recommended when operations' results are almost always needed or frequently reused.
 * It's more complex than standard eager evaluation but can significantly improve performance in suitable scenarios.
 *
 *
 * Complementary to Lazy Evaluation:
 * The article clarifies that over-eager evaluation is not contradictory to lazy evaluation (discussed in a previous
 * item). Lazy evaluation is beneficial when results are not always needed, while over-eager evaluation suits cases
 * where results are frequently required.
*/