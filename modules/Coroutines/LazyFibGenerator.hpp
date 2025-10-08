#pragma once
#include <cstdint>
#include <generator>

inline std::generator<std::uint64_t> fibonacci(std::size_t count)
{
    std::uint64_t a = 0, b = 1;
    for (std::size_t i = 0; i < count; ++i)
    {
        co_yield a;
        auto next = a + b;
        b = a;
        a = next;
    }
}