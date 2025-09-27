
/*
enumerations declared with enum class or enum struct are called scoped enumerations. C++ 11

scope enumerations are restricted namespaces
strongly typed 

disadvantages with unscoped enums
    - export their enumerators to the surrounding scope
        - name clashes if two enumerations in the same namespace
        - 


*/

#include<iostream>

enum class Status { Unknown, Created, Connected };
Status s = Status::Created;

enum class user_rights : unsigned
{

    None,
    Read =1,
    Write =2,
    Delete =4
};

//C++20 standard allows us to associate them with a using directive

int main()
{
    // using enum user_rights;
    // int a = std::to_underlying()

};