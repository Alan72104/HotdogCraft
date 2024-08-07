#define _HAS_CXX20 1

#include <bit>
#include <BitCeil.h>
#include <chrono>
#include <format>
#include <functional>
#include <fwd.h>
#include <glm/fwd.hpp>
#include <HotdogCraft.h>
#include <print>
#include <ranges>
#include <string>

namespace HotdogCraft
{
    static std::chrono::high_resolution_clock::time_point now()
    {
        return std::chrono::high_resolution_clock::now();
    }

    static std::string dur(std::chrono::nanoseconds ns, i64 count)
    {
        auto loc = std::locale("en_US");
        return std::format(loc, "{:L%T} {:L} * {:L}", ns, ns / count, count);
    }

    static void bench(std::function<void()> func)
    {
        auto measureTarget = std::chrono::duration<double>(0.1);
        auto target = std::chrono::duration<double>(0.25);
        i64 count = 1;
        auto start = now();
        func();
        auto elapsed = now() - start;
        std::println("warm up {}", dur(elapsed, count));
        if (elapsed < measureTarget)
        {
            count = std2::bit_ceil((i64)std::ceil(measureTarget / elapsed));
            start = now();
            for (int i : iota(0, count))
                func();
            elapsed = now() - start;
            std::println("measure {}", dur(elapsed, count));
        }
        count = std2::bit_ceil((i64)std::ceil(target / (elapsed / count)));
        start = now();
        for (int i : iota(0, count))
            func();
        elapsed = now() - start;
        std::println("bench {}", dur(elapsed, count));
        std::println();
    }

    static void main()
    {
        std::println("hello {}", "worl");
        bench([]()
            {
                std::format("{}", glm::vec4(1, 2, 3, 4));
            });
        bench([]()
            {
                auto v = glm::vec4(1, 2, 3, 4);
                std::format("({},{},{},{})", v[0], v[1], v[2], v[3]);
            });
        bench([]()
            {
                std::format("{}", glm::mat4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
            });
        bench([]()
            {
                auto v = glm::mat4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
                std::format("(({},{},{},{}),({},{},{},{}),({},{},{},{}),({},{},{},{}))",
                    v[0][0], v[0][1], v[0][2], v[0][3],
                    v[1][0], v[1][1], v[1][2], v[1][3],
                    v[2][0], v[2][1], v[2][2], v[2][3],
                    v[3][0], v[3][1], v[3][2], v[3][3]);
            });
        std::println("{:.3f}", glm::mat3x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
        auto v = glm::mat3x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        std::println("(({},{},{},{}),({},{},{},{}),({},{},{},{}))",
            v[0][0], v[0][1], v[0][2], v[0][3],
            v[1][0], v[1][1], v[1][2], v[1][3],
            v[2][0], v[2][1], v[2][2], v[2][3]);
    }
}

int main()
{
    HotdogCraft::main();
    return 0;
}