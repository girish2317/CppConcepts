#include<iostream>

/*
C++17
-> For copy-list-initialization, auto deduction will deduce an std::initializer_list<T> if all 
the elements in the list have the same type, or be ill-formed.
-> For direct-list-initialization, auto deduction will deduce a T if the list has a single element, or 
be ill-formed if there is more than one element.

copy-list-initialization
auto a = {42}; // std::initializer_list<int>
auto c = {4, 2}; // std::initializer_list<int>

direct-list-initialization
auto b {42}; // int
auto d {4, 2}; // error, too many

*/