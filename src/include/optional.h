#include<optional>
#include<map>
#include<vector>
//#include <expected>

/**
 * Return values from functions that may fail to produce a value:
 */
template <typename K, typename V>
std::optional<V> find(K const key, std::map<K, V> const & m)
{
    auto pos = m.find(key);
    if(pos != m.end()) return pos->second;
    return {};
}

/**
 * parameters to functions that are optional:
 */
std::string extract(std::string const & text,
 std::optional<int> start,
 std::optional<int> end)
{
 auto s = start.value_or(0);
 auto e = end.value_or(text.length());
 return text.substr(s, e - s);
}

/**
 * Class data members that are optional:
 */
struct book
{
 std::string title;
 std::optional<std::string> subtitle;
 std::vector<std::string> authors;
 std::string publisher;
 std::string isbn;
 std::optional<int> pages;
 std::optional<int> year;
};

template <typename T>
class optional
{
 bool _initialized;
 std::aligned_storage_t<sizeof(T), alignof(T)> _storage;
};

/*
Benefits: Clearer semantics, avoids misuse of sentinel values
*/
std::optional<int> findValue(bool condition) {
    if (condition) return 42;
    return std::nullopt;
}

// std::expected<int, std::string> divide(int a, int b) {
//     if (b == 0) return std::unexpected("Division by zero");
//     return a / b;
// }

// error-handling chain using std::expected::and_then and transform

/**
 * 
 
 // Step 1: Parse string into integer
std::expected<int, std::string> parseInt(const std::string& s) {
    try {
        return std::stoi(s);
    } catch (...) {
        return std::unexpected("Invalid number: " + s);
    }
}

// Step 2: Check number is positive
std::expected<int, std::string> checkPositive(int x) {
    if (x <= 0) {
        return std::unexpected("Number must be positive");
    }
    return x;
}

// Step 3: Compute square
int square(int x) {
    return x * x;
}

int main() {
    std::string input = "-42";

    auto result = parseInt(input)
        .and_then(checkPositive)       // if OK → run checkPositive
        .transform(square);            // if OK → apply square

    if (result) {
        std::cout << "Square: " << *result << "\n";
    } else {
        std::cerr << "Error: " << result.error() << "\n";
    }
}



 */

