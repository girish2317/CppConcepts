
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

/**
 * Using exceptions for error handling
 * 
 * When an exception occurs, the stack is unwound (undo) from the point where the exception was thrown to the block where the exception 
        is handled. This process involves the destruction of all local objects in all those stack frame

        If the destructor of an object that is being destroyed during this process throws an exception, another 
        stack unwinding process should begin, which conflicts with the one already under way. Because of 
        this, the program terminates abnormally

        *****
        he rule of thumb for dealing with exceptions in constructors and destructors is as follows:
            • Use exceptions to indicate the errors that occur in constructors.
            • Do not throw or let exceptions leave destructors.
        *****
 */

 void throwing_func()
{
 throw std::runtime_error("timed out");
}

void another_throwing_func()
{
 throw std::system_error(
 std::make_error_code(std::errc::timed_out));
}

// Custom Exception Class
class FileNotFound : public std::runtime_error {
public:
    explicit FileNotFound(const std::string& filename)
    : std::runtime_error("File not found: " + filename) {}
};

void openFile(const std::string& filename) {
    if (filename != "data.txt") {
        throw FileNotFound(filename);
    }
    std::cout << "File opened successfully: " << filename << "\n";
}

// Use noexcept when a function guarantees no exceptions.
// If an exception is thrown from a noexcept function → std::terminate() is called.
void safeFunction() noexcept {
    // Guaranteed not to throw
}

void riskyFunction() noexcept(false) { // explicit
    throw std::runtime_error("oops");
}

// Use noexcept on move constructors/assignment to enable optimizations.


