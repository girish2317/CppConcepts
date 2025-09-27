#include <iostream>

struct Item
{
    int id;
    std::string name;
    double value;

    Item(int const id, std::string const & name, double const value)
    : id(id), name(name), value(value)
    {}

    bool operator==(Item const & other) const
    {
        return id == other.id && name == other.name && value == other.value;
    }
};

namespace std
{
    template<>
    struct hash<Item>
    {
        typedef Item argument_type;
        typedef size_t result_type;

        result_type operator()(argument_type const & item) const{
            result_type hashValue = 17;
            hashValue = 31 * hashValue + std::hash<int>{}(item.id);
            hashValue = 31 * hashValue + std::hash<std::string>{}(item.name);
            hashValue = 31 * hashValue + std::hash<double>{}(item.value);

            return hashValue;
        }
    };
}

/**
 * This specialization makes it possible to use the Item class with unordered associative containers, such 
 as std::unordered_set. An example is provided here:
std::unordered_set<Item> set2
{
 { 1, "one"s, 1.0 },
 { 2, "two"s, 2.0 },
 { 3, "three"s, 3.0 },
};

To compute a good hash value, you should do the following:
1. Start with an initial value, which should be a prime number (for example, 17).
2. For each field that is used to determine whether two instances of the class are equal, adjust 
the hash value according to the following formula:
hashValue = hashValue * prime + hashFunc(field);
3. You can use the same prime number for all fields with the preceding formula, but it is recommended to have a different value than the initial value (for instance, 31).
4. Use a specialization of std::hash to determine the hash value for class data members

eg. 
    std::hash<Item> hasher;
    size_t hashValue = hasher(Item(1, "one", 1.0));
    std::cout<<"Item hash value " << hashValue << std::endl;
    hashValue = hasher(Item(1, "one", 2.0));
    std::cout<<"Item hash value " << hashValue << std::endl;

    output
    Item hash value 12067002538626848761
    Item hash value 10049853779049824484
 */