#include "LazyFibGenerator.hpp"
#include <print>

int main()
{
    int i = 0;
    for (auto v : fibonacci(20))
    {
        std::println("Fib[{}] = {}", i++, v);
    }
}