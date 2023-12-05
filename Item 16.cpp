/**
 * Remember the 80-20 rule.
*/

/**
 * The 80-20 rule, widely verified in various systems, suggests that 80% of resources are used by about 20% of a program's
 * code. This rule, while not to be taken as exact figures, highlights that a small portion of code largely determines a
 * software's overall performance. For programmers, this means that performance issues are likely concentrated in a small
 * part of the code, making it crucial to identify and optimize these areas. However, guessing the performance bottlenecks,
 * as many do, is usually ineffective because program performance characteristics are often counterintuitive.
 *
 * Effective optimization requires using a profiler to empirically identify the problematic 20% of the code. The profiler
 * should measure the specific resources of concern, such as time or memory usage, to help focus efforts on parts of the
 * code where improvements will significantly enhance overall performance. Profilers that provide data on statement
 * execution or function calls are less helpful for performance tuning.
 *
 * It's important to use representative data sets when profiling to avoid optimizing for atypical usage scenarios.
 * By profiling with a variety of representative data, programmers can fine-tune their software to better meet the needs
 * of its primary users.
*/