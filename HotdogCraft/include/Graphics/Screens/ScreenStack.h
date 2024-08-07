#pragma once

#include <Graphics/Screens/Screen.h>
#include <stack>

namespace HotdogCraft::Graphics::Screens
{
    class ScreenStack
    {
    public:

    private:
        std::stack<Screen> stack{};
    };
}