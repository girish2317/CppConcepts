
#include <iostream>
#include <string>

class foo
{
    int a;
    double b;
    std::string c;
public:
    foo(int const a = 0, double const b = 0, std::string const & c = "") :a(a), b(b), c(c)
    {}
    void print() const
    {
        std::cout << '(' << a << ',' << b << ',' << std::quoted(c) << ')' << '\n';
    }
};

void study_unique_ptr()
{
    std::unique_ptr<int> pnull;
    std::unique_ptr<int> pi(new int(42));
    std::unique_ptr<int []> pa(new int[3] {1, 2, 3});
    std::unique_ptr<foo> pa(new foo(42, 42.0, "42"));

}