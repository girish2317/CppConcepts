#include<iostream>

#ifndef FUN_ARRAY_H
#define FUN_ARRAY_H

template<typename T,  size_t const Size>
class c_array
{

    T data[Size] = {};

public:

    T const & GetAt(size_t const index) const {

        if(index < Size) return data[index]; 
        throw std::out_of_range("index out of range");     
    }

    /**
     * To Set Value at index
     * 
     * @param index array index
     * @param value value 
     */
    void SetAt(size_t const index, T const & value)
    {
        if(index < Size)
            data[index] = value;
        else
            throw std::out_of_range("index out of range");
        
    }

    T & operator [] (size_t const index){
         if(index < Size)
            return data[index];
        else
            throw std::out_of_range("index out of range");
    }

     T const & operator [] (size_t const index) const{
         if(index < Size)
            return data[index];
        else
            throw std::out_of_range("index out of range");
    }

    size_t GetSize() const{
        return Size;
    }

};


/**
 * To enable a custom type to be used in range-based for loops, you need to do the following:
 *  operator++ (both the prefix and the postfix version) for incrementing the iterator
 * operator* for dereferencing the iterator and accessing the actual element being pointed 
 * to by the iterator
 * operator!= for comparing the iterator with another iterator for inequality
 */

 template <typename T, typename C, size_t Size>
 class c_array_iterator_type
 {
public:
    c_array_iterator_type(C& collection, size_t const index):
    index(index)
    , collection(collection) 
    {}

    /**
     * for comparing the iterator with another iterator for inequality
     * @param other reference (end) iterator
     */
    bool operator != (c_array_iterator_type const &other)   
    {
        return index != other.index;
    }

    /**
     * for dereferencing the iterator and accessing the actual element being pointed to by the iterator
     */
    T const & operator*() const 
    {
        return collection.GetAt(index);
    }

    /**
     * for incrementing the iterator (both the prefix and the postfix version) 
     */
    c_array_iterator_type& operator++()
    {
        index++;
        return *this;
    }

    c_array_iterator_type operator++(int)
    {
        auto temp = *this;
        ++*this;
        return this;
    }

private:

    size_t index;
    C& collection;

 };

 //Alias templates for mutable and constant iterators

 template <typename T, size_t const Size>
 using array_iterator = c_array_iterator_type<T, c_array<T, Size>, Size>;

 template <typename T, size_t const Size>
 using array_const_iterator = c_array_iterator_type<T, c_array<T, Size> const, Size>;

// Free begin() and end() functions that return the respective begin and end iterators, with 
// overloads for both alias templates:

template <typename T, size_t const Size>
inline array_iterator<T, Size> begin(c_array<T, Size> & collection)
{
    return array_iterator<T, Size>(collection, 0);
}

template <typename T, size_t const Size>
inline array_iterator<T, Size> end(c_array<T, Size> & collection)
{
    return array_iterator<T, Size>(collection, collection.GetSize());
}

template <typename T, size_t const Size>
inline array_const_iterator<T, Size> begin(c_array<T, Size> const & collection)
{
    return array_const_iterator<T, Size>(collection, 0);
}

template <typename T, size_t const Size>
inline array_const_iterator<T, Size> end(c_array<T, Size> const & collection)
{
    return array_const_iterator<T, Size>(collection, collection.GetSize());
}


//When performing an argument-dependent lookup, the compiler will identify the two begin() and end() functions
template <typename T, size_t Size>
void print_c_array(c_array<T, Size> const & arr)
{
    for(auto && e : arr){

        std::cout<< e << "\n";
    }

}

#endif