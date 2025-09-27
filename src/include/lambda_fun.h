#ifndef DELETE_H
#define DELETE_H

#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

namespace
{
    auto numbers = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
 //   auto positives = std::count_if(std::begin(numbers), std::end(numbers), [] (int const n) {return n > 0;});
auto isPositive = [](int const n) { return n > 0;};
//  auto positives = std::count_if(std::begin(numbers), std::end(numbers), ispositive);4

/*

The compiler defines an unnamed function object with the call operator, which has the signature of the lambda expression
struct __lambda_name__
{
 bool operator()(int const n) const { return n > 0; }
};

*/

auto minimum { 5 };
auto maximum { 10 };
// auto inrange = std::count_if(std::begin(numbers), std::end(numbers),[minimum, maximum](int const n) {
//  return minimum <= n && n <= maximum;});
// }

class __lambda_name_2__
{
 int minimum_;
 int maximum_;
public:
 explicit __lambda_name_2__(int const minimum, int const maximum) :
 minimum_( minimum), maximum_( maximum)
 {}
 __lambda_name_2__(const __lambda_name_2__&) = default;
 __lambda_name_2__(__lambda_name_2__&&) = default;
 __lambda_name_2__& operator=(const __lambda_name_2__&)
 = delete;
 ~__lambda_name_2__() = default;
 bool operator() (int const n) const
 {
 return minimum_ <= n && n <= maximum_;
 }
};


// generic and template lambdas ********************

auto lsum = [](auto const s, auto const n) {return s + n;};


//1.  Restrict the use of a generic lambda with only some types, such as a container, or types that satisfy a concept

std::vector<int> vi { 1, 1, 2, 3, 5, 8 };

//template lambda that can be invoked only using an std::vector

/*
auto tl = [] <typename T>(std::vector<T> const & vec)
{
    std::cout<< std::size(vec) << std::endl;
}

tl(vi); // OK, prints 6
tl(42); // error
*/

//2. Make sure that two or more arguments of a generic lambda actually do have the same type

/*
auto tl = []<typename T>(T x, Ty)
{
    std::cout << x << ' ' << y << '\n';
};

tl(10, 20); // OK
tl(10, "20"); // error

*/

// 3. Retrieve the type of a generic parameter so that, for example, we can create instances of it, invoke static methods, or use its iterator types

struct foo
{
 static void f() { std::cout << "foo\n"; }
};
/*
auto t1 = [](auto x)
{
using T = std::decay_t<decltype(x)>; //std::decay is a utility from <type_traits>

T another;

T::f();
}

t1(foo{});


c++ 20 using template

auto t1 = []<typename T>(T x)
{
T another;
T::f();
}


*/

}






#endif