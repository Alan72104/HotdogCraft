#pragma once

#include <exception>
#include <format>
#include <print>
#include <source_location>
#include <stacktrace>

namespace HotdogCraft
{
    class Logger
    {
    public:
        template<class... Types>
        static void verbose(const std::format_string<Types...> fmt, Types&&... args)
        {
            std::print("{}", Color::gray + "v: ");
            std::print(fmt, std::forward<Types>(args)...);
            std::println("{}", Color::reset);
        }

        template<class... Types>
        static void info(const std::format_string<Types...> fmt, Types&&... args)
        {
            std::print("{}", "i: ");
            std::print(fmt, std::forward<Types>(args)...);
            std::println("{}", Color::reset);
        }

        template<class... Types>
        static void warning(const std::format_string<Types...> fmt, Types&&... args)
        {
            std::print("{}", Color::red + "w: ");
            std::print(fmt, std::forward<Types>(args)...);
            std::println("{}", Color::reset);
        }

        template<class... Types>
        static void error(const std::format_string<Types...> fmt, Types&&... args)
        {
            std::print("{}", Color::dark_red + "e: ");
            std::print(fmt, std::forward<Types>(args)...);
            std::println("{}", Color::reset);
        }

        static void throwTraced(std::string msg, std::source_location loc = std::source_location::current())
        {
            Logger::error("At {} line {}", loc.file_name(), loc.line());
            throw std::runtime_error(std::format("{}\n{}", msg, std::to_string(std::stacktrace::current())));
        }

        static void myAssert(bool cond, std::string_view msg, std::source_location loc = std::source_location::current())
        {
            if (!cond)
            {
                throwTraced(std::format("Assertion failed: {}", msg), loc);
            }
        }

    private:
        struct Color
        {
            static inline const std::string reset = "\033[0m";
            static inline const std::string black = "\033[30m";
            static inline const std::string dark_blue = "\033[34m";
            static inline const std::string dark_green = "\033[32m";
            static inline const std::string light_blue = "\033[36m";
            static inline const std::string dark_red = "\033[31m";
            static inline const std::string magenta = "\033[35m";
            static inline const std::string orange = "\033[33m";
            static inline const std::string light_gray = "\033[37m";
            static inline const std::string gray = "\033[90m";
            static inline const std::string blue = "\033[94m";
            static inline const std::string green = "\033[92m";
            static inline const std::string cyan = "\033[96m";
            static inline const std::string red = "\033[91m";
            static inline const std::string pink = "\033[95m";
            static inline const std::string yellow = "\033[93m";
            static inline const std::string white = "\033[97m";
        };
    };
}