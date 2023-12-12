/**
 * Program in the future tense.
*/

/**
 * Expectation of Change:
 * Software developers understand that change is inevitable, though the specifics of these changes are often unknown.
 * Good software should be capable of adapting to new features, platforms, demands, and inputs.
 *
 *
 * Programming in the Future Tense:
 * This concept involves designing and implementing software with future changes in mind. It requires anticipation of
 * potential alterations, such as new functions in libraries, changes in class hierarchies, and different usage contexts.
 *
 *
 * Expressing Design Constraints in Code:
 * Instead of relying solely on comments or documentation, developers should use C++ features to enforce design
 * decisions. For instance, preventing class derivation, enforcing heap-only objects, or prohibiting copying and
 * assignment when they don't make sense.
 *
 *
 * Virtual Functions and Destructors:
 * Decisions about virtual functions should be based on the function's purpose and the likelihood of redefinition in
 * derived classes. A class designed as a base class should have a virtual destructor to behave correctly now and in
 * the future.
 *
 *
 * Assignment and Copy Construction:
 * These should be considered in every class. If not needed or difficult to implement, they should be declared private
 * or deleted to prevent default compiler-generated functions from causing issues.
 *
 *
 * Principle of Least Astonishment:
 * Classes should have intuitive and natural syntax, maintaining consistency with built-in types. Expect users to push
 * the limits of what the software can do, so design classes to be easy to use correctly and hard to use incorrectly.
 *
 *
 * Portability:
 * Aim for portable code, as it allows for easier platform switching, broadens the client base, and supports open
 * systems.
 *
 *
 * Localizing Impact of Changes:
 * Design code so that changes have localized impacts. Encapsulation, use of unnamed namespaces or file-static objects,
 * and avoidance of complex inheritance structures help achieve this.
 *
 *
 * Balancing Present and Future Needs:
 * While addressing current requirements and constraints, developers should also consider long-term viability,
 * reusability, maintainability, and robustness of their software.
*/