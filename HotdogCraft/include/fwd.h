#pragma once

#include <cstdint>
#include <format>
#include <imgui.h>
#include <memory>
#include <ranges>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

namespace HotdogCraft
{
    using i8 = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;
    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    template <auto fn>
    struct DeleterFromFn
    {
        template <typename T>
        constexpr void operator()(T* arg) const
        {
            fn(arg);
        }
    };

    template <typename T>
    using up = std::unique_ptr<T>;
    template <typename T, auto Fn>
    using cup1 = std::unique_ptr<T, DeleterFromFn<Fn>>;
    template <typename T>
    using cup = cup1<T, free>;

    using std::ranges::views::iota;
}

namespace ImGui
{
    template<class... Types>
    void TextF(const std::format_string<Types...> fmt, Types&&... args)
    {
        ImGui::Text(std::format(fmt, std::forward<Types>(args)...).c_str());
    }
}

template<int L, class T>
struct std::formatter<glm::vec<L, T, glm::qualifier::highp>> : std::formatter<T>
{
    std::format_context::iterator format(
        const glm::vec<L, T, glm::qualifier::highp>& v,
        std::format_context& ctx) const
    {
        auto out = ctx.out();
        std::string_view sep = "";
        out = std::format_to(out, "(");
        for (int i : std::ranges::views::iota(0, L))
        {
            out = std::format_to(out, "{}", sep);
            ctx.advance_to(out);
            out = std::formatter<T>::format(v[i], ctx);
            sep = ",";
        }
        out = std::format_to(out, ")");
        return out;
    }
};

template<int C, int R, class T>
struct std::formatter<glm::mat<C, R, T, glm::qualifier::highp>> : std::formatter<T>
{
    std::format_context::iterator format(
        const glm::mat<C, R, T, glm::qualifier::highp>& m,
        std::format_context& ctx) const
    {
        auto out = ctx.out();
        std::string_view sep1 = "";
        out = std::format_to(out, "(");
        for (int i : std::ranges::views::iota(0, C))
        {
            std::string_view sep2 = "";
            out = std::format_to(out, "{}", sep1);
            out = std::format_to(out, "(");
            for (int j : std::ranges::views::iota(0, R))
            {
                out = std::format_to(out, "{}", sep2);
                ctx.advance_to(out);
                out = std::formatter<T>::format(m[i][j], ctx);
                sep2 = ",";
            }
            out = std::format_to(out, ")");
            sep1 = ",";
        }
        out = std::format_to(out, ")");
        return out;
    }
};