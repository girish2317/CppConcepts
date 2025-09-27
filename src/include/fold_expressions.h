
#include <iostream>

/*
feature introduced with C++17

- Simplify the process of applying a binary operator to a parameter pack in a variadic template
- They allow you to "fold" a parameter pack into a single value using a specified operator

A fold expression can be written in one of the following forms
    1. Unary Left Fold: ( ... op pack )
    2. Unary Right Fold: ( pack op ... )
    3. Binary Left Fold: ( init op ... op pack )
    4. Binary Right Fold: ( pack op ... op init )

    Where:

    -> op is a binary operator (e.g., +, *, &&, ||, etc.).
    -> pack is the parameter pack.
    -> init is an initial value for binary folds
*/

/// 1. Unary Left Fold -> ( ... op pack )

template<typename... Args>
void printAll(Args... args){

    ( std::cout<< ... << args) << "\n"; // Left fold with operator <<
}

// printAll(1, 2, 3, "Hello", 4.5); // Output: 123Hello4.5

/// 2. Unary Right Fold -> ( pack op ... )
template<typename... Args>
bool allTrue(Args... args)
{
    return (args && ...); // Right fold with operator &&
}
//std::cout << allTrue(true, true, false) << '\n'; // Output: 0 (false)

/// 3. Binary Left Fold -> Binary Left Fold: ( init op ... op pack )
template<typename... Args>
int add(Args... args)
{
    return (0 + ... + args);    // Left fold with operator + and initial value 0
}

/// @brief Binary Right Fold
/// @tparam ...Args 
/// @param ...args 
/// @return difference
template<typename... Args>
int subtract(Args... args) {
    return (args - ... - 0); // Right fold with operator - and initial value 0
}

/*
Key Points
-> Unary folds apply the operator across all elements of the pack.
-> Binary folds allow you to specify an initial value, which can be useful for operations like summation or logical comparisons.
-> Fold expressions make variadic templates more concise and readable.

This feature is particularly useful for tasks like summing numbers, printing values, or performing logical operations on a parameter pack.

*/
/// function template with a variable number of arguments

template <typename T> // [1] overload with fixed
T add(T value) // number of arguments
{
 return value;
}
template <typename T, typename... Ts> // [2] typename... Ts
T add(T head, Ts... rest) // [3] Ts... rest
{
 return head + add(rest...); // [4] rest...
}

///Using fold expressions to simplify variadic function templates

// • Left folding with a unary form (... op pack): ((pack$1 op pack$2) op ...) op pack$n
template <typename... Ts>
auto add(Ts... args)
{
    return (... + args);
}

//• Left folding with a binary form (init op ... op pack): (((init op pack$1) op pack$2) op ...) op pack$n
template <typename... Ts>
auto add_to_one(Ts... args)
{
    return (1 + ... + args);
}

// Right folding with a unary form (pack op ...):   pack$1 op (... op (pack$n-1 op pack$n))
template <typename... Ts>
auto add2(Ts... args)
{
    return (args + ...);
}

// Right folding with a binary form (pack op ... op init): pack$1 op (... op (pack$n-1 op (pack$n op init)))
template <typename... Ts>
auto add_to_one2(Ts... args)
{
    return (args + ... + 1);
}

auto sum = add(1, 2, 3, 4, 5); // sum = 15
auto sum1 = add_to_one(1, 2, 3, 4, 5); // sum = 16

/*

Fold expressions work with all overloads for the supported binary operators, but do not work with 
arbitrary binary functions

a workaround - providing a wrapper type that will hold a value and an overloaded operator for that wrapper type
*/

/// @brief class template that holds a constant reference to a value of type T
/// @tparam T 
template<typename T>
struct wrapper      
{
    T const & value;
};

template <typename T>
constexpr auto operator<(wrapper<T> const & lhs, wrapper<T> const & rhs)
{
 return wrapper<T> {lhs.value < rhs.value ? lhs.value : rhs.value};
}

/*
The variadic function template 
min (), shown here, uses this overloaded operator< to fold the pack of arguments expanded to instances of the wrapper class template:
*/

template <typename... Ts>
constexpr auto min(Ts&&... args)
{
 return (wrapper<Ts>{args} < ...).value;
}

//auto m = min(3, 1, 2); // m = 1

/*
compiler defined for above

This min() function is expanded by the compiler to something that could look like the following:
template<>
inline constexpr int min<int, int, int>(int && __args0,
 int && __args1,
 int && __args2)
{
 return operator<(wrapper_min<int>{__args0},
    operator<(wrapper_min<int>{__args1},
    wrapper_min<int>{__args2})).value;
}

*/

/// @brief result is a function that returns a Boolean
/// @tparam ...Ts 
/// @param ...args 
/// @return Boolean
template <typename... Ts>
constexpr auto minimum(Ts&&... args)
{
 return (args < ...);
}

/*
compiler transformation - min(3, 1, 2)
template<>
inline constexpr bool minimum<int, int, int>(int && __args0,
 int && __args1,
 int && __args2)
{
 return __args0 < (static_cast<int>(__args1 < __args2));
}
*/

/*
*** Implementing the higher-order functions map and fold ***

A higher-order function is a function that takes one or more other functions as arguments and applies them to a range (a 
list, vector, map, tree, and so on), thus producing either a new range or a value.

*/