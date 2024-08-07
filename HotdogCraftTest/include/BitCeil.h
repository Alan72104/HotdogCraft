#pragma once

#include <print>

namespace std2
{
    uint64_t countl_zero(uint64_t n)
    {
        if (n == 0) return 0;
        uint64_t pos = 0;
        uint64_t msb = 1ULL << sizeof(uint64_t) * 8 - 1;
        while (!(n & msb))
        {
            pos++;
            n <<= 1;
        }
        return pos;
    }

    bool has_single_bit(uint64_t n)
    {
        return (n & (n - 1)) == 0;
    }

    uint64_t bit_ceil(uint64_t n)
    {
        if (!has_single_bit(n))
        {
            uint64_t nn = sizeof(n) * 8 - countl_zero(n);
            return 1ULL << nn;
        }
        return n;
    }
}