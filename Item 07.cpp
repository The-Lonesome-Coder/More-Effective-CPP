/**
 * Never overload &&, ||, or ,.
*/

/**
 * C++ allows you to customize the behavior of the && and || operators for user-defined types.
 * If you decide to take advantage of this opportunity, however, you must be aware that you are changing the
 * rules of the game quite radically, because you are replacing short-circuit semantics with function call semantics.
 *
 * This may not seem like that big a deal, but function call semantics differ from short-circuit semantics in two ways:
 *
 * 1. When a function call is made, all parameters must be evaluated, so when calling the functions operator&& and
 *    operator||, both parameters are evaluated.
 *
 * 2. The language specification leaves undefined the order of evaluation of parameters to a function call, so there
 * is no way of knowing whether expression1 or expression2 will be evaluated first.
 *
 * As a result, if you overload && or ||, there is no way to offer programmers the behavior they both expect and have come
 * to depend on.
*/
