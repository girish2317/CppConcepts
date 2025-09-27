#include <iostream>
#include <vector>
#include <ranges>

void printPositiveNumbers(const std::vector<int>& numbers) {
    for (int num : numbers | std::views::filter( { return n > 0; })) {
        std::cout << num << '\n';
    }
}

/**
 * Range-based for loop: More readable and idiomatic.
 * std::views::filter (C++20): Declarative filtering of elements.   
 * Use of '\n' instead of std::endl: Avoids unnecessary flushing of output buffer.
 */

 /**
  * |   Traditional	                    |   Modern Idiom
  * -------------------------------------------------------------------------------------
  * |   new / delete	                |   Use std::unique_ptr or std::shared_ptr
  * |   Raw loops	                    |   Use std::for_each, std::ranges, or range-based loops
  * |   Manual string manipulation	    |   Use std::string and std::string_view
  * |   typedef	                        |   Use using for type aliases
  * |   NULL	                        |   Use nullptr
  * |   throw exceptions	            |   Use std::optional or std::expected for error handling (C++23)
  */