/**
 * Consider alternative libraries.
*/

/**
 * Compromise in Library Design:
 * The ideal library that is small, fast, powerful, flexible, extensible, intuitive, universally available,
 * well-supported, unrestricted, and bug-free does not exist. Library design involves prioritizing certain aspects over
 * others, leading to different performance profiles in libraries with similar functionalities.
 *
 * Example of iostream vs. stdio Libraries:
 * The iostream library in C++ offers advantages like type-safety and extensibility over the stdio library. However, it
 * generally lags in terms of efficiency, resulting in executables that are larger and slower.
*/
#ifdef STDIO
    #include <stdio.h>
#else
    #include <iostream>
    #include <iomanip>
#endif

const int VALUES = 30000; // # of values to read/write

int main()
{
    double d;
    for (int n = 1; n <= VALUES; ++n)
    {
        #ifdef STDIO
            scanf("%lf", &d);
            printf("%10.5f", d);
        #else
            std::cin >> d;
            std::cout << std::setw(10)                              // set field width
                      << std::setprecision(5)                       // set decimal places
                      << std::setiosflags(std::ios::showpoint)      // keep trailing 0s
                      << std::setiosflags(std::ios::fixed)          // use these settings
                      << d;
        #endif

        if (n % 5 == 0)
        {
            #ifdef STDIO
                printf("\n");
            #else
                std::cout << '\n';
            #endif
        }
    }

    return 0;
}


/**
 * Benchmarking for Performance Comparison:
 * To understand the performance differences, the article suggests benchmarking, despite its limitations. A benchmark
 * example is provided where a program reads and writes floating point numbers using either iostream or stdio, based on
 * a preprocessor directive.
 *
 *
 * Benchmark Results:
 * In various tests across different systems, the stdio version of the benchmark program consistently performs faster
 * than the iostream version, sometimes marginally and sometimes significantly. The stdio version also tends to produce
 * smaller executables.
 *
 *
 * Type-Safety and Extensibility vs. Performance:
 * The article notes that while iostream is more type-safe and extensible, it is more verbose and less efficient than
 * stdio. For example, formatting output is simpler with stdio’s printf than with iostream’s multiple method calls.
 *
 *
 * Implementation-Dependent Efficiency:
 * The efficiency advantages of stdio are highly dependent on the implementation. Future or different implementations
 * might narrow or eliminate the performance gap between iostream and stdio.
 *
 *
 * Choosing the Right Library:
 * The main takeaway is that different libraries have different performance trade-offs. Identifying bottlenecks in
 * software and choosing a library that prioritizes efficiency in that aspect can significantly improve overall
 * performance. For instance, if a program's bottleneck is I/O, switching from iostream to stdio might be beneficial.
*/