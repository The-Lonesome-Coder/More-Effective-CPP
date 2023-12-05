/**
 * Understand the costs of exception handling.
*/

/**
 * Exception handling requires a lot of bookkeeping. At each point during execution, programs must keep record of the
 * objects that needs destruction if exceptions should happen. And they must remember the entry to and exit from every
 * try block. They have to keep track of the exception types each catch block can handle.
 *
 * As a result, exception handling brings cost penalty. Keeping track of the objects which needs destruction alone will
 * make your program grow in size, and make your program run slower. However, most compilers allow you to get rid of this
 * cost if you are quite sure there won't be any exception in your program.
 *
 * A second cost of exception handling arises from the try-catch blocks. These blocks alone, given that no exception is
 * thrown, can make your program grow 5-10% larger, and slow your program by a similar percent.
 *
 * So you should use try-catch blocks only when it's necessary. The hit you get from throwing an exception is even bigger.
 * Compared to normal function return, returning from a function by throwing an exception may be as much as three orders
 * of magnitude slower.
 *
 * The conclusion is: avoid using exception handling whenever possible.
*/