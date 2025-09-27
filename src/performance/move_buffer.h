#include <iostream>
#include <cstring>
#include <utility>

class Buffer
{
    char* ptr;
    size_t length;

public:
    // default constructor
    Buffer() noexcept : ptr(nullptr), length(0)
    {}
    ~Buffer()
    {
        delete[] ptr;
    }

    explicit Buffer(size_t const size) noexcept :
    ptr(new char[size] {0}), length(size)
    {}

    // Constructor from C-string
    Buffer(const char* str)
    {
        if(str){
            length = std::strlen(str);
            ptr = new char[length + 1];
            std::memcpy(ptr, str, length + 1);
        }
        else {
            ptr = new char[1]{'\0'};
            length = 0;
        }

        std::cout << "[Ctor] this=" << this << " data=" << (void*)ptr << "\n";
    }

    // Copy constructor
    Buffer(const Buffer& other): 
        ptr(new char[other.length + 1]),
        length(other.length)
    {
        std::memcpy(ptr, other.ptr, length + 1);
        std::cout << "[Copy ctor] this=" << this << " data=" << (void*)ptr 
             << " (copied from " << &other << ")\n";
    }

    // Copy assignment
    Buffer& operator = (const Buffer& other)
    {
        if(this != &other){

            delete[] ptr;

            ptr = new char[other.length + 1];
            length = other.length;
            std::memcpy(ptr, other.ptr, length + 1);
        }
        return *this;
    }

     // Move constructor
     Buffer(Buffer&& other) noexcept
        : ptr(other.ptr), length(other.length)
    {
        other.ptr = new char[1] {'\0'};
        other.length = 0;

        std::cout << "[Move ctor] this=" << this << " data=" << (void*)ptr 
             << " (moved from " << &other << ")\n";
    }

    /*
    //or alternative move constructor 
    Buffer(Buffer&& other) : ptr(nullptr), length(0)
    {
        *this = std::move(other);
    }
    */

     // Move assignment
    Buffer& operator = (Buffer&& other) noexcept
    {
        if(this != &other){

            delete[] ptr;

            ptr = other.ptr;
            length = other.length;
            other.ptr = new char[1]{0};
            other.length = 0;
        }
        return *this;
    }

    // size
    std::size_t size() const noexcept {return length;}

    // C-string accessor
    const char* c_str() const noexcept {return ptr;}

    // Indexing operator (with bounds checking)
    char& operator[](std::size_t index){
        if(index >= length) throw std::out_of_range("Index out of range");
        return ptr[index];
    }

    const char& operator[](std::size_t index) const {
        if (index >= length) throw std::out_of_range("Index out of range");
        return ptr[index];
    }

    // Concatenation
    Buffer operator+(const Buffer& rhs) const {
        std::size_t newSize = length + rhs.length;
        char* newData = new char[newSize + 1];
        std::memcpy(newData, ptr, length);
        std::memcpy(newData + length, rhs.ptr, rhs.length + 1);
        Buffer result;
        delete[] result.ptr;
        result.ptr = newData;
        result.length = newSize;
        return result;
    }

    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const Buffer& str) {
        return os << str.ptr;
    }
};


/**
 * 
 Notes: Move semantics
 
 * move semantics provide a performance benefit in the context of rvalues *

 An rvalue is an object that does not have a name; 
 it lives temporarily during the evaluation of an expression and is destroyed at the next semicolon
 expressed with &&
 lvalues cannot be moved; they can only be copied

 */