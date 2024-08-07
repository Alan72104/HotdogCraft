#include <HotdogCraft.h>
#include <iostream>
#include <Logger.h>
#include <memory>

int main()
{
    try
    {
        HotdogCraft::HotdogCraft::instance = std::make_unique<HotdogCraft::HotdogCraft>();
        HotdogCraft::HotdogCraft::ins().run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}